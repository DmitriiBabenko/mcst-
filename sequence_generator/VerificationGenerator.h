#pragma once
#include "Instruction.h"
#include "DependencyAnalysis.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <sstream>

std::string floatToFullPrecisionString(float v) {
    std::ostringstream oss;
    oss << std::setprecision(9) << v;
    std::string s = oss.str();
    if (s.find('.') == std::string::npos) {
        s += ".0";
    }
    return s;
}
class VerificationGenerator {
private:
    struct VerificationData {
        std::vector<Instruction> instructions;
        std::unordered_map<std::string, float> predicted_values;
        std::vector<Component> components;
        unsigned num_registers;
        unsigned seed;
    };

public:
    static bool generateVerificationCode(
        const std::vector<Instruction> & instructions,
        const std::unordered_map<std::string, float> & predicted_values,
        const std::vector<Component> & components,
        unsigned num_registers,
        unsigned seed);
private:
    static std::string generateIncludes();
    static std::string generateConstants();
    static std::string generateHelperFunctions();
    static std::string generateMainFunction(const VerificationData& data);
    static std::string generateInitialization(const VerificationData & data);
    static std::string generateInstructionExecution(const VerificationData& data);
    static std::string generateVerification(const VerificationData& data);
    static std::string generateComponentInfo(const std::vector<Component>& components);

    static std::string getOperationSymbol(Ops op);
    static std::string getOperationName(Ops op);
    static std::string findRegisterFinalValue(unsigned reg,
        const std::unordered_map<std::string, float> & values,
        const std::vector<Instruction> & instructions);
    static std::vector<std::pair<std::string, float>> getIntermediateValues(
        const std::unordered_map<std::string, float> & values);
};

bool VerificationGenerator::generateVerificationCode(
    const std::vector<Instruction> & instructions,
    const std::unordered_map<std::string, float> & predicted_values,
    const std::vector<Component> & components,
    unsigned num_registers,
    unsigned seed) {
    VerificationData data{instructions, predicted_values, components, num_registers, seed};

    std::ofstream file("seed_" + std::to_string(seed) + "_num registers_" + std::to_string(num_registers) + ".cpp");

    assert(file.is_open());

    file << generateIncludes() << "\n\n";
    file << generateConstants() << "\n\n";
    file << generateHelperFunctions() << "\n\n";
    file << generateComponentInfo(components) << "\n\n";
    file << generateMainFunction(data);

    file.close();
    return true;
}

std::string VerificationGenerator::generateIncludes() {
    return R"(#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<float.h>
#include<stdbool.h>
#include<string.h>
#include<cstdint>
#include<time.h>)";
}

std::string VerificationGenerator::generateConstants() {
    return R"(#define EPSILON 1e-5
#define MAX_REGISTERS 1000
#define SUCCESS_CODE 0
#define VERIFICATION_FAILED 1
#define FLOAT_ERROR 2)";
}

std::string VerificationGenerator::generateHelperFunctions() {
    return R"(bool float_equal(float a, float b, float epsilon) {
    if (isnan(a) || isnan(b)) {
        return isnan(a) && isnan(b);
    }

    if (isinf(a) || isinf(b)) {
        return (isinf(a) && isinf(b) && ((a > 0) == (b > 0)));
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
    }

    void print_warning(const char* message) {
        printf("[WARNING] %s\n", message);
    }

    void print_register_state(float * registers, int num_regs, const char* stage) {
        printf("\nRegister state at %s:\n", stage);
        for (int i = 0; i < num_regs; i++) {
            if (isnan(registers[i])) {
                printf("reg[%d] = NaN\n", i);
            } else if (isinf(registers[i])) {
                printf("reg[%d] = %sInf\n", i, registers[i] > 0 ? "+" : "-");
            } else {
                printf("reg[%d] = %.8f\n", i, registers[i]);
            }
        }
    })";
}

std::string VerificationGenerator::generateMainFunction(const VerificationData & data) {
    std::string code = "int main() {\n";
    code += "   printf(\"Verification of sequence solution\\n\");\n";
    code += "   printf(\"Seed: " + std::to_string(data.seed) + "\\n\");\n";
    code += "   printf(\"Registers: " + std::to_string(data.num_registers) + "\\n\");\n\n";

    code += generateInitialization(data);
    code += "\n" + generateInstructionExecution(data);
    code += "\n" + generateVerification(data);

    code += "\n return SUCCESS_CODE;\n";
    code += "}\n";

    return code;
}

std::string VerificationGenerator::generateInitialization(const VerificationData & data) {
    std::string code = "    float registers[" + std::to_string(data.num_registers) + "];\n";
    code += "   bool initialized[" + std::to_string(data.num_registers) + "] = {false};\n";
    code += "   int verification_errors = 0;\n";
    code += "   int total_checks = 0;\n\n";

    for (unsigned i = 0; i < data.num_registers; i++) {
        std::string init_name = "reg_" + std::to_string(i) + "_input";
        auto it = data.predicted_values.find(init_name);
        if (it != data.predicted_values.end()) {
            code += "   registers[" + std::to_string(i) + "] = " +
                    floatToFullPrecisionString(it->second) + "f; \n";
            code += "   initialized[" + std::to_string(i) + "] = true;\n";
        } else {
            code += "   registers[" + std::to_string(i) + "] = NAN;\n";
        }
    }

    return code;
}

std::string VerificationGenerator::generateInstructionExecution(const VerificationData & data) {
    bool flag = false;
    std::string code = "    print_header(\"Executing Instructions\");\n\n";

    std::vector<unsigned> versions(data.num_registers, 0);

    for (size_t i = 0; i < data.instructions.size(); i++) {
        const auto & instr = data.instructions[i];

        if (instr.op == Ops::INIT) {
            versions[instr.dest_reg]++;
            std::string var_name = "reg_" + std::to_string(instr.dest_reg) + "_" +
                std::to_string(versions[instr.dest_reg]);

            auto it = data.predicted_values.find(var_name);
            if (it != data.predicted_values.end()) {
                code += "   registers[" + std::to_string(instr.dest_reg) + "] = " +
                    floatToFullPrecisionString(it->second) + "f;\n";
                code += "   initialized[" + std::to_string(instr.dest_reg) + "] = true;\n";
                code += "   printf(\"INIT: reg[%d] = %.8f\\n\", " +
                    std::to_string(instr.dest_reg) + ", registers[" +
                    std::to_string(instr.dest_reg) + "]);\n";
            }
        } else {
            code += "   if (!initialized[" + std::to_string(instr.src_reg1) +
                "] || !initialized[" + std::to_string(instr.src_reg2) + "]) {\n";
            code += "   print_error(\"Instruction " + std::to_string(i) +
                ": Using uninitialized register\");\n";
            code += "   return FLOAT_ERROR;\n";
            code += "   }\n";

            versions[instr.dest_reg]++;
            std::string var_name = "reg_" + std::to_string(instr.dest_reg) + "_" +
                                std::to_string(versions[instr.dest_reg]);
            std::string fstStr = "src1 = registers[" + std::to_string(instr.src_reg1) + "];\n";
            std::string sndStr = "src2 = registers[" + std::to_string(instr.src_reg2) + "];\n";
            std::string addition = "";
            if (!flag) {
                addition = "   float ";
                flag = true;
            }
            code += addition + fstStr;
            code += addition + sndStr;
            std::string operation;

            switch (instr.op) {
                case Ops::ADD:
                    operation = "src1 + src2";
                    break;
                case Ops::SUB:
                    operation = "src1 - src2";
                    break;
                case Ops::MUL:
                    operation = "src1 * src2";
                    break;
                case Ops::DIV:
                    code += "   if (src2 == 0.0f) {\n";
                    code += "       print_error(\"Divizion by zero at instruction " +
                        std::to_string(i) + "\");\n";
                    code += "       return FLOAT_ERROR;\n";
                    code += "   }\n";
                    operation = "src1 / src2";
                    break;
                default:
                    operation = "0.0f";
            }

            code += addition + " result = " + operation + ";\n";
            code += "   registers[" + std::to_string(instr.dest_reg) + "] = result;\n";
            code += "   initialized[" + std::to_string(instr.dest_reg) + "] = true;\n";

            code += "   printf(\"" + getOperationName(instr.op) +
                ": reg[%d] = reg[%d] " + getOperationSymbol(instr.op) +
                " reg[%d] = %.8f " + getOperationSymbol(instr.op) +
                " %.8f = %.8f\\n\", ";
            code += std::to_string(instr.dest_reg) + ", " +
                std::to_string(instr.src_reg1) + ", " +
                    std::to_string(instr.src_reg2) + ", src1, src2, result);\n";

            auto it = data.predicted_values.find(var_name);
            if (it != data.predicted_values.end()) {
                code += "   total_checks++;\n";
                code += "   if (!float_equal(result, " + floatToFullPrecisionString(it->second) +
                    "f, EPSILON)) {\n";
                code += "   printf(\"[ERROR] Mismatch at " + var_name + ": expected %.8f, got %.8f\\n\", " + floatToFullPrecisionString(it->second) + "f, result);\n";
                code += "       verification_errors++;\n";
                code += "   } else {\n";
                code += "       print_success(\"" + var_name + " matches: \");";
                code += "       printf(\"                       %.8f\", result);\n";
                code += "   }\n";
            }
        }
        code += "\n";
    }

    return code;
}

std::string VerificationGenerator::generateVerification(const VerificationData& data) {
    std::string code = "    print_header(\"Final Verification\");\n\n";

    for (unsigned reg = 0; reg < data.num_registers; reg++) {
        std::string final_value = findRegisterFinalValue(reg, data.predicted_values, data.instructions);

        if (!final_value.empty()) {
            code += "   total_checks++;\n";
            code += "   if (!float_equal(registers[" + std::to_string(reg) +
                "], " + final_value + "f, EPSILON)) {\n";
            code += "printf(\"[ERROR] Final reg[" + std::to_string(reg) + "] mismatch: expected " + final_value + ", got %.8f\\n\", registers[" + std::to_string(reg) + "]);\n";
            code += "       verification_errors++;\n";
            code += "   } else {\n";
            code += "       print_success(\"Final reg[" + std::to_string(reg) +
                "] matches: " + final_value + "\");\n";
            code += "   }\n\n";
        }
    }

    code += "   print_header(\"Verification Summary\");\n";
    code += "   printf(\"Total checks performed: %d\\n\", total_checks);\n";
    code += "   printf(\"Verification errors: %d\\n\", verification_errors);\n";
    code += "   if (verification_errors == 0) {\n";
    code += "       print_success(\"All verifications passed!\");\n";
    code += "   } else {\n";
    code += "   printf(\"[ERROR] Verification failed with  %d errors\\n\", verification_errors);\n";
    code += "   print_register_state(registers, " +
        std::to_string(data.num_registers) + ", \"final\");\n";
    code += "   }\n";

    return code;
}
std::string VerificationGenerator::generateComponentInfo(const std::vector<Component> & components) {
    std::string code = "/*\nComponent Information:\n";
    for (size_t i = 0; i < components.size(); i++) {
        code += "Component " + std::to_string(i) + ":\n";
        code += "   Instructions: ";
        for (unsigned idx : components[i].instruction_indices) {
            code += std::to_string(idx) + " ";
        }
        code += "\n Registers: ";
        for (unsigned reg : components[i].involved_regs) {
            code += std::to_string(reg) + " ";
        }
        code += "\n Input registers: ";
        for (unsigned reg : components[i].input_regs) {
            code += std::to_string(reg) += " ";
        }
        code += "\n\n";
    }
    code += "*/";
    return code;
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
std::string VerificationGenerator::findRegisterFinalValue(unsigned reg,
    const std::unordered_map<std::string, float> & values,
    const std::vector<Instruction> & instructions) {

    unsigned max_version = 0;
    for (const auto & instr : instructions) {
        if (instr.dest_reg == reg) {
            max_version++;
        }
    }
    if (max_version > 0) {
        std::string var_name = "reg_" + std::to_string(reg) + "_" + std::to_string(max_version);
        auto it = values.find(var_name);
        if (it != values.end()) {
            return floatToFullPrecisionString(it->second);
        }
    }
    std::string input_name = "reg_" + std::to_string(reg) + "_input";
    auto it = values.find(input_name);
    if (it != values.end()) {
        return floatToFullPrecisionString(it->second);
    }
    return "";
}