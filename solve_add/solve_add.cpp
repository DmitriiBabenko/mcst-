#include <boost/program_options.hpp>
#include "RandomFpa32.h"
#include <set>
#include <vector>
#include <iostream>
#include "z3++.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    int count = 0, seed = 0;

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "show help")
        ("count,c", po::value<int>(&count)->required(), "number of a,b,c sets")
        ("seed,s", po::value<int>(&seed)->required(), "random seed");

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

    std::set<std::vector<float>> set;
    randomFpa32(set, count, seed);

    return 0;
}
