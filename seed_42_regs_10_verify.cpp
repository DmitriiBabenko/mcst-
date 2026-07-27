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
    std::printf("Seed: 42\n");
    std::printf("Registers: 10\n\n");

    float registers[10];
    int verification_errors = 0;
    int total_checks = 0;

    print_header("Executing sequence");

    registers[0] = 32.0009766f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = 0.000977039337f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 - src1;
        registers[2] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 2)\n", 2, result);

        total_checks++;
        if (!float_equal(result, 32.0f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 32.0f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[2];        float result = src0 + src1;
        registers[3] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 3)\n", 3, result);

        total_checks++;
        if (!float_equal(result, 32.0009766f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 32.0009766f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[2];        float result = src0 * src1;
        registers[4] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 4)\n", 4, result);

        total_checks++;
        if (!float_equal(result, 0.0312652588f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 0.0312652588f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 * src1;
        registers[5] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 5)\n", 5, result);

        total_checks++;
        if (!float_equal(result, 0.0312662125f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 5: expected %.8f, got %.8f\n", 0.0312662125f, result);
            verification_errors++;
        } else {
            print_success("node 5 matches");
        }
    }

    {
        float src0 = registers[2];        float src1 = registers[5];        float result = src0 + src1;
        registers[6] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 6)\n", 6, result);

        total_checks++;
        if (!float_equal(result, 32.0312653f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", 32.0312653f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    {
        float src0 = registers[3];        float src1 = registers[4];        float result = src0 - src1;
        registers[7] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 7)\n", 7, result);

        total_checks++;
        if (!float_equal(result, 31.9697113f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", 31.9697113f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[4];        float src1 = registers[5];        if (src1 == 0.0f) {
            print_error("Division by zero at node 8");
            return 2;
        }
        float result = src0 / src1;
        registers[8] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 8)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 0.999969482f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", 0.999969482f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[7];        float src1 = registers[8];        float result = src0 + src1;
        registers[9] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 9)\n", 9, result);

        total_checks++;
        if (!float_equal(result, 32.9696808f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 32.9696808f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

    registers[0] = 0.000110149384f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = 11.3622751f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    registers[2] = 1.5046342e-36f;
    std::printf("INIT: reg[%d] = %.8f  (node 2)\n", 2, registers[2]);

    registers[3] = -26.6813946f;
    std::printf("INIT: reg[%d] = %.8f  (node 3)\n", 3, registers[3]);

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 - src1;
        registers[4] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 4)\n", 4, result);

        total_checks++;
        if (!float_equal(result, -11.3621655f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", -11.3621655f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[5] = 2.125f;
    std::printf("INIT: reg[%d] = %.8f  (node 5)\n", 5, registers[5]);

    {
        float src0 = registers[3];        float src1 = registers[4];        float result = src0 + src1;
        registers[7] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 6)\n", 7, result);

        total_checks++;
        if (!float_equal(result, -38.04356f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 6: expected %.8f, got %.8f\n", -38.04356f, result);
            verification_errors++;
        } else {
            print_success("node 6 matches");
        }
    }

    {
        float src0 = registers[3];        float src1 = registers[4];        if (src1 == 0.0f) {
            print_error("Division by zero at node 7");
            return 2;
        }
        float result = src0 / src1;
        registers[8] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 7)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 2.3482666f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 7: expected %.8f, got %.8f\n", 2.3482666f, result);
            verification_errors++;
        } else {
            print_success("node 7 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[3];        float result = src0 * src1;
        registers[1] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 8)\n", 1, result);

        total_checks++;
        if (!float_equal(result, -0.00293893926f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 8: expected %.8f, got %.8f\n", -0.00293893926f, result);
            verification_errors++;
        } else {
            print_success("node 8 matches");
        }
    }

    {
        float src0 = registers[4];        float src1 = registers[7];        float result = src0 * src1;
        registers[0] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 9)\n", 0, result);

        total_checks++;
        if (!float_equal(result, 432.257233f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 9: expected %.8f, got %.8f\n", 432.257233f, result);
            verification_errors++;
        } else {
            print_success("node 9 matches");
        }
    }

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
