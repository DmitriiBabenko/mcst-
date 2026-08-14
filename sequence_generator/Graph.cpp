#include "Graph.h"
#include <random>
#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
    const std::size_t size(const Ops & op) {
        if (op == Ops::INIT) {
            return 0;
        } else {
            return 2;
        }
    }

    const std::set<std::size_t> getSources(const std::size_t & left, const std::size_t & right, const Ops & op, std::mt19937 & gen) {
        std::set<std::size_t> sources;
        std::uniform_int_distribution<std::size_t> source_selector(left, right);
        while (sources.size() < size(op)) {
            sources.insert(source_selector(gen));
        }
        return sources;
    }

    const Ops getOp(const std::size_t left, const std::size_t right, std::mt19937 & gen) {
        if (right <= left) {
            return Ops::INIT;
        } else {
            std::uniform_int_distribution<std::size_t> operation_selector(0, static_cast<std::size_t>(Ops::COUNT) - 1);
            return static_cast<Ops>(operation_selector(gen));
        }
    }

    const std::size_t Graph::size() const {
        return _ops.size();
    }

    const std::string toStr(const Ops & op) {
        switch(op) {
            case Ops::INIT:
                return "INIT";
            case Ops::ADD:
                return "ADD";
            case Ops::SUB:
                return "SUB";
            case Ops::MUL:
                return "MUL";
            case Ops::DIV:
                return "DIV";
            default:
                return "?";
        }
    }

    namespace {
        std::string formatFloat(float v) {
            std::ostringstream oss;
            oss << std::setprecision(9) << v;
            return oss.str();
        }
        std::string nodeToDot(std::size_t idx, const Ops & op, const std::optional<float> & value, const std::optional<std::size_t> & reg) {
            std::string line = " " + std::to_string(idx) + " [label=\"" + std::to_string(idx) + ": " + toStr(op);
            if (value) {
                line += " = " + formatFloat(*value) + ";";
            }
            if (reg) {
                line += "Reg = " + std::to_string(*reg);
            }
            line += "\"];\n";
            return line;
        }

        std::string edgeToDot(std::size_t src, std::size_t dst) {
            return " " + std::to_string(src) + " -> " + std::to_string(dst) + ";\n";
        }
    }

    const std::string Graph::toDot() const {
        std::string nodes;
        for (std::size_t idx = 0; idx < _ops.size(); ++idx) {
            const std::optional<float> value = hasValues() ? std::optional<float>(_values[idx]) : std::nullopt;
            const std::optional<std::size_t>  regs = hasRegs() ? std::optional<std::size_t>(_regs[idx]) : std::nullopt;
            nodes += nodeToDot(idx, _ops[idx], value, regs);
        }

        std::string edges;
        for (std::size_t src = 0; src < _ways.size(); ++src) {
            for (const auto & dst : _ways[src]) {
                edges += edgeToDot(src, dst);
            }
        }
        return "digraph G {\n" + nodes + edges + "}\n";
    }

    const std::vector<Ops> buildOps(std::mt19937 & gen, const unsigned size) {
        std::vector<Ops> ops;
        ops.push_back(Ops::INIT);
        for (std::size_t idx = 1; idx < size; ++idx) {
            ops.push_back(getOp(0, idx - 1, gen));
        }
        return ops;
    }

    const std::vector<std::vector<std::size_t>> buildWays(std::mt19937 & gen, const unsigned size, const std::vector<Ops> & ops) {
        std::vector<std::vector<std::size_t>> ways(size);
        for (std::size_t idx = 1; idx < size; ++idx) {
            for (const auto & src : getSources(0, idx - 1, ops[idx], gen)) {
                ways[src].push_back(idx);
            }
        }
        return ways;
    }

    Graph::Graph(std::mt19937 & gen, const unsigned size):
        _ops(buildOps(gen, size)),
        _ways(buildWays(gen, size, _ops)){}

    Graph::Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways):
        _ops(std::move(ops)),
        _ways(std::move(ways)){}

    Graph::Graph(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<std::vector<std::size_t>> inc_ways, std::vector<float> values, std::vector<std::size_t> regs):
         _ops(std::move(ops)),
        _ways(std::move(ways)),
        _incoming_ways(std::move(inc_ways)),
        _values(std::move(values)),
        _regs(std::move(regs)){}
    
    Graph Graph::fromParts(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways) {
        return Graph(std::move(ops), std::move(ways));
    }

    Graph Graph::fromParts(std::vector<Ops> ops, std::vector<std::vector<std::size_t>> ways, std::vector<std::vector<std::size_t>> inc_ways, std::vector<float> values, std::vector<std::size_t> regs) {
        return Graph(std::move(ops), std::move(ways), std::move(inc_ways), std::move(values), std::move(regs));
    }

    const Graph Graph::withValues(std::vector<float> values) const {
        return Graph(_ops, _ways, _incoming_ways, std::move(values), _regs);
    }

    const Graph Graph::withRegs(std::vector<std::size_t> regs) const {
        return Graph(_ops, _ways, _incoming_ways, _values, std::move(regs));
    }