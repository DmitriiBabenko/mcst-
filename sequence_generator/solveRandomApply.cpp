#include "solveRandomApply.h"
#include "Componentsolution.h"
#include "Instruction.h"
#include "genSeq.h"
#include "generateComponents.h"
#include "z3++.h"
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../common_add/fpa_to_float.h"
#include "DependencyAnalysis.h"
#include "VerificationGenerator.h"
#include "Jsondiskcache.h" 
#include "Graph.h"

float findFinalValue(const unsigned reg, const std::unordered_map<std::string, float> & values,
        const std::vector<Instruction> & OpsSeq) {

    unsigned max_version = 0;
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

    for (const unsigned reg : comp.input_regs) {
        std::string name = "reg_" + std::to_string(reg) + "_input";
        z3::expr var = ctx.constant(name.c_str(), float32);

        s.add(to_expr(ctx,  Z3_mk_fpa_is_normal(ctx, var)));

        local_vars.emplace(name, std::move(var));
    }

    std::unordered_map<unsigned, unsigned> global_versions;
    for (unsigned i = 0; i < regs; ++i) {
        global_versions[i] = 0;
    }

    std::vector<std::unordered_map<unsigned, unsigned>> versions_at_instruction(OpsSeq.size());
    for (size_t global_idx = 0; global_idx < OpsSeq.size(); ++global_idx) {
        versions_at_instruction[global_idx] = global_versions;
        const auto & instr = OpsSeq[global_idx];
        global_versions[instr.dest_reg]++;
    }

    std::vector<unsigned> sorted_indices = comp.instruction_indices;
    std::sort(sorted_indices.begin(), sorted_indices.end());

    std::vector<std::string> needed_vars;

    for (size_t idx : sorted_indices) {
        if (idx >= OpsSeq.size()) continue;

        const auto & instr = OpsSeq[idx];
        const auto & versions_before = versions_at_instruction[idx];

        unsigned result_version = versions_before.at(instr.dest_reg) + 1;
        std::string result_name = "reg_" + std::to_string(instr.dest_reg) + "_" + std::to_string(result_version);
        needed_vars.push_back(result_name);

        if (instr.op != Ops::INIT) {
            unsigned src1_version = versions_before.at(instr.src_reg1);
            unsigned src2_version = versions_before.at(instr.src_reg2);

            std::string src1_name = (src1_version > 0)
                ? "reg_" + std::to_string(instr.src_reg1) + "_" + std::to_string(src1_version)
                : "reg_" + std::to_string(instr.src_reg1) + "_input";

            std::string src2_name = (src2_version > 0)
                ? "reg_" + std::to_string(instr.src_reg2) + "_" + std::to_string(src2_version)
                : "reg_" + std::to_string(instr.src_reg2) + "_input";

            needed_vars.push_back(src1_name);
            needed_vars.push_back(src2_name);
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

        assert (idx < OpsSeq.size());

        const auto & instr = OpsSeq[idx];
        const auto & versions_before = versions_at_instruction[idx];

        unsigned result_version = versions_before.at(instr.dest_reg) + 1;
        std::string result_name = "reg_" + std::to_string(instr.dest_reg) + "_" + std::to_string(result_version);

        auto result_it = local_vars.find(result_name);
        assert (result_it != local_vars.end());
        z3::expr & result_ref = result_it->second;

        s.add(result_ref >= ctx.fpa_val(-1000.0f));
        s.add(result_ref <= ctx.fpa_val(1000.0f));
        s.add(result_ref >= ctx.fpa_val(0.0001f) || result_ref <= ctx.fpa_val(-0.0001f));

        if (instr.op != Ops::INIT) {
            unsigned src1_version = versions_before.at(instr.src_reg1);
            unsigned src2_version = versions_before.at(instr.src_reg2);

            std::string src1_name = (src1_version > 0)
                ? "reg_" + std::to_string(instr.src_reg1) + "_" + std::to_string(src1_version)
                : "reg_" + std::to_string(instr.src_reg1) + "_input";

            std::string src2_name = (src2_version > 0)
                ? "reg_" + std::to_string(instr.src_reg2) + "_" + std::to_string(src2_version)
                : "reg_" + std::to_string(instr.src_reg2) + "_input";

            auto it1 = local_vars.find(src1_name);
            auto it2 = local_vars.find(src2_name);

            assert (it1 != local_vars.end());

            assert (it2 != local_vars.end());

            z3::expr & src1 = it1->second;
            z3::expr & src2 = it2->second;

            switch (instr.op) {
                case Ops::ADD:
                    s.add(result_ref == src1 + src2);
                break;
                case Ops::SUB:
                    s.add(result_ref == src1 - src2);
                break;
                case Ops::MUL:
                    s.add(result_ref == src1 * src2);
                break;
                case Ops::DIV:
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
                solution.variable_values[name] = fpa_to_float(solution.getModel().eval(var));
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


Component createSubComponent(const Component & original, const std::vector<unsigned> & instructions_indices,
                            const std::vector<Instruction> & OpsSeq) {
    Component sub;
    sub.instruction_indices = instructions_indices;

    for (const size_t idx : instructions_indices) {
        if (idx < OpsSeq.size()) {
            const auto & instr = OpsSeq[idx];
            sub.involved_regs.push_back(instr.dest_reg);
            if (instr.op != Ops::INIT) {
                sub.involved_regs.push_back(instr.src_reg1);
                sub.involved_regs.push_back(instr.src_reg2);
            }
        }
    }

    std::vector<unsigned> written_in_sub;
    for (const size_t idx : instructions_indices) {
        if (idx < OpsSeq.size()) {
            written_in_sub.push_back(OpsSeq[idx].dest_reg);
        }
    }

    for (unsigned reg : sub.involved_regs) {
        if ( std::find(written_in_sub.begin(), written_in_sub.end(), reg) == written_in_sub.end()) {
            sub.input_regs.push_back(reg);
        }
    }

    return sub;
}

void analyzeProblematicInstruction(const Instruction & instr, const size_t idx) {
    std::cout << "Problematic instruction " << idx << ": ";

    if (instr.op == Ops::DIV) {
        std::cout << "Division operation - potential division by zero\n"
        << "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1 << "] / reg[" << instr.src_reg2 << "]\n"
        << "Suggestion: Check if reg[" << instr.src_reg2 << "] can be zero\n";
    } else {
        std::cout << "Unexpected UNSAT cause in arithmetic operation\n";
    }
}
void diagnozeUnsatComponent(const Component & comp, const std::vector<Instruction> & OpsSeq, const unsigned seed, const unsigned regs) {
    std::cout << "Diagnosing UNSAT component with " << comp.instruction_indices.size() << " instructions\n";

    std::vector<unsigned> sorted_indices = comp.instruction_indices;
    std::sort(sorted_indices.begin(), sorted_indices.end());

    if (sorted_indices.empty()) return;

    size_t left = 0, right = sorted_indices.size();
    size_t problematic_start = 0;

    while (left < right) {
        const unsigned mid = (left + right) / 2;

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

    assert (components.size() == solutions.size());

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
        for (const unsigned reg : comp.involved_regs) {
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
        const float final_value = findFinalValue(reg, global_values, OpsSeq);
        std::cout << "reg[" << reg << "] = " << final_value << "\n";
    }
}
void generateAndRunVerification(const std::vector<Component>& components,
                              const std::vector<ComponentSolution>& solutions,
                              const std::vector<Instruction>& OpsSeq,
                              const unsigned regs_count,
                              const unsigned seed,
                              const std::string& verification_file) {

    std::cout << "\n=== Generating Verification Code ===\n";

    std::unordered_map<std::string, float> global_values;
    for (size_t i = 0; i < components.size() && i < solutions.size(); ++i) {
        const ComponentSolution& sol = solutions[i];
        if (sol.is_satisfiable) {
            for (const auto& [var_name, value] : sol.variable_values) {
                global_values[var_name] = value;
            }
        }
    }

    bool success = VerificationGenerator::generateVerificationCode(
        OpsSeq, global_values, components, regs_count, seed);

    if (!success) {
        std::cerr << "Failed to generate verification file: " << verification_file << std::endl;
        return;
    }

    const std::string cpp_file = "seed_" + std::to_string(seed) + "_num registers_" + std::to_string(regs_count) + ".cpp";
    const std::string exe_file = "seed_" + std::to_string(seed) + "_num_registers_" + std::to_string(regs_count) + ".exe";

    std::cout << "Generated verification file: " << cpp_file << '\n';

    const std::string compile_cmd = "g++ -o \"" + exe_file + "\" \"" + cpp_file + "\"";
    std::cout << "Compiling verification code...\n";

    if (const int compile_result = std::system(compile_cmd.c_str()); compile_result == 0) {
        std::cout << "Compilation successful: " << exe_file << "\n=== Running Verification ===\n";
        const std::string run_cmd = "\"" + exe_file + "\"";
        std::system(run_cmd.c_str());
    } else {
        std::cerr << "Compilation failed for " << cpp_file << '\n';
    }
}
void print_graph(std::vector<Graph> & components) {
    std::cout << "Generated " << components.size() << " independent components\n";
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        std::cout <<"=== Component " << components[idx].getId() <<" ===\n";
        for (std::size_t ind = 0; ind < components[idx].getNodes().size(); ++ind) {
            std::cout << "node " << components[idx].getNodes()[ind]->getId() << '\n';
            std::cout << "    incoming nodes: ";
            for (const auto & c : components[idx].getNodes()[ind]->getInc()) {
                std::cout << c->getId() << ' ';
            }
            if (components[idx].getNodes()[ind]->getInc().size() == 0) {
                std::cout << '-';
            }
            std::cout <<'\n';
            std::cout << "    outgoing nodes: ";
            for (const auto & c : components[idx].getNodes()[ind]->getOut()) {
                std::cout << c->getId() << ' ';
            }
            if (components[idx].getNodes()[ind]->getOut().size() == 0) {
                std::cout << '-';
            }
            std::cout << '\n';
        }
    }
}
void solveRandomApply(const unsigned seed, const unsigned size, const unsigned regs, const unsigned comps, const bool intermediateResults, const bool soi, const bool sor) {
    assert(regs >= size / (comps - 1));

    auto getOpSymbol = [](const Ops op) -> std::string {
        switch(op) {
            case Ops::ADD: return "+";
            case Ops::SUB: return "-";
            case Ops::MUL: return "*";
            case Ops::DIV: return "/";
            case Ops::INIT: return "INIT";
            default: return "?";
        }
    };

    std::mt19937 gen(seed);
    std::cout << "Generating sequence with seed=" << seed
                << ", size=" <<size << ", regs=" << regs << ", components=" << comps <<'\n';

    std::vector<Graph> components_;
    components_.reserve(comps);
    const unsigned component_size = size / comps;
    unsigned rest = size - component_size * comps;
    for (std::size_t idx = 0 ; idx < comps; ++idx, rest ^= rest) {
        components_.push_back(Graph(seed, component_size + rest, 2, idx));
        components_[idx].build(gen);
    }
    print_graph(components_);
    const std::vector<std::vector<AbstractOp>> OpsComponents = gen_component(size, seed, comps);
    const std::vector<Instruction> OpsSeq = genSeq(regs, seed, OpsComponents);

    std::cout << "Generated " << OpsSeq.size() << " instructions" << std::endl;

    for (size_t i = 0; i < OpsSeq.size(); ++i) {
        const auto & instr = OpsSeq[i];
        std::cout << "Instr " << i << ": dst=" << instr.dest_reg;
        if (instr.op != Ops::INIT) {
            std::cout << ", src1=" << instr.src_reg1 << ", src2=" << instr.src_reg2;
        }
        std::cout << std::endl;

        assert (instr.dest_reg < regs);
        if (instr.op != Ops::INIT) {
            assert(instr.src_reg1 < regs && instr.src_reg2 < regs);
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
        for (const auto instr : OpsSeq) {
            if (instr.op == Ops::INIT) {
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

    if (!tryloadfromcache(seed, size, regs, comps, solutions)) {
        std::cout << "generating solutions...\n";
        solutions.reserve(components.size());
        for (unsigned i = 0; i < components.size(); ++i) {
            ComponentSolution sol = solveComponent(components[i], OpsSeq, regs, seed + i, sor);
            solutions.push_back(std::move(sol));

            if (!solutions.back().is_satisfiable) {
                std::cout << "Component " << i << " is UNSAT - analyzing...\n";
                diagnozeUnsatComponent(components[i], OpsSeq, seed + i, regs);
            }
        }
        cachesolutions(seed, size, regs, comps, solutions);
    } else {
        std::cout << "===loaded solutions from cache===\n";
    }

    presentResults(components, solutions, OpsSeq, regs, intermediateResults);
    

    generateAndRunVerification(components, solutions, OpsSeq, regs, seed, "seed_" + std::to_string(seed) + "_num_registers_" + std::to_string(regs));
}