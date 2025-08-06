//
// Created by димасик on 31.07.2025.
//
#include "solveRandomApply.h"
#include "Instruction.h"
#include "genSeq.h"
#include "z3++.h"
#include <vector>
#include <iostream>
#include "../common_add/fpa_to_float.h"
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

    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", seed);

    const z3::sort float32 = ctx.fpa_sort(8, 24);
    z3::solver s(ctx);
    s.set(p);

    std::vector<std::vector<z3::expr>> registers;
    for (size_t idx = 0; idx < regs; ++idx) {
        std::string name = "reg_" + std::to_string(idx) + "_0";
        z3::expr reg = ctx.constant(name.c_str(), float32);
        std::vector<z3::expr> regVersions;
        regVersions.push_back(reg);
        registers.push_back(regVersions);
        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, reg)));
    }
    for (const auto & c : OpsSeq) {
        std::string name = "reg_" + std::to_string(c.dest_reg) + "_" + std::to_string(registers[c.dest_reg].size());
        z3::expr val = ctx.constant(name.c_str(), float32);
        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, val)));
        switch(c.op) {
            case Instruction::Ops::ADD:
                s.add(val == registers[c.src_reg1].back() + registers[c.src_reg2].back());
                break;
            case Instruction::Ops::SUB:
                s.add(val == registers[c.src_reg1].back() - registers[c.src_reg2].back());
                break;
            case Instruction::Ops::MUL:
                s.add(val == registers[c.src_reg1].back() * registers[c.src_reg2].back());
                break;
            case Instruction::Ops::DIV:
                s.add(val == registers[c.src_reg1].back() / registers[c.src_reg2].back());
                break;
            case Instruction::Ops::INIT:
                z3::expr value = ctx.constant(name.c_str(), float32);
                s.add(val == value);
                break;
        }
        registers[c.dest_reg].push_back(val);
    }
    std::vector versions(regs, 0);
    if (sor) {
        std::cout<<"system of restrictions z3:"<<std::endl<<s<<std::endl;;
    }
    if (s.check() == z3::sat) {
        const z3::model m = s.get_model();
        std::cout << "\ninit values\n";
        for (int i = 0; i < registers.size(); ++i) {
            std::cout<<"reg["<<i<<"] = "<<fpa_to_float(m.eval(registers[i][0]))<<std::endl;
        }
        std::cout <<std::endl;
        for (auto & operation : OpsSeq) {
            if (operation.op == Instruction::Ops::INIT) {
                std::cout << "reg[" << operation.dest_reg << "] = random_value"
                  << " (was: " << fpa_to_float(m.eval(registers[operation.dest_reg][versions[operation.dest_reg]++])) << ", became: " << fpa_to_float(m.eval(registers[operation.dest_reg][versions[operation.dest_reg]])) << ")\n";
            } else {
                std::cout << "reg[" << operation.dest_reg << "] = reg[" << operation.src_reg1
                 << "] "<<getOpSymbol(operation.op)<<" reg[" << operation.src_reg2 << "]"
                 << " (" << fpa_to_float(m.eval(registers[operation.src_reg1][versions[operation.src_reg1]])) << " " << getOpSymbol(operation.op) <<" " << fpa_to_float(m.eval(registers[operation.src_reg2][versions[operation.src_reg2]])) << " = " << fpa_to_float(m.eval(registers[operation.dest_reg][++versions[operation.dest_reg]]))
                 << ")\n";
            }
            std::cout<<std::endl<<"intermediate results:"<<std::endl;
            for (size_t idx = 0; idx < registers.size(); ++idx) {
                std::cout<<"reg["<<idx<<"] "<<fpa_to_float(m.eval(registers[idx][versions[idx]]))<<std::endl;
            }
            std::cout<<std::endl;
        }
        std::cout << "\nfinal values\n";
        if (intermediateResults) {
            for (int i = 0; i < registers.size(); ++i) {
                std::cout<<"reg["<<i<<"] = "<<fpa_to_float(m.eval(registers[i].back()))<<std::endl;
            }
        } else {
            std::cout << "unsat :(" << std::endl;
        }
    }
}