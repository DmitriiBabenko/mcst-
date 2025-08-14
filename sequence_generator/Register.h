#pragma once
#include "z3++.h"
#include <string>
struct Register {
    enum class Ops {
        ADD,
        SUB,
        MUL,
        DIV,
        INIT
    };
    Ops op;
    const Register *first = nullptr;
    const Register *second = nullptr;
    Register *next = nullptr;
    bool visited = false;
    Register() {
    }
};