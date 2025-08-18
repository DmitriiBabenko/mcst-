#include "genSeq.h"
#include "Instruction.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_set>

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

    if (size == 0 || regs == 0) {
        std::cerr << "Error: size and regs must be > 0" << std::endl;
        return returned;
    }

    std::uniform_int_distribution<unsigned> reg(0, regs - 1);
    std::uniform_int_distribution op_type(0, 4);
    std::uniform_int_distribution op_decision(0, 3);

    constexpr Instruction::Ops ops[] = {
                                Instruction::Ops::ADD,
                                Instruction::Ops::SUB,
                                Instruction::Ops::MUL,
                                Instruction::Ops::DIV,
                                };

    std::vector initialized_regs(regs, false);

    std::vector<unsigned> init_regs_cache;
    init_regs_cache.reserve(regs);

    for (size_t idx = 0; idx < size; ++idx) {
        unsigned dst_reg = reg(gen);

        if (const int operation_type = op_type(gen); !initialized_regs[dst_reg] || operation_type == 4) {
            returned.emplace_back(static_cast<int>(dst_reg));

            if (!initialized_regs[dst_reg]) {
                initialized_regs[dst_reg] = true;
                init_regs_cache.push_back(dst_reg);
            }
        } else {
            if (initialized_regs.size() < 2) {
                returned.emplace_back(static_cast<int>(dst_reg));
                if (!initialized_regs[dst_reg]) {
                    initialized_regs[dst_reg] = true;
                    init_regs_cache.push_back(dst_reg);
                }
            } else {
                const int random_op = op_decision(gen);

                std::uniform_int_distribution<size_t> init_reg_selector(0, init_regs_cache.size() - 1);

                unsigned src_reg1 = init_regs_cache[init_reg_selector(gen)];
                unsigned src_reg2 = init_regs_cache[init_reg_selector(gen)];

                if (src_reg1 >= regs || src_reg2 >= regs || dst_reg >= regs) {
                    std::cerr << "Error: Register index out of bounds" << std::endl;
                    continue;
                }

                if (forbiddenOp(src_reg1, src_reg2, ops[random_op])) {
                    int attempts = 0;
                    do {
                        src_reg1 = init_regs_cache[init_reg_selector(gen)];
                        src_reg2 = init_regs_cache[init_reg_selector(gen)];
                        attempts++;
                        if (attempts > 100) {
                            std::cerr << "Warning: Many attempts to avoid forbidden op" << std::endl;
                            if (init_regs_cache.size() >= 2) {
                                src_reg1 = init_regs_cache[0];
                                src_reg2 = init_regs_cache[1];
                            }
                            break;
                        }
                    } while (forbiddenOp(src_reg1, src_reg2, ops[random_op]) && attempts < 100);
                }

                returned.emplace_back(ops[random_op], static_cast<int>(dst_reg),
                                        static_cast<int> (src_reg1), static_cast<int> (src_reg2));
                if (!initialized_regs[dst_reg]) {
                    initialized_regs[dst_reg] = true;
                    init_regs_cache.push_back(dst_reg);
                }
            }
        }
    }

    return returned;
}
