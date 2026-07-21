#pragma once
#include "Instruction.h"
#include <vector>

struct DependencyNode {
    unsigned instruction_idx;
    unsigned reg_number;
    unsigned version;
    std::vector<DependencyNode*> dependencies;
    std::vector<DependencyNode*> dependents;
    bool visited = false;
    int component_id = -1;

    DependencyNode(const unsigned idx, const unsigned reg, const unsigned ver)
        : instruction_idx(idx), reg_number(reg), version(ver) {
        dependencies.reserve(2);
        dependents.reserve(4);
    }

};

struct Component {
    std::vector<DependencyNode*> nodes;
    std::vector<unsigned> instruction_indices;
    std::vector<unsigned> involved_regs;
    std::vector<unsigned> input_regs;
    bool is_satisfiable = true;
};

class DependencyAnalyzer {
private:
    std::vector<DependencyNode> nodes;
    std::vector<Component> components;
    std::vector<unsigned> current_versions;

public:
    std::vector<Component> analyze(const std::vector<Instruction> & ops, unsigned regs);
    void printAnalysis() const;
private:
    void buildDependencyGraph(const std::vector<Instruction> & ops, unsigned regs);
    void findComponents();
    void classifyRegisters(const std::vector<Instruction> & ops);
};