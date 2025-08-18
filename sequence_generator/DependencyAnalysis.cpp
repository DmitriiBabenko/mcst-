#include "DependencyAnalysis.h"
#include <iostream>

void DependencyAnalyzer::buildDependencyGraph(const std::vector<Instruction> & ops, const unsigned regs) {
    current_versions.clear();
    current_versions.resize(regs, 0);

    nodes.clear();
    nodes.reserve(ops.size());

    std::vector<std::vector<DependencyNode*>> version_to_node(regs);

    for (unsigned i = 0; i < regs; ++i) {
        version_to_node[i].reserve(10);
        version_to_node[i].push_back(nullptr);
    }

    for (size_t i = 0; i < ops.size(); ++i) {
        const auto & instr = ops[i];

        nodes.emplace_back(i, instr.dest_reg, current_versions[instr.dest_reg] + 1);
        DependencyNode* current_node = & nodes.back();

        if (instr.op != Instruction::Ops::INIT) {
            std::vector<DependencyNode*> unique_dependencies;
            unique_dependencies.reserve(2);

            if (current_versions[instr.src_reg1] > 0) {
                if (const unsigned version = current_versions[instr.src_reg1]; version < version_to_node[instr.src_reg1].size() &&
                                                                               version_to_node[instr.src_reg1][version] != nullptr) {
                    unique_dependencies.push_back(version_to_node[instr.src_reg1][version]);
                } else {
                    std::cerr << "Error: Could not find reg " << instr.src_reg1
                                << " version " << version << " in instruction " << i <<std::endl;
                    return;
                }
            } else {
                std::cerr << "Error: Using uninitialized register " << instr.src_reg1
                            << " in instruction " << i << std::endl;
                return;
            }

            if (current_versions[instr.src_reg2] > 0) {
                if (const unsigned version = current_versions[instr.src_reg2]; version < version_to_node[instr.src_reg2].size() &&
                                                                               version_to_node[instr.src_reg2][version] != nullptr) {
                    unique_dependencies.push_back(version_to_node[instr.src_reg2][version]);
                } else {
                    std::cerr << "Error: Could not find reg " << instr.src_reg2
                                << " version " << version << " in instruction " << i <<std::endl;
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

        const unsigned new_version = ++current_versions[instr.dest_reg];
        current_node->version = new_version;

        if (new_version >= version_to_node[instr.dest_reg].size()) {
            version_to_node[instr.dest_reg].resize(new_version + 1, nullptr);
        }
        version_to_node[instr.dest_reg][new_version] = current_node;
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
            stack.reserve(nodes.size());
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
       std::vector<bool> written_regs(ops.size(), false);
        std::vector<bool> read_regs(ops.size(), false);

        int max_reg = 0;
        for(const auto * node : comp.nodes) {
            max_reg = std::max(max_reg, node->reg_number);
        }
        for (const size_t instr_idx : comp.instruction_indices) {
            if (instr_idx < ops.size()) {
                if (const auto & instr = ops[instr_idx]; instr.op != Instruction::Ops::INIT) {
                    max_reg = std::max(max_reg, std::max(instr.src_reg1, instr.src_reg2));
                }
            }
        }

        if (max_reg >= static_cast<int> (written_regs.size())) {
            written_regs.resize(max_reg + 1, false);
            read_regs.resize(max_reg+ 1, false);
        }

        for (const auto * node : comp.nodes) {
            written_regs[node->reg_number] = true;
        }

        for (const size_t instr_idx : comp.instruction_indices) {
            if (instr_idx < ops.size()) {
                if (const auto & instr = ops[instr_idx]; instr.op != Instruction::Ops::INIT) {
                    read_regs[instr.src_reg1] = true;
                    read_regs[instr.src_reg2] = true;
                }
            }
        }

        for (int reg = 0; reg <= max_reg; ++reg) {
            if (read_regs[reg] && !written_regs[reg]) {
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
