#ifndef VERIFICATIONGENERATOR_H
#define VERIFICATIONGENERATOR_H
#include <vector>
#include <unordered_map>
#include <string>
#include "Node.h"

class VerificationGenerator {
public:
    static std::string generateVerificationCode(const std::vector<Node*> & sorted_nodes, const std::unordered_map<Node*, std::size_t> & rho, unsigned num_registers, unsigned seed);
    static bool compileAndRun(const std::string & cpp_path);

private:
    static std::string generateIncludes();
    static std::string generateHelperFunctions();
    static std::string generateMainFunction(const std::vector<Node*> & sorted_nodes, const std::unordered_map<Node*, std::size_t> & rho, unsigned num_registers, unsigned seed);
    static std::string floatToFullPrecisionString(float v);
    static std::string getOperationSymbol(Ops op);
    static std::string getOperationName(Ops op);
};

#endif //VERIFICATIONGENERATOR_H