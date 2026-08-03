#ifndef JSONDISKCACHE_H
#define JSONDISKCACHE_H
#include <vector>
#include <boost/json.hpp>
#include "ComponentSolution.h"
struct Cache {
    std::vector<ComponentSolution> _system_of_restrictions_2;
    unsigned _seed_1;
    unsigned _seed_2;
    unsigned _seed_3;
    unsigned _seed_4;
    unsigned _size_1;
    unsigned _comps_1;
    unsigned _regs_4;
};
Cache tryloadfromcache(const std::string & path);
void cachesolutions(const std::string & custom_path, const Cache & cache);
#endif //JSONDISKCACHE_H
