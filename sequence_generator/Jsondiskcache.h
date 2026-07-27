#ifndef JSONDISKCACHE_H
#define JSONDISKCACHE_H
#include <vector>
#include <boost/json.hpp>
#include "ComponentSolution.h"
bool tryloadfromcache(std::vector<ComponentSolution> & solutions, const std::string & custom_path, unsigned & cached_seed, unsigned & cached_size, unsigned & cached_comps);
void cachesolutions(std::vector<ComponentSolution> & solutions, const std::string & custom_path, const unsigned seed, const unsigned size, const unsigned comps);
std::string cacheFilePath(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps);
#endif //JSONDISKCACHE_H
