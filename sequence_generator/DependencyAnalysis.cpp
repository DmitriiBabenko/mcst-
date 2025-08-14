#include "DependencyAnalysis.h"

void DependencyAnalyzer::buildDependencyGraph(const std::vector<Instruction> & ops, unsigned regs) {
    for (unsigned i = 0; i < regs; ++i) {
        current_versions[i] = 0;
    }

    nodes.clear();
    nodes.reserve(ops.size());

    std::unordered_map<std::string, DependencyNode*> version_to_node;

    for(size_t i = 0; i < ops.size(); ++i) {
        const auto& instr = ops[i];

        int new_version = ++current_versions[instr.dest_reg];

        nodes.emplace_back(i, instr.dest_reg, new_version);
        DependencyNode* current_node = &nodes.back();

        std::string key = std::to_string(instr.dest_reg) + "_" + std::to_string(new_version);
        version_to_node[key] = current_node;

        if(instr.op != Instruction::Ops::INIT) {
            std::string src1_key = std::to_string(instr.src_reg1) + "_" + std::to_string(current_versions[instr.src_reg1]);
            auto it1 = version_to_node.find(src1_key);
            if (it1 != version_to_node.end()) {
                current_node->dependencies.push_back(it1->second);
                it1->second->dependents.push_back(current_node);
            }

            std::string src2_key = std::to_string(instr.src_reg2) + "_" + std::to_string(current_versions[instr.src_reg2]);
            auto it2 = version_to_node.find(src2_key);
            if (it2 != version_to_node.end()) {
                current_node->dependencies.push_back(it2->second);
                it2->second->dependents.push_back(current_node);
            }
        }
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

void DependencyAnalyzer::classifyRegisters() {
    for (auto & comp : components) {
        std::unordered_set<int> written_regs;
        std::unordered_set<int> read_regs;

        for(auto * node : comp.nodes) {
            written_regs.insert(node->reg_number);

            for (auto * dep : node->dependencies) {
                read_regs.insert(dep->reg_number);
            }
        }

        for (int reg : read_regs) {
            if (written_regs.find(reg) == written_regs.end()) {
                comp.input_regs.insert(reg);
            }
        }
    }
}

std::vector<Component> DependencyAnalyzer::analyze(const std::vector<Instruction>& ops, unsigned regs) {
    buildDependencyGraph(ops, regs);
    findComponents();
    classifyRegisters();
    return components;
}
