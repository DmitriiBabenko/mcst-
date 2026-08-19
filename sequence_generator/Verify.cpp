#include "Verify.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <unordered_set>
#include <boost/lexical_cast.hpp>

std::string formatFloat(float v) {
    std::string suffix = (std::ceil(v) == v) ? ".0f" : "f";
    return boost::lexical_cast<std::string>(v) + suffix;
}

char opSymbol(const Ops & op) {
    switch (op) {
        case Ops::ADD: return '+';
        case Ops::SUB: return '-';
        case Ops::MUL: return '*';
        case Ops::DIV: return '/';
        default:
            throw std::runtime_error("toVerify: unexpected op " + toStr(op) + " for a binary node\n");
    }
}

std::string regVar(std::size_t reg) {
    return "r" + std::to_string(reg);
}

const std::string toVerify(const Graph & graph) {
    if (!graph.hasValues()) {
        throw std::runtime_error("toVerify: graph has no predicted values (run stage2 first)\n");
    }
    if (!graph.hasRegs()) {
        throw std::runtime_error("toVerify: graph has no register assigment (run stage4 first)\n");
    }
    
    const auto & ops = graph.ops();
    const auto & values = graph.values();
    const auto & regs = graph.regs();
    const auto & incWays = graph.incWays();

    std::ostringstream out;
    out << "#include <stdio.h>\n"
        << "#include <assert.h>\n"
        << "int main(void) {\n";
    std::unordered_set<std::size_t> declared;

    for (std::size_t idx = 0; idx < graph.size(); ++idx) {
        const std::size_t reg = regs[idx];
        const std::string var = regVar(reg);
        const float expected = values[idx];

        const bool firstUse = declared.insert(reg).second;
        const std::string decl = firstUse ? "float " : "";

        out << "    /* node " << idx << ": " << toStr(ops[idx]) << " */\n";

        if (ops[idx] == Ops::INIT) {
            out << "    " << decl << var << " = " << formatFloat(expected) << ";\n"; 
        } else {
            const auto & srcs = incWays[idx];
            const std::string a = regVar(regs[srcs[0]]);
            const std::string b = regVar(regs[srcs[1]]);

            out << "    " << decl << var << " = " << a << " " << opSymbol(ops[idx]) << " " << b << ";\n";
        }

        out << "    assert(" << var << " == " << formatFloat(expected) << ");\n\n";
    }

    out << "    printf(\"OK: all " << graph.size() << " nodes verified\\n\");\n"
        << "    return 0;\n"
        << "}\n";

    return out.str();
}