#ifndef CACHE_H
#define CACHE_H
#include <string>
#include <optional>
#include "Graph.h"

void saveCache(const Graph & graph, const std::string & path);
std::optional<Graph> loadCache(const std::string & path);

#endif //CACHE_H