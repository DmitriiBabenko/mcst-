#pragma once
#include <string>
struct Instruction {
    enum class Ops {
        ADD,
        SUB,
        MUL,
        DIV,
        INIT
    };
    Ops op;
    int dest_reg;
    int src_reg1;
    int src_reg2;

    // Конструкторы
    Instruction() = default;

    // Для арифметических операций
    Instruction(Ops op, int dest, int src1, int src2)
        : op(op), dest_reg(dest), src_reg1(src1), src_reg2(src2) {}

    // Для инициализации
    Instruction(int dest)
        : op(Ops::INIT), dest_reg(dest), src_reg1(-1), src_reg2(-1){}
};