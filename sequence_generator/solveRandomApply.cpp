#include "solveRandomApply.h"
#include "Instruction.h"
#include "genSeq.h"
#include "z3++.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "../common_add/fpa_to_float.h"
#include "DependencyAnalysis.h"
struct ComponentSolution {
    bool is_satisfiable = false;
    std::unordered_map<std::string, float> variable_values;

    std::unique_ptr<z3::context> ctx_ptr;
    std::unique_ptr<z3::model> model_ptr;

    ComponentSolution() :
        ctx_ptr(std::make_unique<z3::context>()),
        model_ptr(nullptr) {}
    void setModel(z3::model && model) {
        model_ptr = std::make_unique<z3::model>(std::move(model));
    }
    z3::context & getContext() const {
        return *ctx_ptr;
    }
    z3::model* getModel() const {
        return model_ptr.get();
    }
};

float findFinalValue(const int reg, const std::unordered_map<std::string, float> & values,
        const std::vector<Instruction> & OpsSeq) {

    int max_version = 0;
    for (const auto & instr : OpsSeq) {
        if (instr.dest_reg == reg) {
            max_version++;
        }
    }

    if (max_version > 0) {
        const std::string var_name = "reg_" + std::to_string(reg) + "_" + std::to_string(max_version);
        if (const auto it = values.find(var_name); it != values.end()) {
            return it->second;
        }
    }

    const std::string input_name = "reg_" + std::to_string(reg) + "_input";
    if (const auto it = values.find(input_name); it != values.end()) {
        return it->second;
    }

    return 0.0f;
}

ComponentSolution solveComponent(const Component& comp, const std::vector<Instruction> & OpsSeq,
                                unsigned regs, unsigned seed, bool show_constraints) {
    ComponentSolution solution;
    z3::context & ctx = solution.getContext();

    z3::params p(ctx);
    p.set("random_seed", seed);

    const z3::sort float32 = ctx.fpa_sort(8, 24);
    z3::solver s(ctx);
    s.set(p);

    std::unordered_map<std::string, z3::expr> local_vars;

    for (int reg : comp.input_regs) {
        std::string name = "reg_" + std::to_string(reg) + "_input";
        z3::expr var = ctx.constant(name.c_str(), float32);

        s.add(to_expr(ctx,  Z3_mk_fpa_is_normal(ctx, var)));

        z3::expr min_val = ctx.fpa_val(-100.0f);
        z3::expr max_val = ctx.fpa_val(100.0f);
        s.add(var >= min_val && var <= max_val);

        z3::expr small_pos = ctx.fpa_val(0.001f);
        z3::expr small_neg = ctx.fpa_val(-0.001f);
        s.add(var >= small_pos || var <= small_neg);

        local_vars.emplace(name, std::move(var));
    }

    std::unordered_map<int, int> global_versions;
    for (int i = 0; i < regs; ++i) {
        global_versions[i] = 0;
    }

    std::vector<std::unordered_map<int, int>> versions_at_instruction(OpsSeq.size());
    for (size_t global_idx = 0; global_idx < OpsSeq.size(); ++global_idx) {
        versions_at_instruction[global_idx] = global_versions;
        const auto & instr = OpsSeq[global_idx];
        global_versions[instr.dest_reg]++;
    }

    std::vector<size_t> sorted_indices = comp.instruction_indices;
    std::sort(sorted_indices.begin(), sorted_indices.end());

    std::unordered_set<std::string> needed_vars;

    for (size_t idx : sorted_indices) {
        if (idx >= OpsSeq.size()) continue;

        const auto & instr = OpsSeq[idx];
        const auto & versions_before = versions_at_instruction[idx];

        int result_version = versions_before.at(instr.dest_reg) + 1;
        std::string result_name = "reg_" + std::to_string(instr.dest_reg) + "_" + std::to_string(result_version);
        needed_vars.insert(result_name);

        if (instr.op != Instruction::Ops::INIT) {
            int src1_version = versions_before.at(instr.src_reg1);
            int src2_version = versions_before.at(instr.src_reg2);

            std::string src1_name = (src1_version > 0)
                ? "reg_" + std::to_string(instr.src_reg1) + "_" + std::to_string(src1_version)
                : "reg_" + std::to_string(instr.src_reg1) + "_input";

            std::string src2_name = (src2_version > 0)
                ? "reg_" + std::to_string(instr.src_reg2) + "_" + std::to_string(src2_version)
                : "reg_" + std::to_string(instr.src_reg2) + "_input";

            needed_vars.insert(src1_name);
            needed_vars.insert(src2_name);
        }
    }

    for (const std::string & var_name : needed_vars) {
        if (local_vars.find(var_name) == local_vars.end()) {
            z3::expr var = ctx.constant(var_name.c_str(), float32);
            s.add(z3::to_expr(ctx, Z3_mk_fpa_is_normal(ctx, var)));
            local_vars.emplace(var_name, std::move(var));
        }
    }

    for (size_t idx : sorted_indices) {

        if (idx >= OpsSeq.size()) {
            std::cerr << "Error: Instruction index " << idx << " out of bounds" << std::endl;
            return solution;
        }

        const auto & instr = OpsSeq[idx];
        const auto & versions_before = versions_at_instruction[idx];

        int result_version = versions_before.at(instr.dest_reg) + 1;
        std::string result_name = "reg_" + std::to_string(instr.dest_reg) + "_" + std::to_string(result_version);

        auto result_it = local_vars.find(result_name);
        if (result_it == local_vars.end()) {
            std::cerr << "Error: Result variable " << result_name << " not found" << std::endl;
            return solution;
        }
        z3::expr & result_ref = result_it->second;

        if (instr.op != Instruction::Ops::INIT) {
            int src1_version = versions_before.at(instr.src_reg1);
            int src2_version = versions_before.at(instr.src_reg2);

            std::string src1_name = (src1_version > 0)
                ? "reg_" + std::to_string(instr.src_reg1) + "_" + std::to_string(src1_version)
                : "reg_" + std::to_string(instr.src_reg1) + "_input";

            std::string src2_name = (src2_version > 0)
                ? "reg_" + std::to_string(instr.src_reg2) + "_" + std::to_string(src2_version)
                : "reg_" + std::to_string(instr.src_reg2) + "_input";

            auto it1 = local_vars.find(src1_name);
            auto it2 = local_vars.find(src2_name);

            if (it1 == local_vars.end()) {
                std::cerr << "Error: Variable " << src1_name << " not foud for instruction " << idx << std::endl;
                return solution;
            }

            if (it2 == local_vars.end()) {
                std::cerr << "Error: Variable " << src2_name << " not foud for instruction " << idx << std::endl;
                return solution;
            }

            z3::expr & src1 = it1->second;
            z3::expr & src2 = it2->second;

            switch (instr.op) {
                case Instruction::Ops::ADD:
                    s.add(result_ref == src1 + src2);
                break;
                case Instruction::Ops::SUB:
                    s.add(result_ref == src1 - src2);
                break;
                case Instruction::Ops::MUL:
                    s.add(result_ref == src1 * src2);
                break;
                case Instruction::Ops::DIV:
                    s.add(src2 != ctx.fpa_val(0.0f));
                s.add(result_ref == src1 / src2);
                break;
                default:
                    std::cerr << "Error: Unknown operation in instructions " << idx << std::endl;
                    return solution;
            }
        }
    }

    if (show_constraints) {
        std::cout << "Component constraints:\n" << s << "\n";
    }

    if (z3::check_result result = s.check(); result == z3::sat) {
        solution.is_satisfiable = true;
        solution.setModel(s.get_model());

        for (const auto & [name, var] : local_vars) {
            if (solution.getModel()) {
                solution.variable_values[name] = fpa_to_float(solution.getModel()->eval(var));
            }
        }
    } else if (result == z3::unsat) {
        solution.is_satisfiable = false;
        std::cout << "Component is UNSAT" << std::endl;
    } else {
        solution.is_satisfiable = false;
        std::cout << "Component solving returned UNKNOWN" << std::endl;
    }

    return solution;
}


Component createSubComponent(const Component & original, const std::vector<size_t> & instructions_indices,
                            const std::vector<Instruction> & OpsSeq) {
    Component sub;
    sub.instruction_indices = instructions_indices;

    for (const size_t idx : instructions_indices) {
        if (idx < OpsSeq.size()) {
            const auto & instr = OpsSeq[idx];
            sub.involved_regs.insert(instr.dest_reg);
            if (instr.op != Instruction::Ops::INIT) {
                sub.involved_regs.insert((instr.src_reg1));
                sub.involved_regs.insert(instr.src_reg2);
            }
        }
    }

    std::unordered_set<int> written_in_sub;
    for (const size_t idx : instructions_indices) {
        if (idx < OpsSeq.size()) {
            written_in_sub.insert(OpsSeq[idx].dest_reg);
        }
    }

    for (int reg : sub.involved_regs) {
        if (written_in_sub.find(reg) == written_in_sub.end()) {
            sub.input_regs.insert(reg);
        }
    }

    return sub;
}

void analyzeProblematicInstruction(const Instruction & instr, const size_t idx) {
    std::cout << "Problematic instruction " << idx << ": ";

    if (instr.op == Instruction::Ops::DIV) {
        std::cout << "Division operation - potential division by zero\n"
        << "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1 << "] / reg[" << instr.src_reg2 << "]\n"
        << "Suggestion: Check if reg[" << instr.src_reg2 << "] can be zero\n";
    } else {
        std::cout << "Unexpected UNSAT cause in arithmetic operation\n";
    }
}
void diagnozeUnsatComponent(const Component & comp, const std::vector<Instruction> & OpsSeq, const unsigned seed, const unsigned regs) {
    std::cout << "Diagnosing UNSAT component with " << comp.instruction_indices.size() << " instructions\n";

    std::vector<size_t> sorted_indices = comp.instruction_indices;
    std::sort(sorted_indices.begin(), sorted_indices.end());

    if (sorted_indices.empty()) return;

    size_t left = 0, right = sorted_indices.size();
    size_t problematic_start = 0;

    while (left < right) {
        const size_t mid = (left + right) / 2;

        std::vector prefix(sorted_indices.begin(), sorted_indices.begin() + mid);
        if (prefix.empty()) {
            left = mid + 1;
            continue;
        }

        Component test_comp = createSubComponent(comp, prefix, OpsSeq);

        if (const ComponentSolution test_sol = solveComponent(test_comp, OpsSeq, regs, seed, false); test_sol.is_satisfiable) {
            left = mid + 1;
            problematic_start = mid;
        } else {
            right = mid;
        }
    }

    if (problematic_start < sorted_indices.size()) {
        std::cout << "Problem starts at instruction " << sorted_indices[problematic_start] << "\n";
    }

    if (sorted_indices[problematic_start] < OpsSeq.size()) {
        const Instruction & problematic = OpsSeq[sorted_indices[problematic_start]];
        analyzeProblematicInstruction(problematic, sorted_indices[problematic_start]);
    }
}

void presentResults(const std::vector<Component> & components,
                    const std::vector<ComponentSolution> & solutions,
                    const std::vector<Instruction> & OpsSeq,
                    const unsigned regs_count,
                    const bool show_intermediate) {

    if (components.size() != solutions.size()) {
        std::cerr << "Error: Mismatch between components and solutions count" << std::endl;
        return;
    }

    std::unordered_map<std::string, float> global_values;

    for (size_t i = 0; i < components.size() && i < solutions.size(); ++i) {
        const Component & comp = components[i];
        const ComponentSolution & sol = solutions[i];

        std::cout<<"\n=== Component " << i << "===\n"
        << "Instructions: ";
        for (const size_t idx : comp.instruction_indices) {
            if (idx < OpsSeq.size()) {
                std:: cout << idx << " ";
            }
        }
        std::cout << "\nRegisters: ";
        for (const int reg : comp.involved_regs) {
            std::cout << reg << " ";
        }
        std::cout << "\n";

        if (sol.is_satisfiable) {
            std::cout << "Status: SAT\n";
            for (const auto & [var_name, value] : sol.variable_values) {
                global_values[var_name] = value;
                if (show_intermediate) {
                    std::cout << " " << var_name << " = " << value << "\n";
                }
            }
        } else {
            std::cout << "Status: UNSAT\n";
        }
    }

    std::cout << "\n=== Final Results ===\n";

    for (unsigned reg = 0; reg < regs_count; ++reg) {
        const float final_value = findFinalValue(static_cast<int> (reg), global_values, OpsSeq);
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

    std::cout << "Generating sequence with seed=" << seed
                << ", size=" <<size << ", regs=" << regs << std::endl;

    const std::vector<Instruction> OpsSeq = genSeq(size, regs, seed);

    std::cout << "Generated " << OpsSeq.size() << " instructions" << std::endl;

    for (size_t i = 0; i < OpsSeq.size(); ++i) {
        const auto & instr = OpsSeq[i];
        std::cout << "Instr " << i << ": dst=" << instr.dest_reg;
        if (instr.op != Instruction::Ops::INIT) {
            std::cout << ", src1=" << instr.src_reg1 << ", src2=" << instr.src_reg2;
        }
        std::cout << std::endl;

        if (instr.dest_reg < 0 || instr.dest_reg >= static_cast<int>(regs)) {
            std::cerr << "ERROR: Invalid dest_reg " << instr.dest_reg << std::endl;
            return;
        }
        if (instr.op != Instruction::Ops::INIT) {
            if (instr.src_reg1 < 0 || instr.src_reg1 >= static_cast<int>(regs) ||
                instr.src_reg2 < 0 || instr.src_reg2 >= static_cast<int>(regs)) {
                std::cerr << "ERROR: Invalid src regs " << instr.src_reg1 << ", " << instr.src_reg2 << std::endl;
                return;
                }
        }
    }

    DependencyAnalyzer analyzer;
    const std::vector<Component> components = analyzer.analyze(OpsSeq, regs);

    std::cout << "Found " << components.size() << " independent components\n";

    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Component " << i << " has " << components[i].nodes.size()
                    << " nodes and " << components[i].instruction_indices.size()
                    << " instructions" << std::endl;
    }
    if (soi) {
        std::cout<<"sequence of instructions:"<<std::endl;
        for (auto instr : OpsSeq) {
            if (instr.op == Instruction::Ops::INIT) {
                std::cout << "reg[" << instr.dest_reg << "] = random_value"<<std::endl;
            } else {
                std::cout << "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1
                 << "] "<< getOpSymbol(instr.op)<<" reg[" << instr.src_reg2 << "]"
                << std::endl;
            }
        }
        std::cout<<std::endl;
    }

    std::vector<ComponentSolution> solutions;

    solutions.reserve(components.size());
    for (size_t i = 0; i < components.size(); ++i) {
        ComponentSolution sol = solveComponent(components[i], OpsSeq, regs, seed + static_cast<unsigned> (i), sor);
        solutions.push_back(std::move(sol));

        if (!solutions.back().is_satisfiable) {
            std::cout << "Component " << i << " is UNSAT - analyzing...\n";
            diagnozeUnsatComponent(components[i], OpsSeq, seed + static_cast<unsigned>(i), regs);
        }
    }

    presentResults(components, solutions, OpsSeq, regs, intermediateResults);
}