#include "genSeq.h"
#include "Instruction.h"
#include "generateComponents.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <cassert>
std::vector<Instruction> genSeq(const unsigned regs, const unsigned seed, const std::vector<std::vector<AbstractOp>>& OpsComponents) {
    std::vector<Instruction> returned;
    std::mt19937 gen(seed);

    std::uniform_int_distribution<unsigned> reg(0, regs - 1);

    for (std::size_t idx_comp = 0; idx_comp < OpsComponents.size(); ++idx_comp) {

        std::vector<std::size_t> id_to_reg(OpsComponents[idx_comp].size());
        std::vector<bool> regs_cache(regs, false);
        id_to_reg.resize(OpsComponents[idx_comp].size());

        for (std::size_t idx = 0; idx < OpsComponents[idx_comp].size(); ++idx) {

            const AbstractOp op = OpsComponents[idx_comp][idx];

            unsigned dst_reg = reg(gen);
            while (regs_cache[dst_reg]) {
                dst_reg++;
                dst_reg %= regs;
            }
            const char* random_op = op.kind();

            if (random_op == "INIT") {
                returned.emplace_back(dst_reg);

            } else {
                const std::size_t src_reg1 = id_to_reg[op.fst_source()];
                const std::size_t src_reg2 = id_to_reg[op.snd_source()];

                returned.emplace_back(op.operation(), dst_reg,
                                            src_reg1, src_reg2);
            }
            id_to_reg[op.id()] = dst_reg;
            regs_cache[dst_reg] = true;
        }
    }
    return returned;
}
