#include "DependencyAnalysis.h"
#include <iostream>

void DependencyAnalyzer::buildDependencyGraph(const std::vector<Instruction> & ops, const unsigned regs) {
    current_versions.clear();
    for (unsigned i = 0; i < regs; ++i) {
        current_versions[i] = 0;
    }

    nodes.clear();
    nodes.reserve(ops.size());

    std::unordered_map<std::string, DependencyNode*> version_to_node;

    for (size_t i = 0; i < ops.size(); ++i) {
        const auto & instr = ops[i];

        nodes.emplace_back(i, instr.dest_reg, current_versions[instr.dest_reg] + 1);
        DependencyNode* current_node = & nodes.back();

        if (instr.op != Instruction::Ops::INIT) {
            std::unordered_set<DependencyNode*> unique_dependencies;

            if (current_versions[instr.src_reg1] > 0) {
                std::string src1_key = std::to_string(instr.src_reg1) + "_" + std::to_string(current_versions[instr.src_reg1]);
                if (auto it1 = version_to_node.find(src1_key); it1 != version_to_node.end()) {
                    unique_dependencies.insert(it1->second);
                } else {
                    std::cerr << "Error: Could not find for " << src1_key << " in instruction " << i << std::endl;
                    return;
                }
            } else {
                std::cerr << "Error: Using uninitialized register " << instr.src_reg1
                            << " in instruction " << i << std::endl;
                return;
            }

            if (current_versions[instr.src_reg2] > 0) {
                std::string src2_key = std::to_string(instr.src_reg2) + "_" + std::to_string(current_versions[instr.src_reg2]);
                if (auto it2 = version_to_node.find(src2_key); it2 != version_to_node.end()) {
                    unique_dependencies.insert(it2->second);
                } else {
                    std::cerr << "Error: Could not find for " << src2_key << " in instruction " << i << std::endl;
                    return;
                }
            } else {
                std::cerr << "Error: Using uninitialized register " << instr.src_reg2
                            << " in instruction " << i << std::endl;
                return;
            }

            for (DependencyNode* dep : unique_dependencies) {
                current_node->dependencies.push_back(dep);
                dep->dependents.push_back(current_node);
            }
        }

        const int new_version = ++current_versions[instr.dest_reg];
        current_node->version = new_version;

        std::string key = std::to_string(instr.dest_reg) + "_" + std::to_string(new_version);
        version_to_node[key] = current_node;
    }
}

void DependencyAnalyzer::findComponents() {
    components.clear();
    int component_counter = 0;

    for (auto& node : nodes) {
        node.visited = false;
        node.component_id = -1;
    }

    for (auto& node : nodes) {
        if (!node.visited) {
            Component comp;
            std::vector<DependencyNode*> stack;
            stack.push_back(&node);

            while(!stack.empty()) {
                DependencyNode* current = stack.back();
                stack.pop_back();

                if (current->visited) continue;

                current->visited = true;
                current->component_id = component_counter;
                comp.nodes.push_back(current);
                comp.instruction_indices.push_back(current->instruction_idx);
                comp.involved_regs.insert(current->reg_number);

                for (auto * dep : current->dependencies) {
                    if (!dep->visited) {
                        stack.push_back(dep);
                    }
                }

                for (auto * dependent : current->dependents) {
                    if(!dependent->visited) {
                        stack.push_back(dependent);
                    }
                }
            }

            components.push_back(std::move(comp));
            component_counter++;
        }
    }
}

void DependencyAnalyzer::classifyRegisters(const std::vector<Instruction> & ops) {
    for (auto & comp : components) {
        std::unordered_set<int> written_regs;
        std::unordered_set<int> read_regs;

        for(const auto * node : comp.nodes) {
            written_regs.insert(node->reg_number);
        }

        for (const size_t instr_idx : comp.instruction_indices) {
            if (instr_idx < ops.size()) {
                if (const auto & instr = ops[instr_idx]; instr.op != Instruction::Ops::INIT) {
                    read_regs.insert(instr.src_reg1);
                    read_regs.insert(instr.src_reg2);
                }
            }
        }

        for (int reg : read_regs) {
            if (written_regs.find(reg) == written_regs.end()) {
                comp.input_regs.insert(reg);
            }
        }
    }
}

std::vector<Component> DependencyAnalyzer::analyze(const std::vector<Instruction>& ops, const unsigned regs) {
    buildDependencyGraph(ops, regs);
    findComponents();
    classifyRegisters(ops);
    return components;
}
