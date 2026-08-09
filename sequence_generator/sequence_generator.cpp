//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <cstdlib>
#include "Graph.h"
#include "Values.h"
#include "Cache.h"
#include <stdexcept>

namespace po = boost::program_options;

struct Args {
    unsigned seed;
    unsigned size;
    unsigned comps;
    unsigned regs;
};

Graph runStage1(const Graph & g, const Args & args) {
    return Graph(args.seed, args.size, args.comps);
}

Graph runStage2(const Graph & graph, const Args & args) {
    return graph.withValues(solve(graph, args.seed));
}

void tryLog(const char & idx, const Graph & current, const std::string & logs) {
    if (logs.find(idx) != std::string::npos) {
        const std::string name_dot = std::string("stage") + idx + ".dot";
        const std::string name_png = std::string("stage") + idx + ".png";
        std::ofstream out(name_dot);
        out << current.toDot();
        out.close();
        const std::string command = "dot -Tpng " + name_dot + " -o " + name_png; 
        if (std::system(command.c_str()) != 0) {
            throw std::runtime_error("Dot: failed to compile graph.png");
        }
    }
}

using Fn = std::function<Graph(const Graph & graph, const  Args & args)>;



int main(const int argc, char* argv[]) {
    unsigned seed, size, regs, comps, start, end;
    std::string stage, cache_path_download, cache_path_upload, logs;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<unsigned>(&seed)->default_value(1), "random seed")
        ("size", po::value<unsigned>(&size)->default_value(1), "execution size")
        ("regs", po::value<unsigned>(&regs)->default_value(1), "number of registers")
        ("comps", po::value<unsigned>(&comps)->default_value(1), "minimal number of components of tree of operations")
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

    const Args args{seed, size, comps, regs};
    const std::vector<Fn> functions = {runStage1, runStage2};
    const std::vector<char> chars = {'1', '2'};
    Graph current(0, 0, 0);
    try {
        if (start > 1) {
            current = loadCache(cache_path_download);
        }
        for(std::size_t idx = start; idx <= end; ++idx) {
            current = functions[idx - 1](current, args);
            tryLog(chars[idx - 1], current, logs);
        }
        if(!cache_path_upload.empty()) {
            saveCache(current, cache_path_upload);
        }
    } catch (std::runtime_error & e) {
        std::cout << "[ERROR]: " << e.what();
        return 1;
    }
    return 0;
}