#include "z3++.h"
#include <iostream>
#include <vector>
#include <set>
#include "RandomFpa32.cpp"
#include "pseudoOperations.cpp"
int main() {
    std::set<std::vector<float>> a;
    pseudoOperations(15, 5, 10);
    return 0;
}