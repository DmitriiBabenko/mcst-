//
// Created by димасик on 31.07.2025.
//
#ifndef SOLVERANDOMAPPLY_H
#define SOLVERANDOMAPPLY_H
#include "ComponentSolution.h"
#include "Graph.h"
    void solveRandomApply(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, const bool intermediateResults, const bool soi, bool sor);
    std::vector<Graph> generate_sequense(const unsigned seed, const unsigned size, const unsigned comps, const bool log);
    std::vector<ComponentSolution> generate_system_of_restrictions(std::vector<Graph> & components, const unsigned seed, const bool sol);
    void solve_system(std::vector<Graph> & components, std::vector<ComponentSolution> & system_of_restrictions, const bool log);
    std::vector<std::shared_ptr<Node>> build_secuense_nodes(std::vector<Graph> & components, const unsigned seed, const bool log);
    void apply_cached_values(std::vector<Graph> & components, const std::vector<ComponentSolution> & solutions, const bool log);
#endif //SOLVERANDOMAPPLY_H
