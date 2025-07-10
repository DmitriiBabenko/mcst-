
/*++
Copyright (c) 2015 Microsoft Corporation

--*/

#include <iostream>
#include <sstream>
#include<set>
#include"z3++.h"
#include<string>


void randomFpa32(std::set<std::string>& set, const size_t count) {
    z3::context ctx;
    z3::params p(ctx);
    p.set("random_seed", static_cast<unsigned>(time(nullptr)));
    const z3::tactic t = with(z3::tactic(ctx, "smt"), p);
    const z3::sort float_ = ctx.fpa_sort(8, 24);
    const z3::expr a = ctx.constant("a", float_);
    const z3::expr b = ctx.constant("b", float_);
    const z3::expr c = ctx.constant("c", float_);
    z3::solver s = t.mk_solver();
    s.add(a + b == c);
    s.set(p);

    const z3::expr a_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, a));
    const z3::expr b_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, b));
    const z3::expr c_normal = to_expr(ctx, Z3_mk_fpa_is_normal(ctx, c));

    s.add(a_normal);
    s.add(b_normal);
    s.add(c_normal);

    size_t i = 0;
    do {
        i = set.size();
        if (s.check() == z3::sat) {
            z3::model m = s.get_model();
            set.insert(m.to_string());
        }
    } while (set.size() > i and i < count);
    std::cout<<"found "<<set.size()<<" models";
}
int main() {
    std::set<std::string> x;
    randomFpa32(x, 100);
    std::cout<<std::endl;
    const auto m = std::vector<std::string>(x.begin(), x.end());
    std::cout<<m[0];
}