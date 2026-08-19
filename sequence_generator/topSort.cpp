#include "topSort.h"
#include <iterator>
#include <random>
#include <algorithm>
#include <numeric>
#include <iostream>
struct newGraph {
    std::vector<float> values;
    std::vector<std::vector<std::size_t>> ways;
    std::vector<Ops> ops;
};

void dfs(const std::size_t & node, const Graph & component, newGraph & newgraph, std::vector<bool> & used, std::mt19937 & gen, std::vector<size_t> & old_indexes) {
    used[node] = true;
    std::vector<std::size_t> copy = component.ways()[node];
    std::shuffle(copy.begin(), copy.end(), gen);
    for (const auto & u : copy) {
        if (!used[u]) {
            dfs(u, component, newgraph, used, gen, old_indexes);
        }
    }
    old_indexes[node] = newgraph.values.size();
    newgraph.values.push_back(component.values()[node]);
    newgraph.ops.push_back(component.ops()[node]);
}

const std::vector<std::vector<std::size_t>> recalcWays(const std::vector<std::vector<std::size_t>> & oldWays, std::vector<std::size_t> & old_indexes) {
    std::vector<std::vector<std::size_t>> ways(oldWays.size());
    for (std::size_t node = 0; node < oldWays.size(); ++node) {
        for (const auto & other : oldWays[node]) {
            ways[old_indexes[node]].push_back(old_indexes[other]);
        }
    }
    return ways;
}

const Graph topSortComponent(const Graph & component, const unsigned seed) {
    newGraph newgraph;
    std::vector<std::size_t> old_indexes(component.size());
    std::vector<bool> used(component.size(), false);
    std::mt19937 gen(seed);
    std::vector<std::size_t> nodesToChoose(component.size());
    std::iota(std::begin(nodesToChoose), std::end(nodesToChoose), 0);
    std::shuffle(nodesToChoose.begin(), nodesToChoose.end(), gen);
    for (const auto & node : nodesToChoose) {
        if (!used[node]) {
            dfs(node, component, newgraph, used, gen, old_indexes);
        }
    }
    std::reverse(newgraph.values.begin(), newgraph.values.end());
    std::reverse(newgraph.ops.begin(), newgraph.ops.end());

    for (auto & pos : old_indexes) {
        pos = newgraph.values.size() - 1 - pos;
    }
    return (Graph(newgraph.ops, recalcWays(component.ways(), old_indexes), recalcWays(component.incWays(), old_indexes), newgraph.values, component.regs()));
}

const std::vector<Graph> topSort(const std::vector<Graph> & graph, const unsigned & seed, const bool & log) {
    std::vector<Graph> result;
    std::size_t idx = 0;
    for (const auto & component : graph) {
        result.push_back(topSortComponent(component, seed));
        if (log) {
            std::cout << "\n===component № " << idx++ << "===\n";
            result.back().print(log);
        }
    }
    return result;
}