//
// Created by димасик on 31.07.2025.
//
#include "solveRandomApply.h"
#include "Instruction.h"
#include "genSeq.h"
#include <vector>
#include <iostream>
void solveRandomApply(int seed, int size, int regs) {
    std::vector<Instruction> OpsSeq = genSeq(size, regs);
    const std::string ops[] = {"ADD", "SUB", "MUL", "DIV", "INIT"};
    for (auto & c : OpsSeq) {
        int op_index = static_cast<int>(c.op);
        std::cout<<ops[op_index]<<std::endl;
    }
}