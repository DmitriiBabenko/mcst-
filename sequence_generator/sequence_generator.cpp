//
// Created by Dmitrii B. on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <cstdlib>
#include <filesystem>
#include <random>
#include <sys/wait.h>
#include "Graph.h"
#include "Values.h"
#include "Cache.h"
#include "topSort.h"
#include "assignRegisters.h"
#include "Verify.h"
#include <stdexcept>

namespace po = boost::program_options;

struct Args {
    unsigned seed;
    unsigned size;
    unsigned comps;
    unsigned regs;
    std::string log;
};

//Pred: DotsDir и PmgDir существуют, current - валидный граф
//Post: .dot и .png с заданными именами
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

//Pred: Current - набор валидных графов. Logs и idx - произвольные
//Post: 1) idx не содержится в logs => никаких побочных эффектов
//      2) иначе будут созданы директории dots/journal, для каждого из графов в этих директориях будут созданы .dot и .png
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

//current: валидный граф, остальные параметры произвольные.
//post: будут созданы директории "[ERROR]dots" и "[ERROR]journal"
//      и вызвана функция log(current, "[ERROR]dots", "[ERROR]journal")
void tryLogError(const Graph & current, const std::size_t idx, const std::string & message) {
    const std::filesystem::path dotsDir = "[ERROR]dots";
    const std::filesystem::path pngDir = "[ERROR]journal";
    std::filesystem::create_directories(dotsDir);
    std::filesystem::create_directories(pngDir);
    log(current, dotsDir, pngDir, message + "_component_" + std::to_string(idx));
}

//Pred: args.comps > 0
//      параметр g не используется
//Post: набор валидных графов, содержащих:
//       минимум args.comps компонент связности,
//       в сумме ровно args.size узлов
std::vector<Graph> runStage1(const std::vector<Graph> & g, const Args & args) {
    std::cout << "======Generating graph with operations======\n";
    std::vector<Graph> graph;
    std::mt19937 gen(args.seed);
    const bool log = (args.log.find('1') != std::string::npos);
    for (std::size_t idx = 0, comp_size = args.size / args.comps, rest = args.size % args.comps; idx < args.comps; ++idx, rest ^= rest) {
        if (log) {
            std::cout << "===component №" << idx <<"===\n";
        }
        graph.push_back(Graph(gen, comp_size + rest));
        graph.back().print(log);
    }
    return graph;
}

//Pred: graph - набор валидных графов
//Post: вектор из одного валидного графа, являющегося объединением подмножества всех переданных графов.
//        в каждом из узлов графа - вычесленное значение согласованное с его арифметической операцией и с узлами ведущими/исходящими из него. 
//        В случае, если не получится разрешить систему ограничений, заданную в graph_i, граф не будет добавлен в результирубщий набор и в [ERROR]/journal будет копия неразрешённого графа
std::vector<Graph> runStage2(const std::vector<Graph> & graph, const Args & args) {
    std::cout << "\n======Generating system of restrictions======\n";
    const bool log = (args.log.find('2') != std::string::npos);
    std::vector<Graph> new_graph;
    const std::size_t total = graph.size();
    std::size_t idx = 0;
    for (const auto & item : graph) {
        try {
            if (log) {
                std::cout << "[" << (idx) << "/" << total << "] solving component...\n";
            }
            new_graph.push_back(Graph(item.ops(), item.ways(), item.incWays(), solve(item, args.seed, log), item.regs()));
        } catch(const std::runtime_error & e) {
            std::cerr << e.what() << "watch [ERROR]journal/ directory\n";
            tryLogError(item, idx - 1, "failed_to_sat");
        }
        idx++;
    }
    const std::vector<Graph> united = {uniteGraph(new_graph)};
    return united;
}

//Pred: graph - набор валидных графов
//Post: набор валидных графов, result[idx] == graph[idx] с точностью до топологической сортировки
const std::vector<Graph> runStage3(const std::vector<Graph> & graph, const Args & args) {
    const bool log = (args.log.find('3') != std::string::npos);
    std::cout << "\n======Sorting======\n";
    return topSort(graph, args.seed, log);
}

//Pred: graph - набор валидных графов. args.regs > 0
//Post: набор валидных графов, для любых двух узлов a и b, f - порядок в топологической сортировке графа
//                              где f(a) < f(b) ==> f(b) > f(c_i), где c_i все узлы вычисляемые из a
//                              суммарное количегство узлов <= суммарного количества узлов в components
//  в случае если args.regs будет недостаточно для выполнения pred условия, граф не будет добавлен в результирующий набор и будет вызвана trylogerror(...);
const std::vector<Graph> runStage4(const std::vector<Graph> & components, const Args & args) {
    std::vector<Graph> result;
    const bool log = (args.log.find('4') != std::string::npos);
    std::mt19937 gen(args.seed);
    std::cout << "\n======Assigning registers======\n";
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        try {
            result.push_back(assignComponent(components[idx], gen, args.regs));
            if (log) {
                std::cout << "\n===component № " << idx << "===\n";
            }
            result.back().print(log);
        } catch(std::runtime_error & e) {
            std::cerr << e.what() << "watch [ERROR]journal/ directory\n";
            std::cerr << "[ERROR]|While assigning registers| In component " << std::to_string(idx) << ":\n" << e.what() << '\n';
            tryLogError(components[idx], idx, "failed_to_assigned_" + std::to_string(args.regs) + "_regs");
        }
    }
    return result;
}

void compileAndRunVerify(const std::filesystem::path & cPath, const std::filesystem::path & binPath) {
    const std::string compileCmd = "gcc -std=c11 " + cPath.string() + " -o " + binPath.string() + " -lm";
    if (std::system(compileCmd.c_str()) != 0) {
        throw std::runtime_error("failed to compile verification file for " + binPath.string());
    }
    const std::string runCmd = binPath.string();
    if (std::system(runCmd.c_str()) != 0) {
        throw std::runtime_error("failed to run " + binPath.string());
    }
}

//pred: components - набор валидных графов; forall g: g.hasValues() и c.hasRegs()
//post: verify/ где для каждого графа из входного набора происходит эмуляция арифметических операция над регистрами  
const std::vector<Graph> runStage5(const std::vector<Graph> & components, const Args & args) {
    const bool log = (args.log.find('5') != std::string::npos);
    std::cout << "\n======Verifying against predicted results======\n";
    const std::filesystem::path verifyDir = "verify";
    std::filesystem::create_directories(verifyDir);
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        const Graph & component = components[idx];
        const std::string baseName = "component_" + std::to_string(idx);
        const std::filesystem::path cPath = verifyDir / (baseName + ".c");
        const std::filesystem::path binPath = verifyDir / baseName;
        try {
            std::ofstream out(cPath);
            out << toVerify(component);
            out.close();
            compileAndRunVerify(cPath, binPath);
            if (log) {
                std::cout << "===component № " << idx << "=== OK\n";
            }
        } catch (const std::runtime_error & e) {
            std::cerr << e.what() << '\n';
            std::cerr << "[ERROR]|While verifying| In component " << std::to_string(idx) << ":\n" << e.what() << '\n';
            tryLogError(component, idx, "failed_verification");
        }
    }
    return components;
}

using Fn = std::function<std::vector<Graph>(const std::vector<Graph> & graph, const  Args & args)>;


//pred: --help/--h
//post выполнения подмонежства этапов из README
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
        ("end", po::value<unsigned>(&end)->default_value(4), "end stage")
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

    const Args args{seed, size, comps, regs, logs};
    const std::vector<Fn> functions = {runStage1, runStage2, runStage3, runStage4, runStage5};
    const std::vector<char> chars = {'1', '2', '3', '4', '5'};
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
        if(!cache_path_upload.empty()) {
            saveCache(current, cache_path_upload);
        }
    } catch (std::runtime_error & e) {
        std::cout << "[ERROR]: " << e.what();
        return 1;
    }
    return 0;
}