//
// Created by димасик on 31.07.2025.
//

#ifndef GENSEQ_H
#define GENSEQ_H
#include <vector>
#include "Instruction.h"
#include "generateComponents.h"
    std::vector<Instruction> genSeq(const unsigned regs, const unsigned seed, const std::vector<std::vector<AbstractOp>>& OpsComponents);
#endif //GENSEQ_H
