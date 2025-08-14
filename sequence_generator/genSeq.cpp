//
// Created by димасик on 31.07.2025.
//
#include "genSeq.h"
#include "Instruction.h"
#include <vector>
#include <random>
#include <algorithm>

bool forbiddenOp(const unsigned & fst, const unsigned & snd, const Instruction::Ops & op) {
    const std::vector forbidden = {
        Instruction::Ops::SUB,
        Instruction::Ops::DIV,
        };
    return fst == snd && std::find(forbidden.begin(), forbidden.end(), op) != forbidden.end();
}

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
        int random_num = dst(gen);
        unsigned dst_reg = reg(gen);
        switch(random_num) {
            case 4:
                returned.emplace_back(dst_reg);
            break;
            case 0: case 1: case 2: case 3: {
                unsigned src_reg1 = reg(gen);
                unsigned src_reg2 = reg(gen);
                if (forbiddenOp(src_reg1, src_reg2, ops[random_num])) {
                    do {
                        src_reg1 = reg(gen);
                        src_reg2 = reg(gen);
                    } while (forbiddenOp(src_reg1, src_reg2, ops[random_num]));
                }
                returned.emplace_back(ops[random_num], dst_reg, src_reg1, src_reg2);

                break;
            }
        }
    }
    return returned;
}
