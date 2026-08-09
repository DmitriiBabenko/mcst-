#ifndef CACHE_H
#define CACHE_H
#include <string>
#include "Graph.h"

void saveCache(const Graph & graph, const std::string & path);
Graph loadCache(const std::string & path);

#endif //CACHE_H