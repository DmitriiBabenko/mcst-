#include "Graph.h"
#include "Node.h"
#include <random>
class ChooseOp{
public:
    std::size_t get_arity() {
        return 2;
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
            nodes.push_back(new Node(std::vector<Node*>(), cur_size));
            ++cur_size;
        }
        while (cur_size < _size) {
            std::size_t cur_op = random_op.get_arity();
            std::vector<Node*> sources(cur_op);
            for (std::size_t idx = 0, source_idx = 0; idx < cur_op; ++idx) {
                std::uniform_int_distribution<std::size_t> source_selector(source_idx, cur_size - cur_op + idx);
                source_idx = source_selector(gen);
                sources[idx] = nodes[source_idx];
                ++source_idx;
            }
            nodes.push_back(new Node(std::move(sources), cur_size));
            ++cur_size;
        }
    }

const std::vector<Node*> Graph::getNodes() const {
    return nodes;
}

const unsigned Graph::getId() const {
    return _id;
}
