//
// Created by димасик on 31.07.2025.
//
#include "solveRandomApply.h"
#include "Instruction.h"
#include "genSeq.h"
#include "z3++.h"
#include <vector>
#include <iostream>
#include "fpa_to_float.h"
void solveRandomApply(const int seed, const int size, const int regs) {
    const std::vector<Instruction> OpsSeq = genSeq(size, regs);
    const std::string ops[] = {"ADD", "SUB", "MUL", "DIV", "INIT"};

    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", static_cast<unsigned>(seed));

    const z3::sort float32 = ctx.fpa_sort(8, 24);

    std::vector<z3::expr> registers;
    for (int idx = 0; idx < regs; ++idx) {
        std::string name = "reg_" + std::to_string(idx);
        z3::expr reg = ctx.constant(name.c_str(), float32);
        registers.push_back(reg);
    }

    for (auto& c : OpsSeq) {
        z3::solver s(ctx);
        s.set(p);
        z3::expr val = ctx.constant("someValue", float32);
        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, val)));
        switch(c.op) {
            case Instruction::Ops::ADD:
                s.add(val == registers[c.src_reg1] + registers[c.src_reg2]);
                std::cout << "reg[" << c.dest_reg << "] = reg["
                             << c.src_reg1 << "] + reg[" << c.src_reg2 << "]";
                break;
            case Instruction::Ops::SUB:
                s.add(val == registers[c.src_reg1] - registers[c.src_reg2]);
                std::cout << "reg[" << c.dest_reg << "] = reg["
                         << c.src_reg1 << "] - reg[" << c.src_reg2 << "]";
                break;
            case Instruction::Ops::MUL:
                s.add(val == registers[c.src_reg1] * registers[c.src_reg2]);

                break;
            case Instruction::Ops::DIV:
                s.add(val == registers[c.src_reg1] / registers[c.src_reg2]);
                break;
            case Instruction::Ops::INIT:
                z3::expr value = ctx.constant("someValue", float32);
                s.add(val == value);
                break;
        }
        if (s.check() == z3::sat) {
            z3::model m = s.get_model();
            std::cout << "Current register states:\n";
            for (int i = 0; i < regs; ++i) {
                z3::expr reg_val = m.eval(registers[i]);
                std::cout << "  reg[" << i << "] = " << fpa_to_float(reg_val) << "\n";
            }
        } else {
            std::cout << "Invalid operation sequence! No solution exists.\n";
            return;
        }
    }

    std::cout << "\nFinal register values:\n";
    z3::model m = s.get_model();
    for (int i = 0; i < regs; ++i) {
        z3::expr reg_val = m.eval(registers[i]);
        std::cout << "reg[" << i << "] = " << fpa_to_float(reg_val) << std::endl;
    }
}