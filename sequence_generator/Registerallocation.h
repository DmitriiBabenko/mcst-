#ifndef REGISTERALLOCATION_H
#define REGISTERALLOCATION_H
#include <vector>
#include <unordered_map>
#include "Node.h"

std::unordered_map<Node*, std::size_t> assign_registers(const std::vector<Node*> & sorted_nodes, std::size_t regs);

#endif //REGISTERALLOCATION_H