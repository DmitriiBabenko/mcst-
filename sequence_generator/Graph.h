#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <random>
#include <string>
enum class Ops {
    INIT,
    ADD,
    MUL,
    DIV,
    SUB,
    COUNT
    };
class Graph {
public:

    Graph(const unsigned seed, const unsigned size, const unsigned comps);
    const std::string toDot() const;
private:
    const std::vector<Ops> _ops;
    const std::vector<std::vector<std::size_t>> _ways;
    const std::vector<float> _values;
    const std::vector<std::size_t> _regs;
};
#endif //GRAPH_H