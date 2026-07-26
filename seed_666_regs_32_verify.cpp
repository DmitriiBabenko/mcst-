#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <cstdbool>
#include <cstring>
#include <cstdint>

#define EPSILON 1e-5f
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
}

int main() {
    std::printf("Verification of sequence solution\n");
    std::printf("Seed: 666\n");
    std::printf("Registers: 32\n\n");

    float registers[32];
    int verification_errors = 0;
    int total_checks = 0;

    print_header("Executing sequence");

    registers[0] = 0.00906828977f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = 0.00472143572f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    {
        float src0 = registers[0];        float src1 = registers[1];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[2] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 2, result);

        total_checks++;
        if (!float_equal(result, 1.9206636f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 1.9206636f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[2];        float result = src0 - src1;
        registers[3] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 3)\n", 3, result);

        total_checks++;
        if (!float_equal(result, -1.91594219f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", -1.91594219f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[2];        float src1 = registers[3];        if (src1 == 0.0f) {
            print_error("Division by zero at node 4");
            return 2;
        }
        float result = src0 / src1;
        registers[4] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 4)\n", 4, result);

        total_checks++;
        if (!float_equal(result, -1.00246429f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", -1.00246429f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 - src1;
        registers[5] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 5)\n", 5, result);

        total_checks++;
        if (!float_equal(result, 0.00434685405f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 5: expected %.8f, got %.8f\n", 0.00434685405f, result);
            verification_errors++;
        } else {
            print_success("node 5 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[2];        float result = src0 * src1;
        registers[6] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 6)\n", 6, result);

        total_checks++;
        if (!float_equal(result, 0.00906828977f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", 0.00906828977f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[3];        float result = src0 - src1;
        registers[7] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 7)\n", 7, result);

        total_checks++;
        if (!float_equal(result, 1.92501044f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", 1.92501044f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[3];        float result = src0 * src1;
        registers[8] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 8)\n", 8, result);

        total_checks++;
        if (!float_equal(result, -0.00904599763f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", -0.00904599763f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[5];        float src1 = registers[8];        if (src1 == 0.0f) {
            print_error("Division by zero at node 9");
            return 2;
        }
        float result = src0 / src1;
        registers[9] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 9)\n", 9, result);

        total_checks++;
        if (!float_equal(result, -0.480527878f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", -0.480527878f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    {
        float src0 = registers[3];        float src1 = registers[8];        float result = src0 + src1;
        registers[10] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 10)\n", 10, result);

        total_checks++;
        if (!float_equal(result, -1.92498815f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 10: expected %.8f, got %.8f\n", -1.92498815f, result);
            verification_errors++;
        } else {
            print_success("node 10 matches");
        }
    }

    {
        float src0 = registers[2];        float src1 = registers[4];        float result = src0 - src1;
        registers[11] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 11)\n", 11, result);

        total_checks++;
        if (!float_equal(result, 2.92312789f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 11: expected %.8f, got %.8f\n", 2.92312789f, result);
            verification_errors++;
        } else {
            print_success("node 11 matches");
        }
    }

    {
        float src0 = registers[8];        float src1 = registers[9];        if (src1 == 0.0f) {
            print_error("Division by zero at node 12");
            return 2;
        }
        float result = src0 / src1;
        registers[12] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 12)\n", 12, result);

        total_checks++;
        if (!float_equal(result, 0.0188251249f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 12: expected %.8f, got %.8f\n", 0.0188251249f, result);
            verification_errors++;
        } else {
            print_success("node 12 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[11];        if (src1 == 0.0f) {
            print_error("Division by zero at node 13");
            return 2;
        }
        float result = src0 / src1;
        registers[13] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 13)\n", 13, result);

        total_checks++;
        if (!float_equal(result, 0.00161519984f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 13: expected %.8f, got %.8f\n", 0.00161519984f, result);
            verification_errors++;
        } else {
            print_success("node 13 matches");
        }
    }

    {
        float src0 = registers[9];        float src1 = registers[10];        float result = src0 + src1;
        registers[14] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 14)\n", 14, result);

        total_checks++;
        if (!float_equal(result, -2.40551615f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 14: expected %.8f, got %.8f\n", -2.40551615f, result);
            verification_errors++;
        } else {
            print_success("node 14 matches");
        }
    }

    registers[15] = 1.17549449e-38f;
    std::printf("INIT: reg[%d] = %.8f  (node 15)\n", 15, registers[15]);

    registers[16] = -2.98485017f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 16, registers[16]);

    registers[17] = 8.98875713f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 17, registers[17]);

    {
        float src0 = registers[16];        float src1 = registers[17];        float result = src0 + src1;
        registers[18] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 2)\n", 18, result);

        total_checks++;
        if (!float_equal(result, 6.0039072f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 6.0039072f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    registers[19] = 2.03125f;
    std::printf("INIT: reg[%d] = %.8f  (node 3)\n", 19, registers[19]);

    {
        float src0 = registers[17];        float src1 = registers[18];        float result = src0 - src1;
        registers[20] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 4)\n", 20, result);

        total_checks++;
        if (!float_equal(result, 2.98484993f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 2.98484993f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[21] = -0.267746121f;
    std::printf("INIT: reg[%d] = %.8f  (node 5)\n", 21, registers[21]);

    registers[22] = -0.0238152072f;
    std::printf("INIT: reg[%d] = %.8f  (node 6)\n", 22, registers[22]);

    {
        float src0 = registers[21];        float src1 = registers[22];        float result = src0 - src1;
        registers[23] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 7)\n", 23, result);

        total_checks++;
        if (!float_equal(result, -0.243930906f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", -0.243930906f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[22];        float src1 = registers[23];        float result = src0 * src1;
        registers[24] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 8)\n", 24, result);

        total_checks++;
        if (!float_equal(result, 0.00580926519f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", 0.00580926519f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[20];        float src1 = registers[22];        float result = src0 + src1;
        registers[25] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 9)\n", 25, result);

        total_checks++;
        if (!float_equal(result, 2.96103477f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 2.96103477f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    {
        float src0 = registers[20];        float src1 = registers[25];        float result = src0 - src1;
        registers[26] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 10)\n", 26, result);

        total_checks++;
        if (!float_equal(result, 0.023815155f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 10: expected %.8f, got %.8f\n", 0.023815155f, result);
            verification_errors++;
        } else {
            print_success("node 10 matches");
        }
    }

    {
        float src0 = registers[22];        float src1 = registers[24];        float result = src0 - src1;
        registers[27] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 11)\n", 27, result);

        total_checks++;
        if (!float_equal(result, -0.0296244733f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 11: expected %.8f, got %.8f\n", -0.0296244733f, result);
            verification_errors++;
        } else {
            print_success("node 11 matches");
        }
    }

    registers[28] = 3.85185989e-34f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 28, registers[28]);

    registers[29] = -1.19834745f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 29, registers[29]);

    registers[30] = -1.87110364f;
    std::printf("INIT: reg[%d] = %.8f  (node 2)\n", 30, registers[30]);

    {
        float src0 = registers[29];        float src1 = registers[30];        float result = src0 - src1;
        registers[31] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 3)\n", 31, result);

        total_checks++;
        if (!float_equal(result, 0.672756195f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 0.672756195f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[30];        float src1 = registers[31];        float result = src0 * src1;
        registers[0] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 4)\n", 0, result);

        total_checks++;
        if (!float_equal(result, -1.25879657f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", -1.25879657f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[5] = 5.00781155f;
    std::printf("INIT: reg[%d] = %.8f  (node 5)\n", 5, registers[5]);

    {
        float src0 = registers[30];        float src1 = registers[31];        float result = src0 - src1;
        registers[3] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 6)\n", 3, result);

        total_checks++;
        if (!float_equal(result, -2.54385996f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", -2.54385996f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[5];        if (src1 == 0.0f) {
            print_error("Division by zero at node 7");
            return 2;
        }
        float result = src0 / src1;
        registers[2] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 7)\n", 2, result);

        total_checks++;
        if (!float_equal(result, -0.251366615f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", -0.251366615f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[30];        float src1 = registers[31];        float result = src0 - src1;
        registers[4] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 8)\n", 4, result);

        total_checks++;
        if (!float_equal(result, -2.54385996f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", -2.54385996f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[31];        float src1 = registers[2];        float result = src0 + src1;
        registers[8] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 9)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 0.42138958f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 0.42138958f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    {
        float src0 = registers[4];        float src1 = registers[8];        float result = src0 + src1;
        registers[1] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 10)\n", 1, result);

        total_checks++;
        if (!float_equal(result, -2.12247038f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 10: expected %.8f, got %.8f\n", -2.12247038f, result);
            verification_errors++;
        } else {
            print_success("node 10 matches");
        }
    }

    registers[11] = 2.00048828f;
    std::printf("INIT: reg[%d] = %.8f  (node 11)\n", 11, registers[11]);

    registers[9] = 0.841322541f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 9, registers[9]);

    registers[10] = -1.68733668f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 10, registers[10]);

    {
        float src0 = registers[9];        float src1 = registers[10];        float result = src0 + src1;
        registers[16] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 2)\n", 16, result);

        total_checks++;
        if (!float_equal(result, -0.846014142f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", -0.846014142f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[10];        float src1 = registers[16];        float result = src0 * src1;
        registers[17] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 3)\n", 17, result);

        total_checks++;
        if (!float_equal(result, 1.42751074f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 1.42751074f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    registers[18] = 16.4590645f;
    std::printf("INIT: reg[%d] = %.8f  (node 4)\n", 18, registers[18]);

    {
        float src0 = registers[17];        float src1 = registers[18];        if (src1 == 0.0f) {
            print_error("Division by zero at node 5");
            return 2;
        }
        float result = src0 / src1;
        registers[21] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 5)\n", 21, result);

        total_checks++;
        if (!float_equal(result, 0.0867309794f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 5: expected %.8f, got %.8f\n", 0.0867309794f, result);
            verification_errors++;
        } else {
            print_success("node 5 matches");
        }
    }

    {
        float src0 = registers[18];        float src1 = registers[21];        float result = src0 * src1;
        registers[23] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 6)\n", 23, result);

        total_checks++;
        if (!float_equal(result, 1.42751074f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", 1.42751074f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    {
        float src0 = registers[9];        float src1 = registers[17];        if (src1 == 0.0f) {
            print_error("Division by zero at node 7");
            return 2;
        }
        float result = src0 / src1;
        registers[20] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 7)\n", 20, result);

        total_checks++;
        if (!float_equal(result, 0.589363396f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", 0.589363396f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[23];        float src1 = registers[20];        float result = src0 - src1;
        registers[25] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 8)\n", 25, result);

        total_checks++;
        if (!float_equal(result, 0.838147342f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", 0.838147342f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[20];        float src1 = registers[25];        if (src1 == 0.0f) {
            print_error("Division by zero at node 9");
            return 2;
        }
        float result = src0 / src1;
        registers[22] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 9)\n", 22, result);

        total_checks++;
        if (!float_equal(result, 0.703173995f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 0.703173995f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    {
        float src0 = registers[16];        float src1 = registers[25];        if (src1 == 0.0f) {
            print_error("Division by zero at node 10");
            return 2;
        }
        float result = src0 / src1;
        registers[24] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 10)\n", 24, result);

        total_checks++;
        if (!float_equal(result, -1.00938594f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 10: expected %.8f, got %.8f\n", -1.00938594f, result);
            verification_errors++;
        } else {
            print_success("node 10 matches");
        }
    }

    {
        float src0 = registers[18];        float src1 = registers[25];        float result = src0 * src1;
        registers[29] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 11)\n", 29, result);

        total_checks++;
        if (!float_equal(result, 13.7951212f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 11: expected %.8f, got %.8f\n", 13.7951212f, result);
            verification_errors++;
        } else {
            print_success("node 11 matches");
        }
    }

    registers[0] = 1.00001955f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[5] = 1.99935234f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 5, registers[5]);

    {
        float src0 = registers[0];        float src1 = registers[5];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[30] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 30, result);

        total_checks++;
        if (!float_equal(result, 0.500171721f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 0.500171721f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[30];        float result = src0 + src1;
        registers[31] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 3)\n", 31, result);

        total_checks++;
        if (!float_equal(result, 1.50019121f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 1.50019121f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    registers[2] = 2.0f;
    std::printf("INIT: reg[%d] = %.8f  (node 4)\n", 2, registers[2]);

    {
        float src0 = registers[30];        float src1 = registers[31];        float result = src0 + src1;
        registers[4] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 5)\n", 4, result);

        total_checks++;
        if (!float_equal(result, 2.00036287f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 5: expected %.8f, got %.8f\n", 2.00036287f, result);
            verification_errors++;
        } else {
            print_success("node 5 matches");
        }
    }

    {
        float src0 = registers[30];        float src1 = registers[31];        if (src1 == 0.0f) {
            print_error("Division by zero at node 6");
            return 2;
        }
        float result = src0 / src1;
        registers[8] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 6)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 0.333405316f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", 0.333405316f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    registers[10] = 2.0f;
    std::printf("INIT: reg[%d] = %.8f  (node 7)\n", 10, registers[10]);

    {
        float src0 = registers[4];        float src1 = registers[8];        float result = src0 * src1;
        registers[21] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 8)\n", 21, result);

        total_checks++;
        if (!float_equal(result, 0.666931629f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", 0.666931629f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[5];        float src1 = registers[4];        if (src1 == 0.0f) {
            print_error("Division by zero at node 9");
            return 2;
        }
        float result = src0 / src1;
        registers[9] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 9)\n", 9, result);

        total_checks++;
        if (!float_equal(result, 0.999494851f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 0.999494851f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[31];        float result = src0 * src1;
        registers[17] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 10)\n", 17, result);

        total_checks++;
        if (!float_equal(result, 1.50022054f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 10: expected %.8f, got %.8f\n", 1.50022054f, result);
            verification_errors++;
        } else {
            print_success("node 10 matches");
        }
    }

    registers[23] = 1.17549449e-38f;
    std::printf("INIT: reg[%d] = %.8f  (node 11)\n", 23, registers[23]);

    print_header("Verification Summary");
    std::printf("Total checks performed: %d\n", total_checks);
    std::printf("Verification errors: %d\n", verification_errors);
    if (verification_errors == 0) {
        print_success("All verifications passed!");
        return 0;
    }
    print_error("Verification failed");
    return 1;
}
