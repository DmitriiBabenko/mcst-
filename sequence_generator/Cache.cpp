#include "Cache.h"
#include <boost/json.hpp>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace json = boost::json;

namespace {
    json::value opsToJson(const std::vector<Ops> & ops) {
        json::array arr;
        arr.reserve(ops.size());
        std::transform(ops.begin(), ops.end(), std::back_inserter(arr), [](const Ops & op) {return json::value(static_cast<int>(op));});
        return arr;
    }

    std::vector<Ops> opsFromJson(const json::value & v) {
        const auto & arr = v.as_array();
        std::vector<Ops> ops;
        ops.reserve(arr.size());
        std::transform(arr.begin(), arr.end(), std::back_inserter(ops), [](const json::value & item) {return static_cast<Ops>(item.to_number<int>());});
        return ops;
    }

    json::value rowToJson(const std::vector<std::size_t> & row) {
        json::array inner;
        inner.reserve(row.size());
        std::transform(row.begin(), row.end(), std::back_inserter(inner), [](std::size_t dst) { return json::value(static_cast<std::uint64_t>(dst));});
        return inner;
    }

    json::value waysToJson(const std::vector<std::vector<std::size_t>> & ways) {
        json::array outer;
        outer.reserve(ways.size());
        std::transform(ways.begin(), ways.end(), std::back_inserter(outer), rowToJson);
        return outer;
    }

    std::vector<std::size_t> rowFromJson(const json::value & rowVal) {
        const auto & inner = rowVal.as_array();
        std::vector<std::size_t> row;
        row.reserve(inner.size());
        std::transform(inner.begin(), inner.end(), std::back_inserter(row), [](const json::value & item) {return static_cast<std::size_t>(item.to_number<std::uint64_t>());});
        return row;
    }

    std::vector<std::vector<std::size_t>> waysFromJson(const json::value & v) {
        const auto & outer = v.as_array();
        std::vector<std::vector<std::size_t>> ways;
        ways.reserve(outer.size());
        std::transform(outer.begin(), outer.end(), std::back_inserter(ways), rowFromJson);
        return ways;
    }

    json::value valuesToJson(const std::vector<float> & values) {
        json::array arr;
        arr.reserve(values.size());
        std::transform(values.begin(), values.end(), std::back_inserter(arr), [](float v) {return json::value(static_cast<double>(v));});
        return arr;
    }

    json::value regsToJson(const std::vector<std::size_t> & regs) {
        json::array arr;
        arr.reserve(regs.size());
        std::transform(regs.begin(), regs.end(), std::back_inserter(arr), [](std::size_t v) {return json::value(static_cast<std::uint64_t>(v));});
        return arr;
    }

    std::vector<float> valuesFromJson(const json::value & v) {
        const auto & arr = v.as_array();
        std::vector<float> values;
        values.reserve(arr.size());
        std::transform(arr.begin(), arr.end(), std::back_inserter(values), [](const json::value & item) { return static_cast<float>(item.to_number<double>());});
        return values;
    }

    std::vector<std::size_t> regsFromJson(const json::value & v) {
        const auto & arr = v.as_array();
        std::vector<std::size_t> values;
        values.reserve(arr.size());
        std::transform(arr.begin(), arr.end(), std::back_inserter(values), [](const json::value & item) { return item.to_number<std::size_t>();});
        return values;
    }

    template <typename T, typename F>
    auto andThen(T val, F && f) -> decltype(f(val)) {
        return f(val);
    }

    std::string readFile(const std::string & path) {
        if (path.empty()) {
            throw std::runtime_error("file path is empty");
        }
        std::ifstream in(path);
        std::stringstream buffer;
        buffer << in.rdbuf();
        return buffer.str();
    }

    json::value parseJson(const std::string & content) {
        return json::parse(content);
    }

    Graph graphFromJson(const json::value & parsed) {
        const auto & root = parsed.as_object();
        auto ops = opsFromJson(root.at("ops"));
        auto ways = waysFromJson(root.at("ways"));
        auto incWays = waysFromJson(root.at("incWays"));
        auto values = root.contains("values") ? valuesFromJson(root.at("values")) : std::vector<float>{};
        auto regs = root.contains("regs") ? regsFromJson(root.at("regs")) : std::vector<std::size_t>{};
        return Graph(std::move(ops), std::move(ways), std::move(incWays), std::move(values), std::move(regs));
    }

    const std::vector<Graph> vectorFromJson(const json::value & parsed) {
        const auto & arr = parsed.as_array();
        std::vector<Graph> graph;
        graph.reserve(arr.size());
        std::transform(arr.begin(), arr.end(), std::back_inserter(graph), [](const json::value & item) { return graphFromJson(item);});
        return graph;
    }

}

const json::object saveComp(const Graph & graph) {
    json::object root;
    root["ops"] = opsToJson(graph.ops());
    root["ways"] = waysToJson(graph.ways());
    root["incWays"] = waysToJson(graph.incWays());
    root["regs"] = regsToJson(graph.regs());
    root["values"] = valuesToJson(graph.values());
    return root;
}

void saveCache(const std::vector<Graph> & graph, const std::string & path) {
    json::array arr;
    arr.reserve(graph.size());
    std::transform(graph.begin(), graph.end(), std::back_inserter(arr), [](Graph g) {return saveComp(g);});
    std::ofstream out(path);
    out << json::serialize(arr);
}

const std::vector<Graph> loadCache(const std::string & path) {
    return andThen(andThen(readFile(path), parseJson), vectorFromJson);
}