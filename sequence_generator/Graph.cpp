#include "Graph.h"
#include <random>
#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <algorithm>
#include <map>
#include <numeric>
#include <unordered_set>
#include "Cache.h"

    //сортирует множество компонент по невозрастанию
    const std::vector<std::size_t> canon(std::vector<std::size_t> partition) {
        std::sort(partition.begin(), partition.end(), std::greater<>{});
        return partition;
    }

    //перечисление возможных переходов от k узлов к (k + 1) узлам:
    //  1) добавить независимый узел
    //  2) добавить узел в одну компоненту
    //  3) добавить узел свзывающий разные компоненты
    enum class TransitionKind {
        Leaf,
        Same,
        Merge
    };

    //структура описывающая переход от k узлов к (k + 1) узлам
    // target - итоговое разбиение компонент
    // weight - количество способов построить такое разбиение
    // src's - индексы компонент в разбиении,от которых зависит последний добавленный узел
    struct Transition {
        std::vector<std::size_t> _target;
        std::size_t _weight;
        TransitionKind _kind;
        std::size_t _src1;
        std::size_t _src2;
        Transition(const std::vector<std::size_t> & partition) {
            _target = partition;
            _target.push_back(1);
            _weight = 1;
            _kind = TransitionKind::Leaf;
        }

        Transition(const std::vector<std::size_t> & partition, std::size_t src) {
            _target = partition;
            _target[src]++;
            _target = canon(_target); 
            _weight = partition[src] * (partition[src] - 1) / 2;
            _kind = TransitionKind::Same;
            _src1 = src;
            _src2 = src;
        }

        Transition(const std::vector<std::size_t> & partition, std::size_t src1, std::size_t src2) {
            std::size_t resultComp = partition[src1] + partition[src2] + 1;
            std::vector<std::size_t> target;
            for (std::size_t idx = 0; idx < partition.size(); ++idx) {
                if (idx != src1 && idx != src2) {
                    target.push_back(partition[idx]);
                }
            }
            _target = target;
            _target.push_back(resultComp);
            _target = canon(_target);
            _weight = partition[src1] * partition[src2];
            _kind = TransitionKind::Merge;
            _src1 = src1;
            _src2 = src2;
        }
    };

    //построить все возможные переходы из переданного разбиения
    const std::vector<Transition> enumerateTransitions(const std::vector<std::size_t> & partition) {
        std::vector<Transition> result;

        result.push_back(Transition(partition));

        for (std::size_t idx = 0; idx < partition.size(); ++idx) {
            if (partition[idx] > 1) {
                result.push_back(Transition(partition, idx));
            }
        }

        for (std::size_t src1 = 0; src1 < partition.size(); ++src1) {
            for (std::size_t src2 = src1 + 1; src2 < partition.size(); ++src2) {
                result.push_back(Transition(partition, src1, src2));
            }
        }

        return result; 
    }

    // dp[n][prtition] - сколькими способами можно построить граф из n узлов с разбиением на компоненты определённого размера
    std::vector<std::map<std::vector<std::size_t>, std::size_t>> buildForwardDp(std::size_t nodeCount) {
        
        std::vector<std::map<std::vector<std::size_t>, std::size_t>> dp = loadDp("forwardDp.json");
        std::size_t from = dp.size();
        if (from < nodeCount + 1) {
            dp.resize(nodeCount + 1);
        }
        dp[1][{1}] = 1;
        for (std::size_t idx = from; idx < nodeCount; ++idx) {
            for (const auto & [partition, count] : dp[idx]) {
                const std::vector<Transition> transitions = enumerateTransitions(partition);
                for (const auto & transition : transitions) {
                    dp[idx + 1][transition._target] += count * transition._weight;
                }
            }
        }
        saveDpCache(dp, "forwardDp.json");
        return dp;
    }

     std::vector<std::map<std::vector<std::size_t>, std::size_t>> buildSuffixDp(std::size_t nodeCount, const std::vector<std::map<std::vector<std::size_t>, std::size_t>> & dp) {
        std::vector<std::map<std::vector<std::size_t>, std::size_t>> suf(nodeCount + 1);
        suf[nodeCount][{nodeCount}] = 1;

        for (std::size_t k = nodeCount - 1; k >= 1; --k) {
            for (const auto & [partition, _] : dp[k]) {
                std::size_t total = 0;
                for (const auto & tr : enumerateTransitions(partition)) {
                    total += tr._weight * suf[k + 1][tr._target];
                }
                suf[k][partition] = total;
            }
        }

        return suf;
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
        std::map<std::pair<std::size_t, std::size_t>, int> evalDirs(const std::vector<std::vector<std::size_t>> & incWays) {
        std::map<std::pair<std::size_t, std::size_t>, int> directions;
        std::vector<std::vector<std::size_t>> leftIndent(incWays.size());
        std::vector<std::vector<std::size_t>> rightIndent(incWays.size());
        for (std::size_t dst = 0; dst < incWays.size(); ++dst) {
            if (incWays[dst].size() < 2) {
                continue;
            }
            const std::size_t left = incWays[dst][0];
            const std::size_t right = incWays[dst][1];
            const std::pair<std::size_t, std::size_t> fromLeft = {left, dst};
            const std::pair<std::size_t, std::size_t> fromRight = {right, dst};
            if (dst - left == 1) {
                directions[fromLeft] = 0;
            } else {
                std::unordered_set<std::size_t> restrictions;
                for (std::size_t iter = left; iter <= dst; ++iter) {
                    for (const auto & indentIter : leftIndent[iter]) {
                        restrictions.insert(indentIter); 
                    } 
                }
                std::size_t var = 1;
                while (restrictions.find(var) != restrictions.end()) {
                    ++var;
                }
                directions[fromLeft] = -var;
                for (std::size_t iter = left; iter <= dst; ++iter) {
                    leftIndent[iter].push_back(var);
                }
            }

            if (dst - right == 1) {
                directions[fromRight] = 0;
            } else {
                std::unordered_set<std::size_t> restrictions;
                for (std::size_t iter = right; iter <= dst; ++iter) {
                    for (const auto & indentIter : rightIndent[iter]) {
                        restrictions.insert(indentIter); 
                    } 
                }
                std::size_t var = 1;
                while (restrictions.find(var) != restrictions.end()) {
                    ++var;
                }
                directions[fromRight] = var;
                for (std::size_t iter = right; iter <= dst; ++iter) {
                    rightIndent[iter].push_back(var);
                }
            }
        }
        return directions;
    }
        std::string formatFloat(float v) {
            std::ostringstream oss;
            oss << std::setprecision(9) << v;
            return oss.str();
        }
        std::string nodeToDot(std::size_t idx, const Ops & op, const std::optional<float> & value, const std::optional<std::size_t> & reg, const std::pair<std::size_t, std::size_t> & x_y) {
            std::string line = " " + std::to_string(idx) + " [label=\"" + std::to_string(idx) + ": " + toStr(op);
            if (value) {
                line += " = " + formatFloat(*value) + ";";
            }
            if (reg) {
                line += "Reg = " + std::to_string(*reg);
            }
            const std::string x = std::to_string(x_y.first);
            const std::string y = std::to_string(x_y.second);
            line += "\", pos=\"" + std::to_string(1000) + "," + y + "\"];\n";
            return line;
        }

        std::string edgeToDot(std::size_t src, std::size_t dst, std::map<std::pair<std::size_t, std::size_t>, int> & directions, const std::vector<std::pair<std::size_t, std::size_t>> & coords) {
            std::vector<std::pair<std::size_t, std::size_t>> edgePos;
            int way = 0;
            if (directions[{src, dst}] > 0) {
                way = 216;
            } else if (directions[{src, dst}] < 0) {
                way = -216;
            }
            edgePos.push_back({coords[dst].first + way, coords[dst].second + 18});
            edgePos.push_back({coords[src].first + way, coords[src].second - 18});
            edgePos.push_back({coords[src].first + way, coords[src].second - 18});
            edgePos.push_back({coords[src].first + way, coords[src].second - 18});
            edgePos.push_back({coords[src].first + way + directions[{src, dst}] * 10, coords[src].second - 18});
            edgePos.push_back({coords[src].first + way + directions[{src, dst}] * 10, coords[src].second - 18});
            edgePos.push_back({coords[dst].first + way + directions[{src, dst}] * 10, coords[dst].second + 18});
            edgePos.push_back({coords[dst].first + way + directions[{src, dst}] * 10, coords[dst].second + 18});
            edgePos.push_back({coords[dst].first + way + directions[{src, dst}] * 10, coords[dst].second + 18});
            edgePos.push_back({coords[dst].first + way + directions[{src, dst}] * 10, coords[dst].second + 18});
            edgePos.push_back({coords[dst].first + way + way/216, coords[dst].second + 18});
            std::string result = std::to_string(src) + " -> " + std::to_string(dst) + " [pos=\"e,";
            for (const auto & [x, y] : edgePos) {
                result += std::to_string(x) + "," + std::to_string(y) + " ";
            }
            result += "\"];\n";
            return result;
        }
    }

    const std::string Graph::toDot() const {
        std::map<std::pair<std::size_t, std::size_t>, int> directions = evalDirs(incWays());

        const std::size_t width = 2000;
        const std::size_t center = width / 2;

        std::vector<std::pair<std::size_t, std::size_t>> coords(size());
        for (std::size_t idx = 0; idx < size(); ++idx) {
            coords[idx].first = center;
            coords[idx].second = (size() - idx) * 50;
        }
        std::string nodes;
        for (std::size_t idx = 0; idx < _ops.size(); ++idx) {
            const std::optional<float> value = hasValues() ? std::optional<float>(_values[idx]) : std::nullopt;
            const std::optional<std::size_t>  regs = hasRegs() ? std::optional<std::size_t>(_regs[idx]) : std::nullopt;
            nodes += nodeToDot(idx, _ops[idx], value, regs, coords[idx]);
        }
        std::string edges;
        for (std::size_t src = 0; src < _ways.size(); ++src) {
            for (const auto & dst : _ways[src]) {
                edges += edgeToDot(src, dst, directions, coords);
            }
        }

        std::string header = 
        "digraph G {\n"
        "    splines=ortho;\n"
        "    layout=nop2;\n\n"
        "  node [\n"
        "    shape=box,\n"
        "    width=6,\n"
        "  ];\n\n"
        "  edge [\n"
        "    constraint=false\n"
        "  ];\n\n";
    
        return header + nodes + edges + "}\n";
    }

    const std::vector<Ops> buildOps(std::mt19937 & gen, const unsigned size) {
        std::vector<Ops> ops;
        ops.push_back(Ops::INIT);
        for (std::size_t idx = 1; idx < size; ++idx) {
            ops.push_back(getOp(0, idx - 1, gen));
        }
        return ops;
    }

    const std::vector<std::vector<std::size_t>> reverseWays(const std::vector<std::vector<std::size_t>> & ways) {
        std::vector<std::vector<std::size_t>> sources(ways.size());
        for (std::size_t idx = 0; idx < ways.size(); ++idx) {
            for (const auto & dst : ways[idx]) {
                sources[dst].push_back(idx);
            }
        }
        return sources;
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
        _ways(buildWays(gen, size, _ops)) {
            _incoming_ways = reverseWays(_ways);
        }
    
    const std::vector<std::size_t> evalSores(const std::vector<std::size_t> & partition, const std::map<std::vector<std::size_t>, std::size_t> & map) {
        const std::vector<Transition> transitions = enumerateTransitions(partition);
        std::vector<std::size_t> scores;
        for (const auto & tr : transitions) {
            std::size_t sufScore = (map.find(tr._target) != map.end()) ? map.at(tr._target) : 0;
            const std::size_t score = tr._weight * sufScore;
            scores.push_back(score);
        }
        return scores;
    }

    const Transition chooseWay(const std::vector<Transition> & transitions, std::mt19937 & gen, const std::vector<std::size_t> & scores) {
        std::uniform_int_distribution<std::size_t> rollDist(0, std::reduce(scores.begin(), scores.end()) - 1);
        const std::size_t roll = rollDist(gen);

        std::size_t accumulated = 0;
        for (std::size_t idx = 0; idx < transitions.size(); ++idx) {
            accumulated += scores[idx];
            if (roll < accumulated) {
                return transitions[idx];
            }
        }
        return transitions.back();
    }

    const std::pair<std::size_t, std::size_t> chooseSources(const Transition & chosen, const std::vector<std::vector<std::size_t>> & components, std::mt19937 & gen) {
        const std::vector<std::size_t> compA = components[chosen._src1];
        if (chosen._kind == TransitionKind::Same) {
            std::uniform_int_distribution<std::size_t> fisrtSel(0, compA.size() - 1);
            std::uniform_int_distribution<std::size_t> secondSel(0, compA.size() - 2);
            const std::size_t fisrtIdx = fisrtSel(gen);
            std::size_t secondIdx = secondSel(gen);
            if (secondIdx == fisrtIdx) {
                ++secondIdx;
            }
            return {compA[fisrtIdx], compA[secondIdx]};
        } else {
            const std::vector<std::size_t> compB = components[chosen._src2];
            std::uniform_int_distribution<std::size_t> selA(0, compA.size() - 1);
            std::uniform_int_distribution<std::size_t> selB(0, compB.size() - 1);
            return {compA[selA(gen)], compB[selB(gen)]};
        }
    }

    std::vector<std::vector<std::size_t>> updateComponents(const std::vector<std::vector<std::size_t>> & oldComponents, const Transition & chosen, std::size_t k) {
        std::vector<std::vector<std::size_t>> components = oldComponents;
        std::vector<std::size_t> & compA = components[chosen._src1];
        if (chosen._kind == TransitionKind::Same) {
            compA.push_back(k);
        } else {
            std::vector<std::size_t> & compB = components[chosen._src2];
            std::vector<std::size_t> merged = compA;
            merged.insert(merged.end(), compB.begin(), compB.end());
            merged.push_back(k);

            const std::size_t first = std::max(chosen._src1, chosen._src2);
            const std::size_t second = std::min(chosen._src1, chosen._src2);

            components.erase(components.begin() + first);
            components.erase(components.begin() + second);
            components.push_back(merged);
        }

        std::stable_sort(components.begin(), components.end(), 
            [](const auto & lhs, const auto & rhs) {
                return lhs.size() > rhs.size();
        });
        return components;
    }

    Graph buildGraph(std::mt19937 & gen, const unsigned size) {
        std::vector<Ops> ops(size);
        std::vector<std::vector<std::size_t>> ways(size);
        std::vector<std::vector<std::size_t>> sources(size);

        ops[0] = Ops::INIT;

        const std::vector<std::map<std::vector<std::size_t>, std::size_t>> dp = buildForwardDp(size);
        const std::vector<std::map<std::vector<std::size_t>, std::size_t>> suf = buildSuffixDp(size, dp);

        std::vector<std::vector<std::size_t>> components{{0}};
        std::vector<std::size_t> partition{1};

        std::uniform_int_distribution<std::size_t> opSelector(1, static_cast<std::size_t>(Ops::COUNT) - 1);
        for (std::size_t k = 1; k < size; ++k) {
            const std::vector<Transition> transitions = enumerateTransitions(partition);
            const std::vector<std::size_t> scores = evalSores(partition, suf[k+1]);
            const Transition & chosen = chooseWay(transitions, gen, scores);

            if (chosen._kind == TransitionKind::Leaf) {
                ops[k] = Ops::INIT;
                components.push_back({k});
            } else {
                const auto [src1, src2] = chooseSources(chosen, components, gen);
                ops[k] = static_cast<Ops>(opSelector(gen));
                ways[src1].push_back(k);
                ways[src2].push_back(k);
                sources[k].push_back(src1);
                sources[k].push_back(src2);
                components = updateComponents(components, chosen, k);
            }
            partition.clear();
            for (const auto & component : components) {
                partition.push_back(component.size());
            }   
        }
        return Graph(ops, ways, sources, {}, {});
    }
    
    Graph::Graph(const std::vector<Ops> & ops,
                const std::vector<std::vector<std::size_t>> & ways,
                const std::vector<std::vector<std::size_t>> & incWays,
                const std::vector<float> & values,
                const std::vector<std::size_t> & regs):
         _ops(ops),
        _ways(ways),
        _incoming_ways(incWays),
        _values(values),
        _regs(regs) {}

    void Graph::print(const bool & log) const {
        if (!log) {
            return;
        }
        for (std::size_t idx = 0; idx < size(); ++idx) {
            std::cout <<"node № " << idx << " " << toStr(_ops[idx]) << "|";
            std::cout << "incoming nodes: ";
            if (_incoming_ways[idx].size() == 0) {
                std::cout << " - ";
            }
            for (const auto & node : _incoming_ways[idx]) {
                std::cout << node << " ";
            }
            std::cout << "| outgoing nodes: ";
            if (_ways[idx].size() == 0) {
                std::cout << " - ";
            }
            for (const auto & node : _ways[idx]) {
                std::cout << node << " ";
            }
            if (!_regs.empty()) {
                std::cout << "| using register № " << _regs[idx];
            }
            std::cout << '\n';
        }
    }

    const std::vector<std::size_t> uniteWays(const std::vector<std::size_t> & ways, const std::size_t & base) {
        std::vector<std::size_t> result;
        for (const auto & src : ways) {
            result.push_back(src + base);
        }
        return result;
    }

    const Graph uniteGraph(const std::vector<Graph> & graphs) {
        std::vector<Ops> ops;
        std::vector<std::vector<std::size_t>> ways;
        std::vector<std::vector<std::size_t>> incWays;
        std::vector<float> values;
        for (const auto & graph : graphs) {
            const std::vector<Ops> srcOps = graph.ops();
            const std::vector<float> srcValues = graph.values();
            const std::vector<std::vector<std::size_t>> srcWays = graph.ways();
            const std::vector<std::vector<std::size_t>> srcIncWays = graph.incWays();
            const std::size_t base = ways.size();

            for (std::size_t idx = 0; idx < graph.size(); ++idx) {
                ops.push_back(srcOps[idx]);
                values.push_back(srcValues[idx]);
                ways.push_back(uniteWays(srcWays[idx], base));
                incWays.push_back(uniteWays(srcIncWays[idx], base));
            }
        }
        return Graph(ops, ways, incWays, values, {});
    }