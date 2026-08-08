//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"
#include "Values.h"
#include "Cache.h"
#include <stdexcept>

namespace po = boost::program_options;

bool checkUnsignedKey(const unsigned key, const std::string name) {
    if (key == 0) {
        std::cerr << "\n[ERROR]: specify --" << name <<'\n';
        return false;
    }
    return true;
}

Graph runStage1(unsigned seed, unsigned size, unsigned comps) {
    return Graph(seed, size, comps);
}

Graph runStage2(const Graph & graph, unsigned seed) {
    auto values = solve(graph, seed);
    if (!values) {
        throw std::runtime_error("runStage2: constraint system is unsatisfiable");
    }
    return graph.withValues(std::move(*values));
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
    
    if (start > 1 && cache_path_download.empty()) {
        std::cerr << "start > 1 requires --cache-path-download\n";
        return 1;
    }

    std::optional<Graph> current;

    try {
        //---------------------------------------
        //Stage 1
        if (auto cached = loadCache(cache_path_download)) {
            current = std::move(*cached);
        } else if (start > 1) {
            std::cerr << "cannot load graph from cache: " << cache_path_download << "\n";
            return 1;
        } else if (start <= 1 && end >= 1) {
            current = runStage1(seed, size, comps);
        }

        if (start <= 1 && end >= 1 && current) {
            const bool log = (logs.find('1') != std::string::npos);
            if (log) {
                std::ofstream out("graph.dot");
                out << current->toDot();
            }
        }

        if (!cache_path_upload.empty() && current) {
            saveCache(*current, cache_path_upload);
        }

        if (end == 1) {
            return 0;
        }

        //---------------------------------------
        //Stage 2
        if (start <= 2 && end >= 2) {
            const bool log = (logs.find('2') != std::string::npos);
            current = runStage2(*current, seed);

            if (log) {
                std::ofstream out("graph_stage2.dot");
                out << current->toDot();
            }
        }

        if (!cache_path_upload.empty() && current) {
            saveCache(*current, cache_path_upload);
        }

        if (end == 2) {
            return 0;
        }
    } catch (const std::exception & e) {
        std::cerr << "[ERROR]: " << e.what() << "\n";
        return 1;
    }

    return 0;
}