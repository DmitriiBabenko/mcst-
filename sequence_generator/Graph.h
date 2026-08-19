#pragma once
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
    const std::size_t size() const;
    void print(const bool & log) const;
    Graph(const std::vector<Ops> & ops,
        const std::vector<std::vector<std::size_t>> & ways,
        const std::vector<std::vector<std::size_t>> & incWays,
        const std::vector<float> & values,
        const std::vector<std::size_t> & regs);
private:
    std::vector<Ops> _ops;
    std::vector<std::vector<std::size_t>> _ways;
    std::vector<std::vector<std::size_t>> _incoming_ways;
    std::vector<float> _values;
    std::vector<std::size_t> _regs;
};

const Graph uniteGraph(const std::vector<Graph> & graphs);
const std::vector<std::vector<std::size_t>> reverseWays(const std::vector<std::vector<std::size_t>> & ways);