//
// Created by димасик on 31.07.2025.
//
#include "solveRandomApply.h"
#include "Instruction.h"
#include "genSeq.h"
#include "z3++.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "../common_add/fpa_to_float.h"
#include "DependencyAnalysis.h"
struct ComponentSolution {
    bool is_satisfiable = false;
    std::unordered_map<std::string, float> variable_values;
    z3::model model;

    ComponentSolution(z3::context & ctx) : model(ctx) {}
};

float findFinalValue(int reg, const std::unordered_map<std::string, float> & values,
        const std::vector<Instruction> & OpsSeq) {

    int max_version = -1;
    for (size_t i = 0; i < OpsSeq.size(); ++i) {
        if (OpsSeq[i].dest_reg == reg) {
            max_version++;
        }
    }

    if (max_version >= 0) {
        std::string var_name = "reg_" + std::to_string(reg) + "_" + std::to_string(max_version + 1);
        auto it = values.find(var_name);
        if (it != values.end()) {
            return it->second;
        }
    }

    std::string input_name = "reg_" + std::to_string(reg) + "_input";
    auto it = values.find(input_name);
    if (it != values.end()) {
        return it->second;
    }

    return -1;
}

ComponentSolution solveComponent(const Component& comp, const std::vector<Instruction> & OpsSeq,
                                unsigned seed, bool show_constraints) {
    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", seed);

    const z3::sort float32 = ctx.fpa_sort(8, 24);
    z3::solver s(ctx);
    s.set(p);

    ComponentSolution solution(ctx);

    std::unordered_map<std::string, z3::expr> local_vars;

    for (int reg : comp.input_regs) {
        std::string name = "reg_" + std::to_string(reg) + "_input";
        z3::expr var = ctx.constant(name.c_str(), float32);
        s.add(z3::to_expr(ctx, Z3_mk_fpa_is_normal(ctx, var)));
        local_vars.emplace(name, var);
    }

    std::vector<size_t> sorted_indicies = comp.instruction_indices;
    std::sort(sorted_indicies.begin(), sorted_indicies.end());

    std::unordered_map<int, int> local_versions;

    for (size_t idx : sorted_indicies) {
        const auto & instr = OpsSeq[idx];

        int new_version = ++local_versions[instr.dest_reg];
        std::string result_name = "reg_" + std::to_string(instr.dest_reg) + "_" + std::to_string(new_version);

        z3::expr result_var = ctx.constant(result_name.c_str(), float32);
        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, result_var)));
        local_vars.emplace(result_name, result_var);

        if (instr.op != Instruction::Ops::INIT) {
            std::string src1_name, src2_name;

            if (local_versions.find(instr.src_reg1) != local_versions.end()) {
                src1_name = "reg_" + std::to_string(instr.src_reg1) + "_" + std::to_string(local_versions[instr.src_reg1]);
            } else {
                src1_name = "reg_" + std::to_string(instr.src_reg1) + "_input";
            }

            if (local_versions.find(instr.src_reg2) != local_versions.end()) {
                src2_name = "reg_" + std::to_string(instr.src_reg2) + "_" + std::to_string(local_versions[instr.src_reg2]);
            } else {
                src2_name = "reg_" + std::to_string(instr.src_reg2) + "_input";
            }

            z3::expr src1 = local_vars[src1_name];
            z3::expr src2 = local_vars[src2_name];

            switch (instr.op) {
                case Instruction::Ops::ADD:
                    s.add(result_var == src1 + src2);
                    break;
                case Instruction::Ops::SUB:
                    s.add(result_var == src1 - src2);
                    break;
                case Instruction::Ops::MUL:
                    s.add(result_var == src1 * src2);
                    break;
                case Instruction::Ops::DIV:
                    s.add(result_var == src1 / src2);
                    break;
            }
        }
    }

    if (show_constraints) {
        std::cout << "Component constraints:\n" << s << "\n";
    }

    if (s.check() == z3::sat) {
        solution.is_satisfiable = true;
        solution.model = s.get_model();

        for (const auto & [name, var] : local_vars) {
            solution.variable_values[name] = fpa_to_float(solution.model.eval(var));
        }
    }

    return solution;
}

Component createSubComponent(const Component & original, const std::vector<size_t> & instructions_indices,
                            const std::vector<Instruction> & OpsSeq) {
    Component sub;
    sub.instruction_indices = instructions_indices;

    for (size_t idx : instructions_indices) {
        const auto & instr = OpsSeq[idx];
        sub.involved_regs.insert(instr.dest_reg);
        if (instr.op != Instruction::Ops::INIT) {
            sub.involved_regs.insert((instr.src_reg1));
            sub.involved_regs.insert(instr.src_reg2);
        }
    }

    std::unordered_set<int> written_in_sub;
    for (size_t idx : instructions_indices) {
        written_in_sub.insert(OpsSeq[idx].dest_reg);
    }

    for (int reg : sub.involved_regs) {
        if (written_in_sub.find(reg) == written_in_sub.end()) {
            sub.involved_regs.insert(reg);
        }
    }

    return sub;
}

void analyzeProblematicInstruction(const Instruction & instr, size_t idx) {
    std::cout << "Problematic instruction " << idx << ": ";

    if (instr.op == Instruction::Ops::DIV) {
        std::cout << "Division opeartion - potential division by zero\n";
        std::cout<< "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1 << "] / reg[" << instr.src_reg2 << "]\n";
        std::cout << "Suggestion: Check if reg[" << instr.src_reg2 << "] can be zero\n";
    } else {
        std::cout << "Unexpected UNSAT cause in arithmetic operation\n";
    }
}
void diagnozeUnsatComponent(const Component & comp, const std::vector<Instruction> & OpsSeq, unsigned seed) {
    std::cout << "Diagnosing UNSAT component with " << comp.instruction_indices.size() << " instructions\n";

    std::vector<size_t> sorted_indices = comp.instruction_indices;
    std::sort(sorted_indices.begin(), sorted_indices.end());

    size_t left = 0, right = sorted_indices.size();
    size_t problematic_start = 0;

    while (left < right) {
        size_t mid = (left + right) / 2;

        std::vector<size_t> prefix(sorted_indices.begin(), sorted_indices.begin() + mid);
        Component test_comp = createSubComponent(comp, prefix, OpsSeq);

        ComponentSolution test_sol = solveComponent(test_comp, OpsSeq, seed, false);

        if (test_sol.is_satisfiable) {
            left = mid + 1;
            problematic_start = mid;
        } else {
            right = mid;
        }
    }

    std::cout << "Problem starts at instruction " << sorted_indices[problematic_start] << "\n";

    const Instruction & problematic = OpsSeq[sorted_indices[problematic_start]];
    analyzeProblematicInstruction(problematic, sorted_indices[problematic_start]);
}

void presentResults(const std::vector<Component> & components,
                    const std::vector<ComponentSolution> & solutions,
                    const std::vector<Instruction> & OpsSeq,
                    bool show_intermediate) {
    std::unordered_map<std::string, float> global_values;

    for (size_t i = 0; i < components.size(); ++i) {
        const Component & comp = components[i];
        const ComponentSolution & sol = solutions[i];

        std::cout<<"\n=== Component " << i << "===\n";
        std::cout << "Instructions: ";
        for (size_t idx : comp.instruction_indices) {
            std:: cout << idx << " ";
        }
        std::cout << "\nRegisters: ";
        for (int reg : comp.involved_regs) {
            std::cout << reg << " ";
        }
        std::cout << "\n";

        if (sol.is_satisfiable) {
            std::cout << "Status: SAT\n";

            for (const auto & [var_name, value] : sol.variable_values) {
                global_values[var_name] = value;
            }
        } else {
            std::cout << "Status UNSAT\n";
        }
    }

    std::cout << "\n===Final Results ===\n";

    for (int reg = 0; reg < global_values.size(); ++reg) {
        float final_value = findFinalValue(reg, global_values, OpsSeq);
        std::cout << "reg[" << reg << "] = " << final_value << "\n";
    }
}

void solveRandomApply(const unsigned seed, const unsigned size, const unsigned regs, const bool intermediateResults, const bool soi, const bool sor) {
    auto getOpSymbol = [](const Instruction::Ops op) -> std::string {
        switch(op) {
            case Instruction::Ops::ADD: return "+";
            case Instruction::Ops::SUB: return "-";
            case Instruction::Ops::MUL: return "*";
            case Instruction::Ops::DIV: return "/";
            case Instruction::Ops::INIT: return "INIT";
            default: return "?";
        }
    };

    const std::vector<Instruction> OpsSeq = genSeq(size, regs, seed);

    DependencyAnalyzer analyzer;
    std::vector<Component> components = analyzer.analyze(OpsSeq, regs);

    std::cout << "Found " << components.size() << " independent components\n";

    if (soi) {
        std::cout<<"sequence of instructions:"<<std::endl;
        for (auto & instr : OpsSeq) {
            if (instr.op == Instruction::Ops::INIT) {
                std::cout << "reg[" << instr.dest_reg << "] = random_value"<<std::endl;
            } else {
                std::cout << "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1
                 << "] "<<getOpSymbol(instr.op)<<" reg[" << instr.src_reg2 << "]"
                << ")"<<std::endl;
            }
        }
        std::cout<<std::endl;
    }

    std::vector<ComponentSolution> solutions;
    for (unsigned i = 0; i < components.size(); ++i) {
        ComponentSolution sol = solveComponent(components[i], OpsSeq, seed + i, sor);
        solutions.push_back(sol);

        if (!sol.is_satisfiable) {
            std::cout << "Component " << i << " is UNSAT - analyzing...\n";
            diagnozeUnsatComponent(components[i], OpsSeq, seed + i);
        }
    }

    presentResults(components, solutions, OpsSeq, intermediateResults);
}