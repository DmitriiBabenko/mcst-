//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <filesystem>
#include <random>
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

void log(const Graph & current, const std::filesystem::path & dotsDir, const std::filesystem::path & pngDir, const std::string baseName) {
        const std::filesystem::path dotPath = dotsDir / (baseName + ".dot");
        const std::filesystem::path pngPath = pngDir / (baseName + ".png");

        std::ofstream out(dotPath);
        out << current.toDot();
        out.close();

        const std::string command = "dot -Tpng " + dotPath.string() + " -o " + pngPath.string(); 
        if (std::system(command.c_str()) != 0) {
            throw std::runtime_error("Dot: failed to compile " + pngPath.string());
        }
}

void tryLog(const char & idx, const std::vector<Graph> & current, const std::string & logs) {
    if (logs.find(idx) != std::string::npos) {
        const std::filesystem::path dotsDir = "dots";
        const std::filesystem::path pngDir = "journal";
        std::filesystem::create_directories(dotsDir);
        std::filesystem::create_directories(pngDir);
        for (std::size_t ind = 0; ind < current.size(); ++ind) {
            const std::string baseName = std::string("stage") + idx + "component_" + std::to_string(ind);
            log(current[ind], dotsDir, pngDir, baseName);
        }
    }
}

void tryLogError(const Graph & current, const std::size_t idx) {
    const std::filesystem::path dotsDir = "[ERROR]dots";
    const std::filesystem::path pngDir = "[ERROR]journal";
    std::filesystem::create_directories(dotsDir);
    std::filesystem::create_directories(pngDir);
    log(current, dotsDir, pngDir, "unsat_component_" + std::to_string(idx));
}

std::vector<Graph> runStage1(const std::vector<Graph> & g, const Args & args) {
    std::vector<Graph> graph;
    std::mt19937 gen(args.seed);
    for (std::size_t idx = 0, comp_size = args.size / args.comps, rest = args.size % args.comps; idx < args.comps; ++idx, rest ^= rest) {
        graph.push_back(Graph(gen, comp_size + rest));
    }
    return graph;
}

std::vector<Graph> runStage2(const std::vector<Graph> & graph, const Args & args) {
    std::vector<Graph> new_graph;
    const std::size_t total = graph.size();
    std::size_t idx = 0;
    for (const auto & item : graph) {
        std::cout << "[" << (++idx) << "/" << total << "] solving component...\n";
        try {
            new_graph.push_back(item.withValues(solve(item, args.seed)));
        } catch(const std::runtime_error & e) {
            std::cerr << e.what() << "watch [ERROR]journal/ directory\n";
            tryLogError(item, idx - 1);
        }
    }
    return new_graph;
}

using Fn = std::function<std::vector<Graph>(const std::vector<Graph> & graph, const  Args & args)>;



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
        ("logs", po::value<std::string>(&logs)->default_value("12345"), "show logs in stages, for example: \"12345\"")
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
    std::mt19937  tmpgen(1);
    std::vector<Graph> current(comps, {tmpgen, 0});

    try {
        if (start > 1) {
            current = loadCache(cache_path_download);
        }
        for(std::size_t idx = start; idx <= end; ++idx) {
            current = functions[idx - 1](current, args);
            tryLog(chars[idx - 1], current, logs);
        }
        std::cout << cache_path_upload.empty() ? "YES\n" : "NO\n";
        if(!cache_path_upload.empty()) {
            saveCache(current, cache_path_upload);
        }
    } catch (std::runtime_error & e) {
        std::cout << "[ERROR]: " << e.what();
        return 1;
    }
    return 0;
}