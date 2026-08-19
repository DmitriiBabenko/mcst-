#include "assignRegisters.h"
#include <random>
#include <deque>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iostream>

const std::deque<std::size_t> makeQueue(const unsigned & regs, std::mt19937 & gen) {
    std::deque<std::size_t> registers(regs);
    std::iota(registers.begin(), registers.end(), 0);
    std::shuffle(registers.begin(), registers.end(), gen);
    return registers;
}

std::size_t findLastNode(const std::vector<std::size_t> & dependents) {
    return *(std::max_element(dependents.begin(), dependents.end()));
}

void freeRegs(std::deque<std::size_t> & regsQueue, const std::vector<std::vector<std::size_t>> & timeToFreeReg, const std::size_t & idx) {
    for (const auto & reg : timeToFreeReg[idx]) {
        regsQueue.push_front(reg);
    }
}

const Graph assignComponent(const Graph & graph, std::mt19937 & gen, const unsigned & regs) {
    std::vector<std::size_t> nodeToRegister(graph.size());
    std::deque<std::size_t> regsQueue = makeQueue(regs, gen);
    std::vector<std::vector<std::size_t>> timeToFreeReg(graph.size());
    for (std::size_t idx = 0; idx < graph.size(); ++idx) {
        freeRegs(regsQueue, timeToFreeReg, idx);
        if (regsQueue.empty()) {
            std::string message = "not enough registers for op " + std::to_string(idx) + "\n regs usage:\n";
            for (std::size_t ind = 0; ind < idx; ++ind) {
                message += std::to_string(ind) + ": " + std::to_string(nodeToRegister[ind]) + '\n'; 
            }
            throw std::runtime_error(message);
        }
        nodeToRegister[idx] = regsQueue.back();
        regsQueue.pop_back();
        if (!graph.ways()[idx].empty()){
            timeToFreeReg[findLastNode(graph.ways()[idx])].push_back(nodeToRegister[idx]);
        } else if (idx + 1 < graph.size()){
            timeToFreeReg[idx + 1].push_back(nodeToRegister[idx]);
        }
    }
    return Graph(graph.ops(), graph.ways(), graph.incWays(), graph.values(), nodeToRegister);
}