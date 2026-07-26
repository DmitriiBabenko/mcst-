//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>
#include "solveRandomApply.h"
#include "Registerallocation.h"
#include "VerificationGenerator.h"

namespace po = boost::program_options;

int main(const int argc, char* argv[]) {
    unsigned seed = 0, size = 0, regs = 0, comps = 1;
    bool ir, soi, sor;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<unsigned>(&seed)->required(), "random seed")
        ("size", po::value<unsigned>(&size)->required(), "execution size")
        ("regs", po::value<unsigned>(&regs)->required(), "number of registers")
        ("comps", po::value<unsigned>(&comps)->required(), "minimal number of components of tree of operations")
        ("ir", po::bool_switch(&ir), "show intermediate results")
        ("soi", po::bool_switch(&soi), "show sequence of instructions")
        ("sor", po::bool_switch(&sor), "show system of restrictions");

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
    assert(regs >= size / (comps - 1));
    std::cout << "Generating sequence with seed=" << seed
                << ", size=" <<size << ", regs=" << regs << ", components=" << comps <<'\n';

    std::vector<Graph> components = generate_sequense(seed, size, comps, soi);
    
    std::vector<ComponentSolution> system_of_restrictions = generate_system_of_restrictions(components, seed, sor);

    solve_system(components, system_of_restrictions);

    std::vector<Node*> sorted_nodes = build_secuense_nodes(components);
    std::unordered_map<Node*, std::size_t> rho = assign_registers(sorted_nodes, regs);

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