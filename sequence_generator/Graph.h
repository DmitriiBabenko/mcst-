#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Node.h"
#include <random>
class Graph {
public:
    Graph(const unsigned seed, const unsigned size, const unsigned min_count_init, const unsigned id);
    void build(std::mt19937 & gen);
    const std::vector<Node*> getNodes() const;
    const unsigned getId() const;
private:
    const unsigned _min_inits;
    const unsigned _size;
    const unsigned _id;
    std::vector<Node*> nodes;
};
#endif //GRAPH_H