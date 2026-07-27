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

int main(const int argc, char* argv[]) {
    unsigned seed = 0, size = 0, regs = 0, comps = 1;
    bool ir, soi, sor, cache;
    std::string stage, cache_path;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<unsigned>(&seed), "random seed")
        ("size", po::value<unsigned>(&size), "execution size")
        ("regs", po::value<unsigned>(&regs), "number of registers")
        ("comps", po::value<unsigned>(&comps), "minimal number of components of tree of operations")
        ("ir", po::bool_switch(&ir), "show intermediate results")
        ("soi", po::bool_switch(&soi), "show sequence of instructions")
        ("sor", po::bool_switch(&sor), "show system of restrictions")
        ("cache", po::bool_switch(&cache)->default_value(false), "to cache or load the solved system of restrictions")
        ("stage", po::value<std::string>(&stage)->default_value("full"), "to generate secuense <prefix> | to assign registers in a sequense <suffix> | to execute full program <full>")
        ("cache-path", po::value<std::string>(&cache_path)->default_value(""), "path to cache or load the solved system of restrictions");

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

    std::vector<Graph> components;
    std::vector<ComponentSolution> system_of_restrictions;

    if (stage == "prefix" || stage == "full") {
        std::cout << "Generating sequence with seed=" << seed
                    << ", size=" <<size << ", regs=" << regs << ", components=" << comps <<'\n';

        components = generate_sequense(seed, size, comps, soi);
        
        system_of_restrictions = generate_system_of_restrictions(components, seed, sor);
        solve_system(components, system_of_restrictions);
        if (cache) {
            cachesolutions(system_of_restrictions, cache_path, seed, size, comps);
        }
    }

    if (stage == "suffix" || stage == "full") {
        if (cache) {
            cache_path = cache_path.empty() ? cacheFilePath(seed, size, regs, comps) : cache_path;
            if (unsigned cached_seed = 0, cached_size = 0, cached_comps = 0; tryloadfromcache(system_of_restrictions, cache_path, cached_seed, cached_size, cached_comps)) {
                std::cout << "\nloaded solved system of restrictions from cache\n";
                components = generate_sequense(cached_seed, cached_size, cached_comps);
                apply_cached_values(components, system_of_restrictions);
            } else {
                std::cout << "\n[ERROR]:  failed to load solved system\n";
                return 1;
            }
        }
        std::vector<Node*> sorted_nodes = build_secuense_nodes(components);
        std::unordered_map<Node*, std::size_t> rho;
        try {
            rho = assign_registers(sorted_nodes, regs);
        } catch(std::runtime_error & e) {
            std::cout << "\n[ERROR]:  " << e.what() << '\n';
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
    }

    return 0;
}