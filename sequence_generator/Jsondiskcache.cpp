#include "Jsondiskcache.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem>
#include <stdexcept>

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

Cache tryloadfromcache(const std::string & path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("path: \"" + path +  "\" to download cache isn't exists");
    }

    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    boost::json::value jv = boost::json::parse(buffer.str());
    const auto & obj = jv.as_object();

    Cache cache;
    cache._seed_1 = static_cast<unsigned>(obj.at("_seed_1").to_number<std::uint64_t>());
    cache._seed_2 = static_cast<unsigned>(obj.at("_seed_2").to_number<std::uint64_t>());
    cache._seed_3 = static_cast<unsigned>(obj.at("_seed_3").to_number<std::uint64_t>());
    cache._seed_4 = static_cast<unsigned>(obj.at("_seed_4").to_number<std::uint64_t>());
    cache._size_1 = static_cast<unsigned>(obj.at("_size_1").to_number<std::uint64_t>());
    cache._comps_1 = static_cast<unsigned>(obj.at("_comps_1").to_number<std::uint64_t>());
    cache._regs_4 = static_cast<unsigned>(obj.at("_regs_4").to_number<std::uint64_t>());

    const auto & solutions_arr = obj.at("solutions").as_array();
    for (const auto & item : solutions_arr) {
        cache._system_of_restrictions_2.push_back(componentSolutionFromJson(item));
    }

    return cache;
}

void cachesolutions(const std::string & path, const Cache & cache) {
    const std::filesystem::path fs_path(path);
    if (fs_path.has_parent_path()) {
        std::filesystem::create_directories(fs_path.parent_path());
    }

    boost::json::array solutions_json;
    for (const auto & sol : cache._system_of_restrictions_2) {
        solutions_json.push_back(componentSolutionToJson(sol));
    }

    const boost::json::object out = {
        {"solutions", std::move(solutions_json)},
        {"_seed_1", cache._seed_1},
        {"_seed_2", cache._seed_2},
        {"_seed_3", cache._seed_3},
        {"_seed_4", cache._seed_4},
        {"_size_1", cache._size_1},
        {"_comps_1", cache._comps_1},
        {"_regs_4", cache._regs_4},
    };

    std::ofstream file(path);
    file << boost::json::serialize(out);
}