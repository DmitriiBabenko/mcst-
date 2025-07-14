#include "z3++.h"
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include "fpa_to_float.cpp"


void randomFpa32(std::set<std::vector<float>>& set, const size_t count, const unsigned seed) {
    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", seed);

    const z3::tactic t = with(z3::tactic(ctx, "smt"), p);
    const z3::sort float32 = ctx.fpa_sort(8, 24);

    const z3::expr a = ctx.constant("a", float32);
    const z3::expr b = ctx.constant("b", float32);
    const z3::expr c = ctx.constant("c", float32);

    z3::solver s = t.mk_solver();
    s.add(a + b == c);
    s.set(p);

    const z3::expr a_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, a));
    const z3::expr b_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, b));
    const z3::expr c_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, c));

    s.add(a_normal);
    s.add(b_normal);
    s.add(c_normal);

    size_t attempts = 0;
    const size_t max_attempts = count * 10;

    while (set.size() < count && attempts < max_attempts) {
        attempts++;

        if (s.check() == z3::sat) {
            z3::model m = s.get_model();

            z3::expr val_a = m.eval(a);
            z3::expr val_b = m.eval(b);
            z3::expr val_c = m.eval(c);
            std::vector<float> model{fpa_to_float(val_a), fpa_to_float(val_b), fpa_to_float(val_c)};

            set.insert(model);

            s.add(!(a == val_a && b == val_b && c == val_c));
        } else {
            std::cout << "No more satisfying models found." << std::endl;
            break;
        }
    }

    std::cout << "Found " << set.size() << " unique models after "
              << attempts << " attempts." << std::endl;
}