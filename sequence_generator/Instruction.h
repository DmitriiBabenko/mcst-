#pragma once
struct Instruction {
    enum class Ops {
        ADD,
        SUB,
        MUL,
        DIV,
        INIT
    };
    Ops op;
    unsigned dest_reg;
    unsigned src_reg1;
    unsigned src_reg2;

    Instruction() = default;

    Instruction(const Ops op, const unsigned dest, const unsigned src1, const unsigned src2)
        : op(op), dest_reg(dest), src_reg1(src1), src_reg2(src2) {}

    explicit Instruction(const unsigned dest)
        : op(Ops::INIT), dest_reg(dest), src_reg1(-1), src_reg2(-1){}
};