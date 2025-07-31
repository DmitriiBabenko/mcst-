//
// Created by димасик on 30.07.2025.
//
#include "z3++.h"
#include "addLimits.h"
void addLimits(z3::expr & a_idx, z3::expr & b_idx, z3::expr & c_idx, z3::expr & opCode, z3::context & ctx, z3::expr & val, z3::expr &  result, z3::solver & op_solver, const int size) {
    op_solver.add(a_idx >= 0 && a_idx < size);
    op_solver.add(b_idx >= 0 && b_idx < size);
    op_solver.add(c_idx >= 0 && c_idx < size);
    op_solver.add(opCode >= 0 && opCode < 5);
    op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, result)));
    op_solver.add(to_expr(ctx, Z3_mk_fpa_is_normal(ctx, val)));
}