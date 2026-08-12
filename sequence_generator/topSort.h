#ifndef TOPSORT_H
#define TOPSORT_H
#include <vector>
#include "Graph.h"
const std::vector<Graph> topSort(const std::vector<Graph> & graph, const unsigned & seed, const bool & log);
#endif //TOPSORT_H