#include "generateComponents.h"
#include "DependencyAnalysis.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <cassert>
std::vector<AbstractOp> gen_sequence(const unsigned size, std::mt19937& gen) {
    std::vector<AbstractOp> result_sequence;
    result_sequence.reserve(size);

    const unsigned init_count = std::max(std::min(size, 2u), std::min(size / 5, 5u));

    for(std::size_t idx = 0; idx < init_count && idx < size; ++idx) {
        result_sequence.push_back(AbstractOp(Ops::INIT, idx, 1, 1));
    }

    for (std::size_t idx = init_count; idx < size; ++idx) {
        std::uniform_int_distribution<std::size_t> source_selector(0, idx - 1);
        std::size_t src1 = source_selector(gen);
        std::size_t src2 = source_selector(gen);
        while (src1 == src2) {
            src2 = source_selector(gen);
        }

        std::uniform_int_distribution<std::size_t> operation_selector(1, 4);
        std::size_t op = operation_selector(gen);
        result_sequence.push_back(AbstractOp(static_cast<Ops>(op), idx, src1, src2));
    }

    return result_sequence;
}
std::vector<std::vector<AbstractOp>> gen_component(const unsigned size, const unsigned seed, const unsigned comps) {
    assert(comps > 0 && comps <= size);
    std::vector<std::vector<AbstractOp>> returned;
    returned.reserve(comps);
    std::mt19937 gen(seed);

    const unsigned component_size = size / comps;
    unsigned rest = size - component_size * comps; 
    for (std::size_t idx = 0; idx < comps; ++idx, rest ^= rest) {
        returned.push_back(gen_sequence(component_size + rest, gen));
    }

    return returned;
}