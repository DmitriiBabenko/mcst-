#include "Values.h"
#include "../common_add/fpa_to_float.h"
#include <z3++.h>
#include <unordered_map>
#include <string>
#include <iostream>

namespace {

    z3::expr applyOp(z3::context & ctx, Ops op,
                        const z3::expr & a, const z3::expr & b,
                        z3::solver & solver) {
        switch (op) {
            case Ops::ADD: return a + b;
            case Ops::SUB: return a - b;
            case Ops::MUL: return a * b;
            case Ops::DIV:
                solver.add(!(b == ctx.fpa_val(0.0f)));
                return a / b;
            default:
                throw std::runtime_error("unknown operation " + toStr(op) + '\n');
        }
    }
}

std::vector<float> solve(const Graph & graph, unsigned seed, const bool & log) {
    const auto & ops = graph.ops();
    const auto & ways = graph.ways();
    const std::size_t n = ops.size();

    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", seed);
    z3::solver solver(ctx);
    solver.set(p);

    const z3::sort fpaSort = ctx.fpa_sort<32>();

    const std::vector<std::vector<std::size_t>> sourcesOf = graph.incWays();

    std::unordered_map<std::size_t, z3::expr> nodeExpr;
    nodeExpr.reserve(n);

    for (std::size_t idx = 0; idx < n; ++idx) {
        const std::string name = "v" + std::to_string(idx);
        z3::expr x = ctx.constant(name.c_str(), fpaSort);
        nodeExpr.emplace(idx, x);
        solver.add(x.mk_is_normal());
        solver.add(x >= ctx.fpa_val(-1000.0f));
        solver.add(x <= ctx.fpa_val(1000.0f));
        solver.add(x >= ctx.fpa_val(0.0001f) || x <= ctx.fpa_val(-0.0001f));

        if (ops[idx] != Ops::INIT) {
            const z3::expr & a = nodeExpr.at(sourcesOf[idx][0]);
            const z3::expr & b = nodeExpr.at(sourcesOf[idx][1]);
            z3::expr result = applyOp(ctx, ops[idx], a, b, solver);
            solver.add(x == result);
        }
    }

    if (log) {
        std::cout << "=== constraints ===\n" << solver << "\n==========\n";
    }

    if (solver.check() != z3::sat) {
        throw std::runtime_error("system is unsat\n");
    }

    z3::model model = solver.get_model();
    std::vector<float> values(n);
    for (std::size_t idx = 0; idx < n; ++idx) {
        z3::expr val = model.eval(nodeExpr.at(idx), true);
        values[idx] = fpa_to_float(val);
    }
    return values;
}