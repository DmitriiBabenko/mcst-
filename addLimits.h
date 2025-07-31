//
// Created by димасик on 30.07.2025.
//
#ifndef ADDLIMITS_H
#define ADDLIMITS_H
#include "z3++.h"
void addLimits(z3::expr & a_idx, z3::expr & b_idx, z3::expr & c_idx, z3::expr & opCode, z3::context & ctx, z3::expr & val, z3::expr &  result, z3::solver & op_solver, int size);
#endif //ADDLIMITS_H
