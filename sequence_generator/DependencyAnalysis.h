//
// Created by димасик on 14.08.2025.
//
#pragma once
#include "Instruction.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct DependencyNode {
    size_t instruction_idx;
    int reg_number;
    int version;
    std::vector<DependencyNode*> dependencies;
    std::vector<DependencyNode*> dependents;
    bool visited = false;
    int component_id = -1;

    DependencyNode(size_t idx, int reg, int ver)
        : instruction_idx(idx), reg_number(reg), version(ver) {}

};

struct Component {
    std::vector<DependencyNode*> nodes;
    std::vector<size_t> instruction_indices;
    std::unordered_set<int> involved_regs;
    std::unordered_set<int> input_regs;
    bool is_satisfiable = true;
};

class DependencyAnalyzer {
private:
    std::vector<DependencyNode> nodes;
    std::vector<Component> components;
    std::unordered_map<int, int> current_versions;

public:
    std::vector<Component> analyze(const std::vector<Instruction> & ops, unsigned regs);
    void printAnalysis() const;
private:
    void buildDependencyGraph(const std::vector<Instruction> & ops, unsigned regs);
    void findComponents();
    void classifyRegisters();
};