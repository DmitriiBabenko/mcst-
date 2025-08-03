//
// Created by димасик on 30.07.2025.
//
#include <iostream>
#include "../addLimits.h"
#include "z3++.h"
void getOperations(const size_t times, z3::context & ctx, z3::params & p, z3::solver & s, z3::sort float32, const int size, std::vector<z3::expr> & regs) {

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

        addLimits(a_idx, b_idx, c_idx, opCode, ctx, val, result, op_solver, size);

        op_solver.add(a_idx >= 0 && a_idx < size);
        op_solver.add(b_idx >= 0 && b_idx < size);
        op_solver.add(c_idx >= 0 && c_idx < size);
        op_solver.add(opCode >= 0 && opCode < 5);
        op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, result)));
        op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, val)));

        z3::expr_vector all_conditions(ctx);



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
            s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, new_reg))); //  TODO

            regs[c_val] = new_reg; //
        } else {
            std::cout << "Op " << iteration << ": UNSAT - no valid operation found" << std::endl;
        }
    }
}