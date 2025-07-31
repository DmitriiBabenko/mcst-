//
// Created by димасик on 31.07.2025.
//
#include <boost/program_options.hpp>
#include "pseudoOperations.h"
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    int seed = 0, size = 0, regs = 0;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("seed", po::value<int>(&seed)->required(), "random seed")
        ("size", po::value<int>(&size)->required(), "execution size")
        ("regs", po::value<int>(&regs)->required(), "number of registers");

    po::variables_map vm;
    try {
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

    pseudoOperations(seed, regs, size);
    return 0;
}
