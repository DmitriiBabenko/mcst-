#include "Graph.h"
#include "Node.h"
#include <random>
class ChooseOp{
public:
    std::size_t get_arity(Ops op) {
        if (op == Ops::INIT) {
            return 0;
        } else {
            return 2;
        }
    }
};

    Graph::Graph(const unsigned seed, const unsigned size, const unsigned min_count_init, const unsigned id):
        _min_inits(min_count_init),
        _size(size),
        _id(id) {
            nodes.reserve(size);
        }
    void Graph::build(std::mt19937 & gen) {
        ChooseOp random_op;
        unsigned cur_size = 0;
        while (cur_size < _min_inits) {
            nodes.push_back(new Node(std::vector<Node*>(), cur_size, Ops::INIT));
            ++cur_size;
        }
        std::uniform_int_distribution<std::size_t> operation_selector(0, static_cast<std::size_t>(Ops::COUNT) - 1);
        while (cur_size < _size) {
            Ops op_name = static_cast<Ops>(operation_selector(gen));
            std::size_t op_arity = random_op.get_arity(op_name);
            std::vector<Node*> sources(op_arity);
            for (std::size_t idx = 0, source_idx = 0; idx < op_arity; ++idx) {
                std::uniform_int_distribution<std::size_t> source_selector(source_idx, cur_size - op_arity + idx);
                source_idx = source_selector(gen);
                sources[idx] = nodes[source_idx];
                ++source_idx;
            }
            nodes.push_back(new Node(std::move(sources), cur_size, op_name));
            ++cur_size;
        }
    }

const std::vector<Node*> Graph::getNodes() const {
    return nodes;
}

const unsigned Graph::getId() const {
    return _id;
}
