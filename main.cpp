#include "z3++.h"
#include <iostream>
#include <vector>
#include <set>
#include "RandomFpa32.h"
#include "pseudoOperations.h"

int main() {
    std::set<std::vector<float>> set;
    std::string way;
    std::cout<<"input <a + b> to solve a + b == c problem"<<std::endl<<"input something else to solve randomOp problem"<<std::endl;
    std::cin>>way;
    if (way == "a + b") {
        int c, s;
        std::cout<<"count of a,b,c:    seed:"<<std::endl;
        std::cin>>c>>s;
        randomFpa32(set, c, s);
    } else {
        int seed, size, regs;
        std::cout<<"--seed:       --exec-size:        --regs-num:"<<std::endl;
        std::cin>>seed>>size>>regs;
        pseudoOperations(seed, regs, size);
    }
    return 0;
}