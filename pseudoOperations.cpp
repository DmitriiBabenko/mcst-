//
// Created by димасик on 14.07.2025.
//
/*
Blessed is the mind too small for doubt.
Holy is the machine, sacred is its function.
Praise the Omnissiah, whose will is manifest in gears and circuits.
Let the machine spirits be appeased, and the rites of ignition observed.
For the Machine God watches, and his judgment is precise
.*/
// В pseudoOperations.cpp
#include "z3++.h"
#include "fpa_to_float.h"
#include <vector>
#include <iostream>
void pseudoOperations(const unsigned seed, const int size, const size_t times) {
    std::cout<<"please, stand by"<<std::endl;
    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", seed);

    const z3::sort float32 = ctx.fpa_sort(8, 24);
    z3::solver s(ctx);
    s.set(p);

    std::vector<z3::expr> regs;
    for (int idx = 0; idx < size; ++idx) {
        std::string name = "reg_" + std::to_string(idx);
        z3::expr reg = ctx.constant(name.c_str(), float32);
        regs.push_back(reg);

        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, reg)));
    }

    for (size_t iteration = 0; iteration < times; ++iteration) {
        z3::solver op_solver(ctx);
        op_solver.set(p);

        z3::expr_vector current_constraints = s.assertions();
        for (unsigned i = 0; i < current_constraints.size(); ++i) {
            op_solver.add(current_constraints[i]);
        }

        std::string a_name = "a_" + std::to_string(iteration);
        std::string b_name = "b_" + std::to_string(iteration);
        std::string c_name = "c_" + std::to_string(iteration);
        std::string result_name = "result_" + std::to_string(iteration);
        std::string val_name = "val_" + std::to_string(iteration);
        std::string op_name = "op_" + std::to_string(iteration);

        z3::expr a_idx = ctx.int_const(a_name.c_str());
        z3::expr b_idx = ctx.int_const(b_name.c_str());
        z3::expr c_idx = ctx.int_const(c_name.c_str());
        z3::expr result = ctx.constant(result_name.c_str(), float32);
        z3::expr val = ctx.constant(val_name.c_str(), float32);
        z3::expr opCode = ctx.int_const(op_name.c_str());

        // Ограничиваем индексы
        op_solver.add(a_idx >= 0 && a_idx < size);
        op_solver.add(b_idx >= 0 && b_idx < size);
        op_solver.add(c_idx >= 0 && c_idx < size);
        op_solver.add(opCode >= 0 && opCode < 5);

        op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, result)));
        op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, val)));

        z3::expr_vector all_conditions(ctx);

        for (int a = 0; a < size; ++a) {
            for (int b = 0; b < size; ++b) {
                for (int c = 0; c < size; ++c) {
                    z3::expr indices_match = (a_idx == a) && (b_idx == b) && (c_idx == c);

                    z3::expr reg_a = regs[a];
                    z3::expr reg_b = regs[b];

                    z3::expr operations =
                        (opCode == 0 && result == reg_a + reg_b) ||
                        (opCode == 1 && result == reg_a - reg_b) ||
                        (opCode == 2 && result == reg_a * reg_b) ||
                        (opCode == 3 && result == reg_a / reg_b) ||
                        (opCode == 4 && result == val);

                    all_conditions.push_back(implies(indices_match, operations));
                }
            }
        }

        for (unsigned i = 0; i < all_conditions.size(); ++i) {
            op_solver.add(all_conditions[i]);
        }

        if (op_solver.check() == z3::sat) {
            z3::model m = op_solver.get_model();

            int a_val = m.eval(a_idx).get_numeral_int();
            int b_val = m.eval(b_idx).get_numeral_int();
            int c_val = m.eval(c_idx).get_numeral_int();
            int op_val = m.eval(opCode).get_numeral_int();
            z3::expr result_val = m.eval(result);

            std::cout << "Op " << iteration << ": reg[" << c_val << "] = ";

            const char* op_names[] = {"+", "-", "*", "/", "rand"};
            if (op_val < 5) {
                if (op_val == 4) {
                    std::cout << "random_value";
                } else {
                    std::cout << "reg[" << a_val << "] " << op_names[op_val] << " reg[" << b_val << "]";
                }
            }
            std::cout << std::endl;

            std::string new_reg_name = "reg_" + std::to_string(c_val) + "_iter" + std::to_string(iteration);
            z3::expr new_reg = ctx.constant(new_reg_name.c_str(), float32);

            s.add(new_reg == result_val);
            s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, new_reg)));

            regs[c_val] = new_reg;
        } else {
            std::cout << "Op " << iteration << ": UNSAT - no valid operation found" << std::endl;
        }
    }

    std::cout << "\nFinal values:" << std::endl;
    if (s.check() == z3::sat) {
        z3::model final_model = s.get_model();
        for (int i = 0; i < size; ++i) {
            z3::expr reg_val = final_model.eval(regs[i]);
            std::cout << "reg[" << i << "] = " << fpa_to_float(reg_val) << std::endl;
        }
    } else {
        std::cout << "Final state is UNSAT" << std::endl;
    }
}
/*
*Final values:
reg[0] = 3.85192e-34
reg[1] = -1.00012
reg[2] = 1.17549e-38
reg[3] = 1.17564e-38
reg[4] = 4.77086e-07
 */