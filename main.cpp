#include "z3++.h"
#include <iostream>
#include <vector>
#include <set>
#include "RandomFpa32.h"
#include "pseudoOperations.h"

int main() {
    std::set<std::vector<float>> set;
    randomFpa32(set, 5, 10);
    pseudoOperations(2, 5, 5);
    return 0;
}