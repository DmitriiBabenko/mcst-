#ifndef VALUES_H
#define VALUES_H
#include <vector>
#include <optional>
#include "Graph.h"

std::optional<std::vector<float>> solve(const Graph & graph, unsigned seed);
#endif //VALUES_H