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
    std::printf("Registers: 5\n\n");

    float registers[5];
    int verification_errors = 0;
    int total_checks = 0;

    print_header("Executing sequence");

    registers[0] = -19.434082f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = 19.4299316f;
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
        if (!float_equal(result, -1.00021362f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", -1.00021362f, result);
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
        if (!float_equal(result, 20.4301453f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 20.4301453f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    registers[4] = 10476474.0f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 4, registers[4]);

    registers[0] = -9.41158502e+09f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 0, registers[0]);

    {
        float src0 = registers[4];        float src1 = registers[0];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[1] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 1, result);

        total_checks++;
        if (!float_equal(result, -0.00111314666f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", -0.00111314666f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    registers[2] = -1.85827661f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 2, registers[2]);

    registers[4] = -0.00390625745f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 4, registers[4]);

    {
        float src0 = registers[2];        float src1 = registers[4];        float result = src0 - src1;
        registers[0] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 2)\n", 0, result);

        total_checks++;
        if (!float_equal(result, -1.85437036f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", -1.85437036f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
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
