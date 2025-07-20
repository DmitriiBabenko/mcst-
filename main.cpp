#include "z3++.h"
#include <iostream>
#include <vector>
#include <set>
#include "RandomFpa32.h"

int main() {
    std::set<std::vector<float>> set;
    randomFpa32(set, 5, 10);
    return 0;
}