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
    Graph(std::mt19937 & gen, const unsigned size);
    const std::string toDot() const;
    const std::vector<float> & values() const { return _values;}
    bool hasValues() const { return !_values.empty();}
    bool hasRegs() const { return !_regs.empty();}
    const std::vector<Ops> & ops() const {return _ops;}
    const std::vector<std::vector<std::size_t>> & ways() const {return _ways;}
    const std::vector<std::vector<std::size_t>> & incWays() const {return _incoming_ways;}
    const std::vector<std::size_t> & regs() const { return _regs;}
    void setValues(const std::vector<float> & values) {_values = values;}
    void setRegs(const std::vector<std::size_t> & regs) {_regs = regs;}
    const Graph withValues(std::vector<float> values) const;
    const Graph withRegs(std::vector<std::size_t> regs) const;
    const std::size_t size() const;
    void print(const bool & log) const;
    static Graph fromParts(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways);
    static Graph fromPartsWithIncWays(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> incWays);
    static Graph fromParts(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<float> values, std::vector<std::size_t> regs);
    static std::vector<std::vector<std::size_t>> buildWaysFromIncWays(const std::vector<std::vector<std::size_t>> & incWays);
    Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<std::vector<std::size_t>> incWays, std::vector<float> values, std::vector<std::size_t> regs);
private:
    Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways);
    Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<std::vector<std::size_t>> incWays);
    Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<float> values, std::vector<std::size_t> regs);
    std::vector<std::vector<std::size_t>> buildIncWays() const;
    std::vector<Ops> _ops;
    std::vector<std::vector<std::size_t>> _ways;
    std::vector<std::vector<std::size_t>> _incoming_ways;
    std::vector<float> _values;
    std::vector<std::size_t> _regs;
};
#endif //GRAPH_H