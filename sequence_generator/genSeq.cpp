//
// Created by димасик on 31.07.2025.
//
#include "genSeq.h"
#include "Instruction.h"
#include <vector>
#include <random>
std::vector<Instruction> genSeq(const unsigned size, const unsigned regs, const unsigned seed) {
    std::vector<Instruction> returned;
    std::mt19937 gen(seed);

    std::uniform_int_distribution dst(0, 4);
    std::uniform_int_distribution<unsigned> reg(0, regs - 1);

    const Instruction::Ops ops[] = {
                                Instruction::Ops::ADD,
                                Instruction::Ops::SUB,
                                Instruction::Ops::MUL,
                                Instruction::Ops::DIV,
                                };

    for (size_t idx = 0; idx < size; ++idx) {

        const int random_num = dst(gen);
        unsigned dst_reg = reg(gen);

        switch(random_num) {
            case 4:
                returned.emplace_back(dst_reg);
                break;
            case 0: case 1: case 2: case 3:
                unsigned src_reg1 = reg(gen);
                unsigned src_reg2 = reg(gen);
                returned.emplace_back(ops[random_num], dst_reg, src_reg1, src_reg2);
        }
    }
    return returned;
}