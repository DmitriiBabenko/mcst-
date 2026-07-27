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
    std::printf("Seed: 5\n");
    std::printf("Registers: 20\n\n");

    float registers[20];
    int verification_errors = 0;
    int total_checks = 0;

    print_header("Executing sequence");

    registers[0] = 1.0625f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = -4.00195312f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 - src1;
        registers[2] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 2)\n", 2, result);

        total_checks++;
        if (!float_equal(result, 5.06445312f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 5.06445312f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    registers[3] = -6.12548828f;
    std::printf("INIT: reg[%d] = %.8f  (node 3)\n", 3, registers[3]);

    {
        float src0 = registers[1];        float src1 = registers[3];        float result = src0 - src1;
        registers[4] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 4)\n", 4, result);

        total_checks++;
        if (!float_equal(result, 2.12353516f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 2.12353516f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[5] = 0.0625914559f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 5, registers[5]);

    registers[6] = 1.08421044e-19f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 6, registers[6]);

    registers[7] = 24.0273438f;
    std::printf("INIT: reg[%d] = %.8f  (node 2)\n", 7, registers[7]);

    {
        float src0 = registers[5];        float src1 = registers[7];        float result = src0 * src1;
        registers[8] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 3)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 1.50390637f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 1.50390637f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[7];        float src1 = registers[8];        float result = src0 - src1;
        registers[9] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 4)\n", 9, result);

        total_checks++;
        if (!float_equal(result, 22.5234375f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 22.5234375f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[10] = 0.503963649f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 10, registers[10]);

    registers[11] = 1128.00427f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 11, registers[11]);

    {
        float src0 = registers[10];        float src1 = registers[11];        float result = src0 * src1;
        registers[12] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 2)\n", 12, result);

        total_checks++;
        if (!float_equal(result, 568.473145f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 568.473145f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    registers[13] = -305.907227f;
    std::printf("INIT: reg[%d] = %.8f  (node 3)\n", 13, registers[13]);

    {
        float src0 = registers[12];        float src1 = registers[13];        float result = src0 + src1;
        registers[14] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 4)\n", 14, result);

        total_checks++;
        if (!float_equal(result, 262.565918f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 262.565918f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[15] = -16.0f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 15, registers[15]);

    registers[16] = -0.0625f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 16, registers[16]);

    {
        float src0 = registers[15];        float src1 = registers[16];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[17] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 17, result);

        total_checks++;
        if (!float_equal(result, 256.0f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 256.0f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[15];        float src1 = registers[16];        float result = src0 * src1;
        registers[18] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 3)\n", 18, result);

        total_checks++;
        if (!float_equal(result, 1.0f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 1.0f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[17];        float src1 = registers[18];        if (src1 == 0.0f) {
            print_error("Division by zero at node 4");
            return 2;
        }
        float result = src0 / src1;
        registers[19] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 4)\n", 19, result);

        total_checks++;
        if (!float_equal(result, 256.0f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 256.0f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[0] = 1.93749905f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 0, registers[0]);

    registers[1] = -0.125000015f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    {
        float src0 = registers[0];        float src1 = registers[1];        float result = src0 - src1;
        registers[3] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 2)\n", 3, result);

        total_checks++;
        if (!float_equal(result, 2.06249905f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 2.06249905f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[0];        float src1 = registers[3];        float result = src0 + src1;
        registers[5] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 3)\n", 5, result);

        total_checks++;
        if (!float_equal(result, 3.99999809f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 3.99999809f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[5];        if (src1 == 0.0f) {
            print_error("Division by zero at node 4");
            return 2;
        }
        float result = src0 / src1;
        registers[7] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 4)\n", 7, result);

        total_checks++;
        if (!float_equal(result, -0.0312500186f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", -0.0312500186f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[8] = 4.00010109f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 8, registers[8]);

    registers[10] = 0.0009765625f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 10, registers[10]);

    {
        float src0 = registers[8];        float src1 = registers[10];        float result = src0 * src1;
        registers[11] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 2)\n", 11, result);

        total_checks++;
        if (!float_equal(result, 0.00390634872f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 0.00390634872f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[8];        float src1 = registers[10];        float result = src0 - src1;
        registers[12] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 3)\n", 12, result);

        total_checks++;
        if (!float_equal(result, 3.99912453f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 3.99912453f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[8];        float src1 = registers[12];        float result = src0 + src1;
        registers[13] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 4)\n", 13, result);

        total_checks++;
        if (!float_equal(result, 7.99922562f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 7.99922562f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[15] = 1.75f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 15, registers[15]);

    registers[16] = 1.21484375f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 16, registers[16]);

    {
        float src0 = registers[15];        float src1 = registers[16];        float result = src0 - src1;
        registers[17] = result;
        std::printf("SUB: reg[%d] = %.8f  (node 2)\n", 17, result);

        total_checks++;
        if (!float_equal(result, 0.53515625f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 0.53515625f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    registers[18] = -0.3125f;
    std::printf("INIT: reg[%d] = %.8f  (node 3)\n", 18, registers[18]);

    {
        float src0 = registers[17];        float src1 = registers[18];        float result = src0 + src1;
        registers[0] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 4)\n", 0, result);

        total_checks++;
        if (!float_equal(result, 0.22265625f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 0.22265625f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[3] = -15.1747875f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 3, registers[3]);

    registers[1] = 1.2611059f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 1, registers[1]);

    {
        float src0 = registers[3];        float src1 = registers[1];        float result = src0 * src1;
        registers[5] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 2)\n", 5, result);

        total_checks++;
        if (!float_equal(result, -19.1370144f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", -19.1370144f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[5];        float result = src0 + src1;
        registers[10] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 3)\n", 10, result);

        total_checks++;
        if (!float_equal(result, -17.8759079f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", -17.8759079f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[3];        float src1 = registers[10];        float result = src0 * src1;
        registers[8] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 4)\n", 8, result);

        total_checks++;
        if (!float_equal(result, 271.263092f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 271.263092f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[12] = 1.04394805f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 12, registers[12]);

    registers[15] = 1.02125895f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 15, registers[15]);

    {
        float src0 = registers[12];        float src1 = registers[15];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[16] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 16, result);

        total_checks++;
        if (!float_equal(result, 1.0222168f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 1.0222168f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[12];        float src1 = registers[16];        if (src1 == 0.0f) {
            print_error("Division by zero at node 3");
            return 2;
        }
        float result = src0 / src1;
        registers[17] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 3)\n", 17, result);

        total_checks++;
        if (!float_equal(result, 1.02125895f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", 1.02125895f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[15];        float src1 = registers[16];        float result = src0 * src1;
        registers[18] = result;
        std::printf("MUL: reg[%d] = %.8f  (node 4)\n", 18, result);

        total_checks++;
        if (!float_equal(result, 1.04394805f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", 1.04394805f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
        }
    }

    registers[1] = -0.0286397524f;
    std::printf("INIT: reg[%d] = %.8f  (node 0)\n", 1, registers[1]);

    registers[5] = -0.0286126472f;
    std::printf("INIT: reg[%d] = %.8f  (node 1)\n", 5, registers[5]);

    {
        float src0 = registers[1];        float src1 = registers[5];        if (src1 == 0.0f) {
            print_error("Division by zero at node 2");
            return 2;
        }
        float result = src0 / src1;
        registers[3] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 2)\n", 3, result);

        total_checks++;
        if (!float_equal(result, 1.00094736f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 2: expected %.8f, got %.8f\n", 1.00094736f, result);
            verification_errors++;
        } else {
            print_success("node 2 matches");
        }
    }

    {
        float src0 = registers[5];        float src1 = registers[3];        if (src1 == 0.0f) {
            print_error("Division by zero at node 3");
            return 2;
        }
        float result = src0 / src1;
        registers[10] = result;
        std::printf("DIV: reg[%d] = %.8f  (node 3)\n", 10, result);

        total_checks++;
        if (!float_equal(result, -0.0285855662f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 3: expected %.8f, got %.8f\n", -0.0285855662f, result);
            verification_errors++;
        } else {
            print_success("node 3 matches");
        }
    }

    {
        float src0 = registers[1];        float src1 = registers[10];        float result = src0 + src1;
        registers[12] = result;
        std::printf("ADD: reg[%d] = %.8f  (node 4)\n", 12, result);

        total_checks++;
        if (!float_equal(result, -0.0572253168f, EPSILON)) {
            std::printf("[ERROR] Mismatch at node 4: expected %.8f, got %.8f\n", -0.0572253168f, result);
            verification_errors++;
        } else {
            print_success("node 4 matches");
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
