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

    std::vector<float> valuesFromJson(const json::value & v) {
        const auto & arr = v.as_array();
        std::vector<float> values;
        values.reserve(arr.size());
        std::transform(arr.begin(), arr.end(), std::back_inserter(values), [](const json::value & item) { return static_cast<float>(item.to_number<double>());});
        return values;
    }

    template <typename T, typename F>
    auto andThen(std::optional<T> opt, F && f) -> decltype(f(*opt)) {
        if (!opt) {
            return std::nullopt;
        }
        return f(*opt);
    }

    std::optional<std::string> readFile(const std::string & path) {
        if (path.empty()) {
            return std::nullopt;
        }
        std::ifstream in(path);
        if (!in) {
            return std::nullopt;
        }
        std::stringstream buffer;
        buffer << in.rdbuf();
        return buffer.str();
    }

    std::optional<json::value> parseJson(const std::string & content) {
        try {
            return json::parse(content);
        } catch(const std::exception & e) {
            return std::nullopt;
        }
    }

    std::optional<Graph> graphFromJson(const json::value & parsed) {
        const auto & root = parsed.as_object();
        auto ops = opsFromJson(root.at("ops"));
        auto ways = waysFromJson(root.at("ways"));
        auto values = root.contains("values") ? valuesFromJson(root.at("values")) : std::vector<float>{};
        return Graph::fromParts(std::move(ops), std::move(ways), std::move(values));
    }
}

void saveCache(const Graph & graph, const std::string & path) {
    json::object root;
    root["ops"] = opsToJson(graph.ops());
    root["ways"] = waysToJson(graph.ways());
    root["values"] = valuesToJson(graph.values());

    std::ofstream out(path);
    out << json::serialize(root);
}

std::optional<Graph> loadCache(const std::string & path) {
    return andThen(andThen(readFile(path), parseJson), graphFromJson);
}