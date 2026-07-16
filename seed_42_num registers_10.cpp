#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<float.h>
#include<stdbool.h>
#include<string.h>
#include<cstdint>
#include<time.h>

#define EPSILON 1e-5
#define MAX_REGISTERS 1000
#define SUCCESS_CODE 0
#define VERIFICATION_FAILED 1
#define FLOAT_ERROR 2

bool float_equal(float a, float b, float epsilon) {
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
    }

/*
Component Information:
Component 0:
   Instructions: 0 
 Registers: 3 
 Input registers: 

Component 1:
   Instructions: 1 
 Registers: 7 
 Input registers: 

Component 2:
   Instructions: 2 
 Registers: 9 
 Input registers: 

Component 3:
   Instructions: 3 
 Registers: 1 
 Input registers: 

Component 4:
   Instructions: 4 6 5 
 Registers: 7 5 8 
 Input registers: 

Component 5:
   Instructions: 7 
 Registers: 6 
 Input registers: 

Component 6:
   Instructions: 8 10 11 9 
 Registers: 1 2 0 4 
 Input registers: 

Component 7:
   Instructions: 12 15 14 13 
 Registers: 0 3 8 4 
 Input registers: 

*/

int main() {
   printf("Verification of sequence solution\n");
   printf("Seed: 42\n");
   printf("Registers: 10\n");

    float registers[10];
   bool initialized[10] = {false};
   int verification_errors = 0;
   int total_checks = 0;

   registers[0] = NAN;
   registers[1] = NAN;
   registers[2] = NAN;
   registers[3] = NAN;
   registers[4] = NAN;
   registers[5] = NAN;
   registers[6] = NAN;
   registers[7] = NAN;
   registers[8] = NAN;
   registers[9] = NAN;

    print_header("Executing Instructions");

   registers[3] = 0.000480108662f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   registers[7] = 0.122907817f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   registers[9] = 0.000960217323f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   registers[1] = 0.0614547729f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   registers[7] = 6.37499952f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   registers[8] = -0.626068294f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   if (!initialized[8] || !initialized[7]) {
   print_error("Instruction 6: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[8];
   float src2 = registers[7];
   float  result = src1 * src2;
   registers[5] = result;
   initialized[5] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 5, 8, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -3.99118519f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_1: expected %.8f, got %.8f\n", -3.99118519f, result);
       verification_errors++;
   } else {
       print_success("reg_5_1 matches: ");       printf("                       %.8f", result);
   }

   registers[6] = 0.000480108662f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[1] = -7.61614656f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   registers[4] = -0.00835700613f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   if (!initialized[1] || !initialized[4]) {
   print_error("Instruction 10: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[4];
 result = src1 - src2;
   registers[2] = result;
   initialized[2] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 2, 1, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -7.60778952f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_1: expected %.8f, got %.8f\n", -7.60778952f, result);
       verification_errors++;
   } else {
       print_success("reg_2_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[2] || !initialized[4]) {
   print_error("Instruction 11: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[4];
 result = src1 - src2;
   registers[0] = result;
   initialized[0] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 0, 2, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -7.59943247f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_1: expected %.8f, got %.8f\n", -7.59943247f, result);
       verification_errors++;
   } else {
       print_success("reg_0_1 matches: ");       printf("                       %.8f", result);
   }

   registers[0] = 15.8505659f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[4] = -0.0234374925f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   if (!initialized[0] || !initialized[4]) {
   print_error("Instruction 14: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 14");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[8] = result;
   initialized[8] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 8, 0, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -676.291016f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_2: expected %.8f, got %.8f\n", -676.291016f, result);
       verification_errors++;
   } else {
       print_success("reg_8_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[8] || !initialized[0]) {
   print_error("Instruction 15: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[8];
src2 = registers[0];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 8, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -692.141602f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_2: expected %.8f, got %.8f\n", -692.141602f, result);
       verification_errors++;
   } else {
       print_success("reg_3_2 matches: ");       printf("                       %.8f", result);
   }


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[0], 15.8505659f, EPSILON)) {
printf("[ERROR] Final reg[0] mismatch: expected 15.8505659, got %.8f\n", registers[0]);
       verification_errors++;
   } else {
       print_success("Final reg[0] matches: 15.8505659");
   }

   total_checks++;
   if (!float_equal(registers[1], -7.61614656f, EPSILON)) {
printf("[ERROR] Final reg[1] mismatch: expected -7.61614656, got %.8f\n", registers[1]);
       verification_errors++;
   } else {
       print_success("Final reg[1] matches: -7.61614656");
   }

   total_checks++;
   if (!float_equal(registers[2], -7.60778952f, EPSILON)) {
printf("[ERROR] Final reg[2] mismatch: expected -7.60778952, got %.8f\n", registers[2]);
       verification_errors++;
   } else {
       print_success("Final reg[2] matches: -7.60778952");
   }

   total_checks++;
   if (!float_equal(registers[3], -692.141602f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected -692.141602, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: -692.141602");
   }

   total_checks++;
   if (!float_equal(registers[4], -0.0234374925f, EPSILON)) {
printf("[ERROR] Final reg[4] mismatch: expected -0.0234374925, got %.8f\n", registers[4]);
       verification_errors++;
   } else {
       print_success("Final reg[4] matches: -0.0234374925");
   }

   total_checks++;
   if (!float_equal(registers[5], -3.99118519f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected -3.99118519, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: -3.99118519");
   }

   total_checks++;
   if (!float_equal(registers[6], 0.000480108662f, EPSILON)) {
printf("[ERROR] Final reg[6] mismatch: expected 0.000480108662, got %.8f\n", registers[6]);
       verification_errors++;
   } else {
       print_success("Final reg[6] matches: 0.000480108662");
   }

   total_checks++;
   if (!float_equal(registers[7], 6.37499952f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected 6.37499952, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: 6.37499952");
   }

   total_checks++;
   if (!float_equal(registers[8], -676.291016f, EPSILON)) {
printf("[ERROR] Final reg[8] mismatch: expected -676.291016, got %.8f\n", registers[8]);
       verification_errors++;
   } else {
       print_success("Final reg[8] matches: -676.291016");
   }

   total_checks++;
   if (!float_equal(registers[9], 0.000960217323f, EPSILON)) {
printf("[ERROR] Final reg[9] mismatch: expected 0.000960217323, got %.8f\n", registers[9]);
       verification_errors++;
   } else {
       print_success("Final reg[9] matches: 0.000960217323");
   }

   print_header("Verification Summary");
   printf("Total checks performed: %d\n", total_checks);
   printf("Verification errors: %d\n", verification_errors);
   if (verification_errors == 0) {
       print_success("All verifications passed!");
   } else {
   printf("[ERROR] Verification failed with  %d errors\n", verification_errors);
   print_register_state(registers, 10, "final");
   }

 return SUCCESS_CODE;
}
