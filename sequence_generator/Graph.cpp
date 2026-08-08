#include "Graph.h"
#include <random>
#include <set>
#include <iostream>
#include <string>
    const std::size_t leftBound(const std::size_t idx, const unsigned size, const unsigned comps) {
        return (idx / (size / comps)) * (size / comps);
    }

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

    const std::string Graph::toDot() const {
        std::string dot = "digraph G {\n";
        for (std::size_t idx = 0; idx < _ops.size(); ++idx) {
            dot += " " + std::to_string(idx) + " [label=\"" + std::to_string(idx) + ": " + toStr(_ops[idx]) + (_values.size() > 1 ? ", val=" + std::to_string(_values[idx]) : "") +"\"];\n";
        }
        for (std::size_t src = 0; src < _ways.size(); ++src) {
            for (const auto & dst : _ways[src]) {
                dot += " " + std::to_string(src) + " -> " + std::to_string(dst) + ";\n";
            }
        }
        dot += "}\n";
        return dot;
    }

    const std::vector<Ops> buildOps(unsigned seed, unsigned size, unsigned comps) {
        std::mt19937 gen(seed);
        std::vector<Ops> ops;
        ops.push_back(Ops::INIT);
        for (std::size_t idx = 1; idx < size; ++idx) {
            ops.push_back(getOp(leftBound(idx, size, comps), idx - 1, gen));
        }
        return ops;
    }

    const std::vector<std::vector<std::size_t>> buildWays(unsigned seed, unsigned size, unsigned comps, const std::vector<Ops> & ops) {
        std::mt19937 gen(seed);
        std::vector<std::vector<std::size_t>> ways(size);
        for (std::size_t idx = 1; idx < size; ++idx) {
            for (const auto & src : getSources(leftBound(idx, size, comps), idx - 1, ops[idx], gen)) {
                ways[src].push_back(idx);
            }
        }
        return ways;
    }

    Graph::Graph(const unsigned seed, const unsigned size, const unsigned comps):
        _ops(buildOps(seed, size, comps)),
        _ways(buildWays(seed, size, comps, _ops)){}
