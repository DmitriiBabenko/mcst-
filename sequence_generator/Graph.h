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

const std::string toStr(const Ops & op);

class Graph {
public:
    Graph(const unsigned seed, const unsigned size, const unsigned comp);
    const std::string toDot() const;
    const std::vector<float> & values() const {
        return _values;
    }
    bool hasValues() const {
        return !_values.empty();
    }
    const std::vector<Ops> & ops() const {return _ops;}
    const std::vector<std::vector<std::size_t>> & ways() const {return _ways;}
    Graph withValues(std::vector<float> values) const;
    static Graph fromParts(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<float> values);
private:
    Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<float> values); 
    std::vector<Ops> _ops;
    std::vector<std::vector<std::size_t>> _ways;
    std::vector<float> _values;
    std::vector<std::size_t> _regs;
};
#endif //GRAPH_H