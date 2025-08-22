//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include <iostream>

#include "solveRandomApply.h"

namespace po = boost::program_options;

int main(const int argc, char* argv[]) {
    unsigned seed = 0, size = 0, regs = 0;
    bool ir, soi, sor;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<unsigned>(&seed)->required(), "random seed")
        ("size", po::value<unsigned>(&size)->required(), "execution size")
        ("regs", po::value<unsigned>(&regs)->required(), "number of registers")
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
    std::cout<<1;
    solveRandomApply(seed, size, regs, ir, soi, sor);
    return 0;
}