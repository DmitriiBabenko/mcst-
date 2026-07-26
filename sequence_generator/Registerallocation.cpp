#include "Registerallocation.h"
#include <algorithm>
#include <queue>
#include <stdexcept>
#include <iostream>

std::unordered_map<Node*, std::size_t> assign_registers(const std::vector<Node*> & sorted_nodes, std::size_t regs) {
    std::unordered_map<Node*, std::size_t> rho;

    //positions - position of each Node v in topsort.
    std::unordered_map<Node*, std::size_t> positions;
    positions.reserve(sorted_nodes.size());
    for (std::size_t i = 0; i < sorted_nodes.size(); ++i) {
        positions[sorted_nodes[i]] = i;
    }

    //last_use - last position of v consumers.
    std::unordered_map<Node*, std::size_t> last_use;
    last_use.reserve(sorted_nodes.size());
    for (Node* v : sorted_nodes) {
        std::size_t last = positions[v];
        for (Node* consumer : v->getOut()) {
            last  = std::max(last, positions.at(consumer));
        }
        last_use[v] = last;
    }

    // release_at[i] -- is a vector of nodes whose registers can be freed
    std::vector<std::vector<Node*>> release_at(sorted_nodes.size());
    for (Node* v : sorted_nodes) {
        release_at[last_use[v]].push_back(v); 
    }

    std::queue<std::size_t> free_regs;
    for (std::size_t r = 0; r < regs; ++r) {
        free_regs.push(r);
    }

    for (std::size_t i = 0; i < sorted_nodes.size(); ++i) {
        Node* v = sorted_nodes[i];

        if (free_regs.empty()) {
            throw std::runtime_error("not enough registers");
        }
        std::size_t reg = free_regs.front();
        free_regs.pop();
        rho[v] = reg;

        for (Node* done : release_at[i]) {
            if (done != v) {
                free_regs.push(rho.at(done));
            }
        }
    }

    std::cout << "\nintermediate register values...\n";
    for (Node* v : sorted_nodes) {
        std::cout << "reg[" << rho.at(v) << "] = " << v->getValue() << "  (node " << v->getId() << ")\n";
    }
    return rho;
}