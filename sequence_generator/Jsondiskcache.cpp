#include "Jsondiskcache.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem>

boost::json::value componentSolutionToJson(const ComponentSolution & sol) {
    boost::json::object values_obj;
    for (const auto & [name, val] : sol.variable_values) {
        values_obj[name] = val;
    }

    return boost::json::value {
        {"is_satisfiable", sol.is_satisfiable},
        {"variable_values", std::move(values_obj)}
    };
}

ComponentSolution componentSolutionFromJson(const boost::json::value & jv) {
    const auto & obj =  jv.as_object();

    ComponentSolution sol;
    sol.is_satisfiable = obj.at("is_satisfiable").as_bool();

    const auto & values_obj = obj.at("variable_values").as_object();
    for (const auto & [key, val] : values_obj) {
        sol.variable_values[std::string(key)] = static_cast<float>(val.as_double());
    }

    return sol;
}

std::string cacheFilePath(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps) {
    return std::string("cache_solutions") + "/sol_seed" + std::to_string(seed) + "_size" + std::to_string(size) +
    "_regs" + std::to_string(regs) +
    "_comps" + std::to_string(comps) + ".json"; 
}

bool tryloadfromcache(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, std::vector<ComponentSolution> & solutions) {
    const std::string path = cacheFilePath(seed, size, regs, comps);

    if (!std::filesystem::exists(path)) {
        return false;
    }

    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    boost::json::value jv;
    jv = boost::json::parse(buffer.str());

    const auto & obj = jv.as_object();

    const auto & solutions_arr = obj.at("solutions").as_array();
    solutions.reserve(solutions_arr.size());
    for (const auto & item : solutions_arr) {
        solutions.push_back(componentSolutionFromJson(item));
    }

    return true;
}
void cachesolutions(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, std::vector<ComponentSolution> & solutions) {
    std::filesystem::create_directories("cache_solutions");
    const std::string path = cacheFilePath(seed, size, regs, comps);

    boost::json::array solutions_json;
    solutions_json.reserve(solutions.size());
    for (const auto & sol : solutions) {
        solutions_json.push_back(componentSolutionToJson(sol));
    }

    const boost::json::object out = {
        {"solutions", std::move(solutions_json)}
    };

    std::ofstream file(path);
    file << boost::json::serialize(out);
}