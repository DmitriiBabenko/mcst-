//
// Created by димасик on 31.07.2025.
//
#include "genSeq.h"
#include "Instruction.h"
#include <vector>
#include <random>
std::vector<Instruction> genSeq(int size, int regs) {
    std::vector<Instruction> returned;
    for (size_t idx = 0; idx < size; ++idx) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> dist(1, 5);
        std::uniform_int_distribution<int> reg(0, regs - 1);

        int random_num = dist(gen);
        int dist_reg = reg(gen);
        int src_reg1 = reg(gen);
        int src_reg2 = reg(gen);
        switch(random_num) {
            case 1:
                returned.push_back(Instruction(Instruction::Ops::ADD, dist_reg, src_reg1, src_reg2));
                break;
            case 2:
                returned.push_back(Instruction(Instruction::Ops::SUB, dist_reg, src_reg1, src_reg2));
                break;
            case 3:
                returned.push_back(Instruction(Instruction::Ops::MUL, dist_reg, src_reg1, src_reg2));
                break;
            case 4:
                returned.push_back(Instruction(Instruction::Ops::DIV, dist_reg, src_reg1, src_reg2));
                break;
            case 5:
                returned.push_back(Instruction(dist_reg));
                break;
        }
    }
    return returned;
}