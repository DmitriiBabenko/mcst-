#ifndef ASSIGNREG_H
#define ASSIGNREG_H
#include <vector>
#include "Graph.h"
const Graph assignComponent(const Graph & graph, std::mt19937 & gen, const unsigned & regs);
#endif //ASSIGNREG_H