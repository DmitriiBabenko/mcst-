#include "VerificationGenerator.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <iostream>

std::string VerificationGenerator::floatToFullPrecisionString(float v) {
    std::ostringstream oss;
    oss << std::setprecision(9) << v;
    std::string s = oss.str();
    if (s.find('.') == std::string::npos && s.find('e') == std::string::npos) {
        s += ".0";
    }
    return s;
}

std::string VerificationGenerator::getOperationSymbol(Ops op) {
    switch (op) {
        case Ops::ADD: return "+";
        case Ops::SUB: return "-";
        case Ops::MUL: return "*";
        case Ops::DIV: return "/";
        case Ops::INIT: return "=";
        default: return "?";
    }
}

std::string VerificationGenerator::getOperationName(Ops op) {
    switch (op) {
        case Ops::ADD: return "ADD";
        case Ops::SUB: return "SUB";
        case Ops::MUL: return "MUL";
        case Ops::DIV: return "DIV";
        case Ops::INIT: return "INIT";
        default: return "UNKNOWN";
    }
}

std::string VerificationGenerator::generateIncludes() {
    return R"(#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <cstdbool>
#include <cstring>
#include <cstdint>)";
}

std::string VerificationGenerator::generateHelperFunctions() {
    return R"(#define EPSILON 1e-5f
static bool float_equal(float a, float b, float isinf) {
    if (std::isnan(a) || std::isnan(b)) {
        return std::isnan(a) && std::isnan(b);
    }

    if (std::isinf(a) || std::isinf(b)) {
        return (std::isinf(a) && std::isinf(b) && ((a > 0) == (b > 0)));
    }
    
    if (a == 0.0f && b == 0.0f) {
        return true;
    } 
    
    uint32_t ia, ib;
    memcpy(&ia, &a, sizeof(float));
    memcpy(&ib, &b, sizeof(float));
    return ia == ib;
    
    }

    void print_header(const char * title) {
        printf("\n== %s ==\n", title);
    }

    void print_success(const char* message) {
        printf("[OK] %s\n", message);
    }

    void print_error(const char* message) {
        printf("[ERROR] %s\n", message);
})";
}

std::string VerificationGenerator::generateMainFunction(
    const std::vector<std::shared_ptr<Node>> & sorted_nodes,
    const std::unordered_map<std::shared_ptr<Node>, std::size_t> & rho,
    unsigned num_registers,
    unsigned seed) {
 
    std::string code = "int main() {\n";
    code += "    std::printf(\"Verification of sequence solution\\n\");\n";
    code += "    std::printf(\"Seed: " + std::to_string(seed) + "\\n\");\n";
    code += "    std::printf(\"Registers: " + std::to_string(num_registers) + "\\n\\n\");\n\n";
 
    code += "    float registers[" + std::to_string(num_registers) + "];\n";
    code += "    int verification_errors = 0;\n";
    code += "    int total_checks = 0;\n\n";
 
    code += "    print_header(\"Executing sequence\");\n\n";
 
    for (std::shared_ptr<Node> v : sorted_nodes) {
        const std::size_t reg = rho.at(v);
        const std::string node_label = std::to_string(v->getId());
        const float predicted = v->getValue();
 
        if (v->getOp() == Ops::INIT) {
            code += "    registers[" + std::to_string(reg) + "] = " +
                     floatToFullPrecisionString(predicted) + "f;\n";
            code += "    std::printf(\"INIT: reg[%d] = %.8f  (node " + node_label +
                     ")\\n\", " + std::to_string(reg) + ", registers[" + std::to_string(reg) + "]);\n\n";
            continue;
        }
 
        const std::vector<std::shared_ptr<Node>> & inc = v->getInc();
 
        code += "    {\n";
        for (std::size_t i = 0; i < inc.size(); ++i) {
            code += "        float src" + std::to_string(i) + " = registers[" +
                     std::to_string(rho.at(inc[i])) + "];";
        }
 
        if (v->getOp() == Ops::DIV) {
            code += "        if (src" + std::to_string(inc.size() - 1) + " == 0.0f) {\n";
            code += "            print_error(\"Division by zero at node " + node_label + "\");\n";
            code += "            return 2;\n";
            code += "        }\n";
        }
 
        std::string expr = "src0";
        for (std::size_t i = 1; i < inc.size(); ++i) {
            expr += " " + getOperationSymbol(v->getOp()) + " src" + std::to_string(i);
        }
 
        code += "        float result = " + expr + ";\n";
        code += "        registers[" + std::to_string(reg) + "] = result;\n";
        code += "        std::printf(\"" + getOperationName(v->getOp()) +
                 ": reg[%d] = %.8f  (node " + node_label + ")\\n\", " +
                 std::to_string(reg) + ", result);\n\n";
 
        code += "        total_checks++;\n";
        code += "        if (!float_equal(result, " + floatToFullPrecisionString(predicted) + "f, EPSILON)) {\n";
        code += "            std::printf(\"[ERROR] Mismatch at node " + node_label +
                 ": expected %.8f, got %.8f\\n\", " + floatToFullPrecisionString(predicted) + "f, result);\n";
        code += "            verification_errors++;\n";
        code += "        } else {\n";
        code += "            print_success(\"node " + node_label + " matches\");\n";
        code += "        }\n";
        code += "    }\n\n";
    }
 
    code += "    print_header(\"Verification Summary\");\n";
    code += "    std::printf(\"Total checks performed: %d\\n\", total_checks);\n";
    code += "    std::printf(\"Verification errors: %d\\n\", verification_errors);\n";
    code += "    if (verification_errors == 0) {\n";
    code += "        print_success(\"All verifications passed!\");\n";
    code += "        return 0;\n";
    code += "    }\n";
    code += "    print_error(\"Verification failed\");\n";
    code += "    return 1;\n";
    code += "}\n";
 
    return code;
}
 
std::string VerificationGenerator::generateVerificationCode(
    const std::vector<std::shared_ptr<Node>> & sorted_nodes,
    const std::unordered_map<std::shared_ptr<Node>, std::size_t> & rho,
    unsigned num_registers,
    unsigned seed) {
 
    const std::string path = "seed_" + std::to_string(seed) + "_regs_" + std::to_string(num_registers) + "_verify.cpp";
    std::ofstream file(path);
    if (!file.is_open()) {
        return "";
    }
 
    file << generateIncludes() << "\n\n";
    file << generateHelperFunctions() << "\n\n";
    file << generateMainFunction(sorted_nodes, rho, num_registers, seed);
    file.close();
 
    return path;
}
 
bool VerificationGenerator::compileAndRun(const std::string & cpp_path) {
    const std::string exe_path = cpp_path.substr(0, cpp_path.size() - 4);
 
    const std::string compile_cmd = "g++ -O0 -o \"" + exe_path + "\" \"" + cpp_path + "\"";
    std::cout << "Compiling verification code: " << cpp_path << "\n";
    if (const int compile_result = std::system(compile_cmd.c_str()); compile_result != 0) {
        std::cerr << "Compilation failed for " << cpp_path << "\n";
        return false;
    }
 
    std::cout << "Compilation successful, running " << exe_path << "\n=== Running Verification ===\n";
    const std::string run_cmd = "./\"" + exe_path + "\"";
    std::system(run_cmd.c_str());
    return true;
}