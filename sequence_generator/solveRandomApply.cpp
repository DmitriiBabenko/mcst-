#include "solveRandomApply.h"
#include "ComponentSolution.h"
#include "z3++.h"
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../common_add/fpa_to_float.h"
#include "VerificationGenerator.h"
#include "Jsondiskcache.h" 
#include "Graph.h"

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
//-----------------------------------------------------------------------
// float findFinalValue(const unsigned reg, const std::unordered_map<std::string, float> & values,
//         const std::vector<Instruction> & OpsSeq) {

//     unsigned max_version = 0;
//     for (const auto & instr : OpsSeq) {
//         if (instr.dest_reg == reg) {
//             max_version++;
//         }
//     }

//     if (max_version > 0) {
//         const std::string var_name = "reg_" + std::to_string(reg) + "_" + std::to_string(max_version);
//         if (const auto it = values.find(var_name); it != values.end()) {
//             return it->second;
//         }
//     }

//     const std::string input_name = "reg_" + std::to_string(reg) + "_input";
//     if (const auto it = values.find(input_name); it != values.end()) {
//         return it->second;
//     }

//     return 0.0f;
// }

ComponentSolution generate_subsystem_of_restrictions(const Graph & graph,
                                unsigned seed, bool show_constraints) {
    ComponentSolution solution;
    z3::context & ctx = solution.getContext();

    z3::params p(ctx);
    p.set("random_seed", seed);
    p.set("unsat_core", true);

    const z3::sort float32 = ctx.fpa_sort(8, 24);
    z3::solver s(ctx);
    s.set(p);

    unsigned tracker_id = 0;
    auto add_tracker = [&](z3::expr constraint, const std::string & label) {
        z3::expr tracker = ctx.bool_const((label + "_" + std::to_string(tracker_id++)).c_str());
        s.add(constraint, tracker);
    };

    for (std::size_t ind = 0; ind < graph.getNodes().size(); ++ind) {
        std::string var_name = std::to_string(graph.getId()) + '_' + std::to_string(graph.getNodes()[ind]->getId());
        z3::expr var = ctx.constant(var_name.c_str(), float32);

        if (graph.getNodes()[ind]->getOp() == Ops::INIT) {
            add_tracker(z3::to_expr(ctx, Z3_mk_fpa_is_normal(ctx, var)), var_name + "_normal");
        } else {
            add_tracker(var >= ctx.fpa_val(-1000.0f), var_name + "_lb");
            add_tracker(var <= ctx.fpa_val(1000.0f), var_name + "_ub");
            add_tracker(var >= ctx.fpa_val(0.0001f) || var <= ctx.fpa_val(-0.0001f), var_name + "_nonzero");

            z3::expr_vector src_exprs(ctx);

            for (std::size_t idx = 0; idx < graph.getNodes()[ind]->getInc().size(); ++idx) {
                const Node * node = graph.getNodes()[ind]->getInc()[idx];
                std::string src_name = std::to_string(graph.getId()) + '_' + std::to_string(node->getId());
                z3::expr & src_expr = solution.local_vars.at(src_name);
                src_exprs.push_back(src_expr);
            }

            z3::expr result(ctx);
            switch (graph.getNodes()[ind]->getOp()) {
                case Ops::ADD:
                    result = src_exprs[0];
                    for (std::size_t i = 1; i < src_exprs.size(); ++i) {
                        result = result + src_exprs[i];
                    }
                break;
                case Ops::SUB:
                    result = src_exprs[0];
                    for (std::size_t i = 1; i < src_exprs.size(); ++i) {
                        result = result - src_exprs[i];
                    }
                break;
                case Ops::MUL:
                    result = src_exprs[0];
                    for (std::size_t i = 1; i < src_exprs.size(); ++i) {
                        result = result * src_exprs[i];
                    }
                break;
                case Ops::DIV:
                    result = src_exprs[0];
                    for (std::size_t i = 1; i < src_exprs.size(); ++i) {
                        s.add(src_exprs[i] != ctx.fpa_val(0.0f));
                        result = result / src_exprs[i];
                    }
                break;
                default:
                    std::cerr << "Error: Unknown operation in instructions " << var_name << std::endl;
                    return solution;
            }
            add_tracker(result == var, var_name + "_def");
        }

        solution.local_vars.emplace(var_name, var);
    }

    if (show_constraints) {
         std::cout << "\n=====System of restrictions in component № " <<graph.getId() <<"=====\n"<< s << "\n";
    }

    // if (z3::check_result result = s.check(); result == z3::sat) {
    //     solution.is_satisfiable = true;
    //     solution.setModel(s.get_model());

    //     for (const auto & [name, var] : local_vars) {
    //         if (solution.getModel()) {
    //             solution.variable_values[name] = fpa_to_float(solution.getModel().eval(var));
    //         }
    //     }
    // } else if (result == z3::unsat) {
    //     solution.is_satisfiable = false;
    //     std::cout << "Component is UNSAT" << std::endl;
    // } else {
    //     solution.is_satisfiable = false;
    //     std::cout << "Component solving returned UNKNOWN" << std::endl;
    // }
    solution.setSolver(std::move(s));
    return solution;
}

//-----------------------------------------------------------------------
// Component createSubComponent(const Component & original, const std::vector<unsigned> & instructions_indices,
//                             const std::vector<Instruction> & OpsSeq) {
//     Component sub;
//     sub.instruction_indices = instructions_indices;

//     for (const size_t idx : instructions_indices) {
//         if (idx < OpsSeq.size()) {
//             const auto & instr = OpsSeq[idx];
//             sub.involved_regs.push_back(instr.dest_reg);
//             if (instr.op != Ops::INIT) {
//                 sub.involved_regs.push_back(instr.src_reg1);
//                 sub.involved_regs.push_back(instr.src_reg2);
//             }
//         }
//     }

//     std::vector<unsigned> written_in_sub;
//     for (const size_t idx : instructions_indices) {
//         if (idx < OpsSeq.size()) {
//             written_in_sub.push_back(OpsSeq[idx].dest_reg);
//         }
//     }

//     for (unsigned reg : sub.involved_regs) {
//         if ( std::find(written_in_sub.begin(), written_in_sub.end(), reg) == written_in_sub.end()) {
//             sub.input_regs.push_back(reg);
//         }
//     }

//     return sub;
// }
//-----------------------------------------------------------------------
// void analyzeProblematicInstruction(const Instruction & instr, const size_t idx) {
//     std::cout << "Problematic instruction " << idx << ": ";

//     if (instr.op == Ops::DIV) {
//         std::cout << "Division operation - potential division by zero\n"
//         << "reg[" << instr.dest_reg << "] = reg[" << instr.src_reg1 << "] / reg[" << instr.src_reg2 << "]\n"
//         << "Suggestion: Check if reg[" << instr.src_reg2 << "] can be zero\n";
//     } else {
//         std::cout << "Unexpected UNSAT cause in arithmetic operation\n";
//     }
// }
//-----------------------------------------------------------------------
// void diagnozeUnsatComponent(const Component & comp, const std::vector<Instruction> & OpsSeq, const unsigned seed, const unsigned regs) {
//     std::cout << "Diagnosing UNSAT component with " << comp.instruction_indices.size() << " instructions\n";

//     std::vector<unsigned> sorted_indices = comp.instruction_indices;
//     std::sort(sorted_indices.begin(), sorted_indices.end());

//     if (sorted_indices.empty()) return;

//     size_t left = 0, right = sorted_indices.size();
//     size_t problematic_start = 0;

//     while (left < right) {
//         const unsigned mid = (left + right) / 2;

//         std::vector prefix(sorted_indices.begin(), sorted_indices.begin() + mid);
//         if (prefix.empty()) {
//             left = mid + 1;
//             continue;
//         }

//         Component test_comp = createSubComponent(comp, prefix, OpsSeq);

//         if (const ComponentSolution test_sol = solveComponent(test_comp, OpsSeq, regs, seed, false); test_sol.is_satisfiable) {
//             left = mid + 1;
//             problematic_start = mid;
//         } else {
//             right = mid;
//         }
//     }

//     if (problematic_start < sorted_indices.size()) {
//         std::cout << "Problem starts at instruction " << sorted_indices[problematic_start] << "\n";
//     }

//     if (sorted_indices[problematic_start] < OpsSeq.size()) {
//         const Instruction & problematic = OpsSeq[sorted_indices[problematic_start]];
//         analyzeProblematicInstruction(problematic, sorted_indices[problematic_start]);
//     }
// }
//-----------------------------------------------------------------------
// void presentResults(const std::vector<Component> & components,
//                     const std::vector<ComponentSolution> & solutions,
//                     const std::vector<Instruction> & OpsSeq,
//                     const unsigned regs_count,
//                     const bool show_intermediate) {

//     assert (components.size() == solutions.size());

//     std::unordered_map<std::string, float> global_values;

//     for (size_t i = 0; i < components.size() && i < solutions.size(); ++i) {
//         const Component & comp = components[i];
//         const ComponentSolution & sol = solutions[i];

//         std::cout<<"\n=== Component " << i << "===\n"
//         << "Instructions: ";
//         for (const size_t idx : comp.instruction_indices) {
//             if (idx < OpsSeq.size()) {
//                 std:: cout << idx << " ";
//             }
//         }
//         std::cout << "\nRegisters: ";
//         for (const unsigned reg : comp.involved_regs) {
//             std::cout << reg << " ";
//         }
//         std::cout << "\n";

//         if (sol.is_satisfiable) {
//             std::cout << "Status: SAT\n";
//             for (const auto & [var_name, value] : sol.variable_values) {
//                 global_values[var_name] = value;
//                 if (show_intermediate) {
//                     std::cout << " " << var_name << " = " << value << "\n";
//                 }
//             }
//         } else {
//             std::cout << "Status: UNSAT\n";
//         }
//     }

//     std::cout << "\n=== Final Results ===\n";

//     for (unsigned reg = 0; reg < regs_count; ++reg) {
//         const float final_value = findFinalValue(reg, global_values, OpsSeq);
//         std::cout << "reg[" << reg << "] = " << final_value << "\n";
//     }
// }
//--------------------------------------------------------------------------
// void generateAndRunVerification(const std::vector<Component>& components,
//                               const std::vector<ComponentSolution>& solutions,
//                               const std::vector<Instruction>& OpsSeq,
//                               const unsigned regs_count,
//                               const unsigned seed,
//                               const std::string& verification_file) {

//     std::cout << "\n=== Generating Verification Code ===\n";

//     std::unordered_map<std::string, float> global_values;
//     for (size_t i = 0; i < components.size() && i < solutions.size(); ++i) {
//         const ComponentSolution& sol = solutions[i];
//         if (sol.is_satisfiable) {
//             for (const auto& [var_name, value] : sol.variable_values) {
//                 global_values[var_name] = value;
//             }
//         }
//     }

//     bool success = VerificationGenerator::generateVerificationCode(
//         OpsSeq, global_values, components, regs_count, seed);

//     if (!success) {
//         std::cerr << "Failed to generate verification file: " << verification_file << std::endl;
//         return;
//     }

//     const std::string cpp_file = "seed_" + std::to_string(seed) + "_num registers_" + std::to_string(regs_count) + ".cpp";
//     const std::string exe_file = "seed_" + std::to_string(seed) + "_num_registers_" + std::to_string(regs_count);

//     std::cout << "Generated verification file: " << cpp_file << '\n';

//     const std::string compile_cmd = "g++ -o \"" + exe_file + "\" \"" + cpp_file + "\"";
//     std::cout << "Compiling verification code...\n";

//     if (const int compile_result = std::system(compile_cmd.c_str()); compile_result == 0) {
//         std::cout << "Compilation successful: " << exe_file << "\n=== Running Verification ===\n";
//         const std::string run_cmd = "./\"" + exe_file + "\"";
//         std::system(run_cmd.c_str());
//     } else {
//         std::cerr << "Compilation failed for " << cpp_file << '\n';
//     }
// }
//-----------------------------------------------------------------------
void print_graph(std::vector<Graph> & components) {
    std::cout << "Generated " << components.size() << " independent components\n";
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        std::cout <<"=== Component " << components[idx].getId() <<" ===\n";
        for (std::size_t ind = 0; ind < components[idx].getNodes().size(); ++ind) {
            std::cout << "node " << components[idx].getId() << "_" << components[idx].getNodes()[ind]->getId() << "     |";
            std::cout << getOpSymbol(components[idx].getNodes()[ind]->getOp()) << '|';
            std::cout << "    incoming nodes: ";
            for (const auto & c : components[idx].getNodes()[ind]->getInc()) {
                std::cout << components[idx].getId() << "_" << c->getId() << ' ';
            }
            if (components[idx].getNodes()[ind]->getInc().size() == 0) {
                std::cout << '-';
            }
            std::cout <<"   |";
            std::cout << "    outgoing nodes: ";
            for (const auto & c : components[idx].getNodes()[ind]->getOut()) {
                std::cout << components[idx].getId() << "_" << c->getId() << ' ';
            }
            if (components[idx].getNodes()[ind]->getOut().size() == 0) {
                std::cout << '-';
            }
            std::cout << '\n';
        }
    }
}

std::pair<std::size_t, std::size_t> parse_pair(const std::string & s) {
    std::size_t pos = s.find('_');
    std::size_t first = std::stoull(s.substr(0, pos));
    std::size_t second = std::stoull(s.substr(pos + 1));
    return {first, second};
}

std::vector<Graph> generate_sequense(const unsigned seed, const unsigned size, const unsigned comps, const bool soi) {
    std::mt19937 gen(seed);

    std::vector<Graph> components;
    components.reserve(comps);
    const unsigned component_size = size / comps;
    unsigned rest = size - component_size * comps;
    for (std::size_t idx = 0 ; idx < comps; ++idx, rest ^= rest) {
        components.push_back(Graph(seed, component_size + rest, 2, idx));
        components[idx].build(gen);
    }

    if (soi) {
        print_graph(components);
    }

    return components;
}

std::vector<ComponentSolution> generate_system_of_restrictions(std::vector<Graph> & components, const unsigned seed, const bool sor) {
    std::vector<ComponentSolution> solutions;

    std::cout << "\ngenerating system of restrictions...\n";
    solutions.reserve(components.size());
    for (unsigned i = 0; i < components.size(); ++i) {
        ComponentSolution sol = generate_subsystem_of_restrictions(components[i], seed + i, sor);
        solutions.push_back(std::move(sol));
    }

    return solutions;
}

void solve_system(std::vector<Graph> & components, std::vector<ComponentSolution> & system_of_restrictions) {
    std::cout << "\nsolving system of restrictions...\n";
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        std::cout << "\nComponent № " << idx << " is ";
        ComponentSolution & solution = system_of_restrictions[idx];
        z3::solver & solver = solution.getSolver();
        if (z3::check_result result = solver.check(); result == z3::sat) {
            std::cout << "SAT\n";
            solution.setModel(solver.get_model());
             for (const auto & [name, var] : solution.local_vars) {
                auto [cmp_id, nd_id] = parse_pair(name);
                float value = fpa_to_float(solution.getModel().eval(var));
                components[cmp_id].getNodes()[nd_id]->setValue(value);
                std::cout << name <<"  ==  "<< value << '\n';  
             }
        } else if (result == z3::unsat) {
            solution.is_satisfiable = false;
            std::cout << "UNSAT, core:\n";
            z3::expr_vector core = solver.unsat_core();
            for (unsigned i = 0; i < core.size(); ++i) {
                std::cout << " " << core[i] << '\n';
            }
        } else {
            solution.is_satisfiable = false;
            std::cout << "UNKNOWN\n";
        }
    }
}