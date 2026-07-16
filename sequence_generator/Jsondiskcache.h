#ifndef JSONDISKCACHE_H
#define JSONDISKCACHE_H
#include <vector>
#include <boost/json.hpp>
#include "Componentsolution.h"
bool tryloadfromcache(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, std::vector<ComponentSolution> & solutions);
void cachesolutions(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, std::vector<ComponentSolution> & solutions);
#endif //JSONDISKCACHE_H
