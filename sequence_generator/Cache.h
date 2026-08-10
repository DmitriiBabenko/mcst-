#ifndef CACHE_H
#define CACHE_H
#include <string>
#include "Graph.h"

void saveCache(const std::vector<Graph> & graph, const std::string & path);
const std::vector<Graph> loadCache(const std::string & path);

#endif //CACHE_H