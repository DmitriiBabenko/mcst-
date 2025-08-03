//
// Created by димасик on 30.07.2025.
//
#include "z3++.h"
#include <vector>
#include "../makeRegs.h"

std::vector<z3::expr> makeRegs(int size, z3::context& ctx, const z3::sort & float32, z3::solver & s) {
    std::vector<z3::expr> regs;
    for (int idx = 0; idx < size; ++idx) {
        std::string name = "reg_" + std::to_string(idx);
        z3::expr reg = ctx.constant(name.c_str(), float32);
        regs.push_back(reg);
        s.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, reg)));
    }
    return regs;
}