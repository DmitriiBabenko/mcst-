//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include "solveRandomApply.h"
#include "Registerallocation.h"
#include "VerificationGenerator.h"
#include "Jsondiskcache.h"
#include <stdexcept>

namespace po = boost::program_options;

bool checkUnsignedKey(const unsigned key, const std::string name) {
    if (key == 0) {
        std::cerr << "\n[ERROR]: specify --" << name <<'\n';
        return false;
    }
    return true;
}

int main(const int argc, char* argv[]) {
    unsigned seed, size, regs, comps, start, end;
    std::string stage, cache_path_download, cache_path_upload, logs;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<unsigned>(&seed)->default_value(0), "random seed")
        ("size", po::value<unsigned>(&size)->default_value(0), "execution size")
        ("regs", po::value<unsigned>(&regs)->default_value(0), "number of registers")
        ("comps", po::value<unsigned>(&comps)->default_value(0), "minimal number of components of tree of operations")
        ("start", po::value<unsigned>(&start)->default_value(1), "start stage")
        ("end", po::value<unsigned>(&end)->default_value(5), "end stage")
        ("logs", po::value<std::string>(&logs)->default_value(""), "show logs in stages, for example: \"12345\"")
        ("cache-path-download", po::value<std::string>(&cache_path_download)->default_value(""), "path to download the cache")
        ("cache-path-upload", po::value<std::string>(&cache_path_upload)->default_value(""), "path to upload the cache");

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }
        po::notify(vm);
    } catch (const po::error& e) {
        std::cerr << "Argument error: " << e.what() << "\n" << desc << "\n";
        return 1;
    }

    if (start > end || start < 1 || end > 5) {
        std::cerr << "start must be <= end, start must be >= 1, end must be <= 5";
        return 1;
    }

    std::vector<Graph> components;
    std::vector<ComponentSolution> system_of_restrictions;
    std::vector<std::shared_ptr<Node>> sorted_nodes;
    std::unordered_map<std::shared_ptr<Node>, std::size_t> rho;
    Cache cache;

    if (start != 1) {
        cache = tryloadfromcache(cache_path_download);
    }
    if (comps > size) {
        std::cerr << "\ncomps must be <= size\n";
        return 1;
    }

//-------------------------------------------
// Stage 1
        bool log = (logs.find('1') != std::string::npos);
        if (start > 1) {
            components = generate_sequense(cache._seed_1, cache._size_1, cache._comps_1, log);
        } else {
            if (!checkUnsignedKey(size, "size") || !checkUnsignedKey(seed, "seed") || !checkUnsignedKey(comps, "comps")) {
                return 1;
            }
            std::cout << "Generating sequence with seed=" << seed
                    << ", size=" <<size << ", components=" << comps <<'\n';
            components = generate_sequense(seed, size, comps, log);

            cache._seed_1 = seed;
            cache._size_1 = size;
            cache._comps_1 = comps;
        }

        if (end == 1) {
            if (cache_path_upload != "") {
                cachesolutions(cache_path_upload, cache);
            }
            return 0;
        }
//-------------------------------------------
// Stage 2

    log = (logs.find('2') != std::string::npos);

    if (start > 2) {
        apply_cached_values(components, cache._system_of_restrictions_2, log);
    } else {
        if (!checkUnsignedKey(seed, "seed")) {
            return 1;
        }
        std::cout << "\ngenerating system of restrictions...\n";
        system_of_restrictions = generate_system_of_restrictions(components, seed, log);
        std::cout << "\nsolving system of restrictions...\n";
        solve_system(components, system_of_restrictions, log);

        cache._system_of_restrictions_2 = std::move(system_of_restrictions);
        cache._seed_2 = seed;
    }

    if (end == 2) {
        if (cache_path_upload != "") {
            cachesolutions(cache_path_upload, cache);
        }
        return 0;
    }

//-------------------------------------------
// Stage 3

    log = (logs.find('3') != std::string::npos);

    if (start > 3) {
        sorted_nodes = build_secuense_nodes(components, cache._seed_3, log);
    } else {
        if (!checkUnsignedKey(seed, "seed")) {
            return 1;
        }
        std::cout << "\nbuilding top.sort...\n";
        sorted_nodes = build_secuense_nodes(components, seed, log);

        cache._seed_3 = seed;
    }

    if (end == 3) {
        if (cache_path_upload != "") {
            cachesolutions(cache_path_upload, cache);
        }
        return 0;
    }

//-------------------------------------------
// Stage 4

    log = (logs.find('4') != std::string::npos);

    if (start > 4) {
        try {
            rho = assign_registers(sorted_nodes, cache._regs_4, cache._seed_4, log);
        } catch (std::runtime_error & e) {
            std::cerr << "[ERROR]: " << e.what() << '\n';
            return 1;
        }
    } else {
        if (!checkUnsignedKey(seed, "seed") || !checkUnsignedKey(regs, "regs")) {
            return 1;
        }
        std::cout << "\nassigning registerts...\n";
        try {
            rho = assign_registers(sorted_nodes, regs, seed, log);
        } catch (std::runtime_error & e) {
            std::cerr << "[ERROR]: " << e.what() << '\n';
            return 1;
        }

        cache._regs_4 = regs;
        cache._seed_4 = seed;
    }

    if (end == 4) {
        if (cache_path_upload != "") {
            cachesolutions(cache_path_upload, cache);
        }
        return 0;
    }

//-------------------------------------------
// Stage 5
    if (!checkUnsignedKey(seed, "seed") || !checkUnsignedKey(regs, "regs")) { 
        return 1;
    }

    const std::string verify_cpp = VerificationGenerator::generateVerificationCode(sorted_nodes, rho, regs, seed);
    if (verify_cpp.empty()) {
        std::cerr << "Failed to write verification file\n";
        return 1;
    }
    if (!VerificationGenerator::compileAndRun(verify_cpp)) {
        return 1;
    }

    return 0;
}