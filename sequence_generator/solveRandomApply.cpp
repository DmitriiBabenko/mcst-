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
#include <map>

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

std::string var_name(const Graph & graph, const std::shared_ptr<Node> & node) {
    return std::to_string(graph.getId()) + '_' + std::to_string(node->getId());
}

void add_var_to_dependetns(const Graph & graph, std::map<std::string, z3::expr_vector> & name_to_sources, const std::shared_ptr<Node> & node, z3::context & ctx, const z3::expr & var) {
    for (auto & dependent_node : node->getOut()) {
        std::string name = var_name(graph, dependent_node);
        auto it = name_to_sources.find(name);
        if (it == name_to_sources.end()) {
            it = name_to_sources.emplace(name, z3::expr_vector(ctx)).first;
        }
        it->second.push_back(var);
    }
}

ComponentSolution generate_subsystem_of_restrictions(const Graph & graph,
                                unsigned seed, bool show_constraints) {
    ComponentSolution solution;
    z3::context & ctx = solution.getContext();
    std::map<std::string, z3::expr_vector> name_to_sources;

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
        const std::shared_ptr<Node> & cur_node = graph.getNodes()[ind];
        std::string name = var_name(graph, cur_node);
        z3::expr var = ctx.constant(name.c_str(), float32);

        z3::expr result (ctx);
        if (cur_node->getOp() != Ops::INIT) {
            z3::expr_vector src_exprs(ctx);
            for (const auto & inc_node : cur_node->getInc()) {
                std::string src_name = var_name(graph, inc_node);
                src_exprs.push_back(solution.local_vars.at(src_name));
            }

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
                    std::cerr << "Error: Unknown operation in instructions " << name << std::endl;
                    return solution;
            }
            add_tracker(result == var, name + "_def");
        }

        add_tracker(var >= ctx.fpa_val(-1000.0f), name + "_lb");
        add_tracker(var <= ctx.fpa_val(1000.0f), name + "_ub");
        add_tracker(var >= ctx.fpa_val(0.0001f) || var <= ctx.fpa_val(-0.0001f), name + "_nonzero");
        add_tracker(z3::to_expr(ctx, Z3_mk_fpa_is_normal(ctx, var)), name + "_normal");

        solution.local_vars.emplace(name, var);
    }

    if (show_constraints) {
         std::cout << "\n=====System of restrictions in component № " <<graph.getId() <<"=====\n"<< s << "\n";
    }
    solution.setSolver(std::move(s));
    return solution;
}

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

void apply_cached_values(std::vector<Graph> & components, const std::vector<ComponentSolution> & solutions, const bool log) {
    std::size_t comp_num = 0;
    for (const auto & solution : solutions) {
        if (log) {
            std::cout << "\nComponent № " << comp_num++ << " is ";
        }
        if (!solution.is_satisfiable) {
            if (log) {
                std::cout << "UNSAT\n";
            }
            continue;
        }

        if (log) {
            std::cout << "SAT\n";
        }
        
        for (const auto & [name, value] : solution.variable_values) {
            auto [cmd_id, nd_id] = parse_pair(name);
            components[cmd_id].getNodes()[nd_id]->setValue(value);
            if (log) {
                std::cout << name <<"  ==  "<< value << '\n';  
            }
        }
    }
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

    solutions.reserve(components.size());
    for (unsigned i = 0; i < components.size(); ++i) {
        ComponentSolution sol = generate_subsystem_of_restrictions(components[i], seed + i, sor);
        solutions.push_back(std::move(sol));
    }

    return solutions;
}

void solve_system(std::vector<Graph> & components, std::vector<ComponentSolution> & system_of_restrictions, const bool log) {
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        if (log) {
            std::cout << "\nComponent № " << idx << " is ";
        }
        ComponentSolution & solution = system_of_restrictions[idx];
        z3::solver & solver = solution.getSolver();
        if (z3::check_result result = solver.check(); result == z3::sat) {
            if (log) {
                std::cout << "SAT\n";
            }
            solution.is_satisfiable = true;
            solution.setModel(solver.get_model());
             for (const auto & [name, var] : solution.local_vars) {
                auto [cmp_id, nd_id] = parse_pair(name);
                float value = fpa_to_float(solution.getModel().eval(var));
                components[cmp_id].getNodes()[nd_id]->setValue(value);
                solution.variable_values[name] = value;
                if (log) {
                    std::cout << name <<"  ==  "<< value << '\n';  
                }
             }
        } else if (result == z3::unsat) {
            solution.is_satisfiable = false;
            if (log) {
                std::cout << "UNSAT, core:\n";
            }
            z3::expr_vector core = solver.unsat_core();
            if (log) {
                for (unsigned i = 0; i < core.size(); ++i) {
                    std::cout << " " << core[i] << '\n';
                }
            }
        } else {
            solution.is_satisfiable = false;
            if (log) {
                std::cout << "UNKNOWN\n";
            }
        }
    }
}

std::vector<std::shared_ptr<Node>> build_secuense_nodes(std::vector<Graph> & components, const unsigned seed, const bool log) {
    if (log) {
        std::cout << "===top. sorted nodes===\n";
    }
    std::vector<std::shared_ptr<Node>> result_secuense;
    for (std::size_t idx = 0; idx < components.size(); ++idx) {
        std::vector<std::shared_ptr<Node>> nodes = components[idx].getNodes();
        for (std::size_t ind = 0; ind < nodes.size(); ++ind) {
            if (log) {
                std::cout << '\n' << components[idx].getId() << "_" << nodes[ind]->getId() << '\n';
            }
            result_secuense.push_back(nodes[ind]);
        }
    }
    return result_secuense;
}