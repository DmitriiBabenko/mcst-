//
// Created by димасик on 30.07.2025.
//

#ifndef MAKEREGS_H
#define MAKEREGS_H
//return size registers, normalize all of them in solver (s);
std::vector<z3::expr> makeRegs(int size, z3::context& ctx, const z3::sort & float32, z3::solver & s);
#endif //MAKEREGS_H
