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
   Instructions: 0 17 25 27 26 4 22 23 13 14 2 12 8 16 21 1 24 20 7 18 11 9 15 10 6 
 Registers: 11 7 8 12 9 23 31 28 15 27 30 1 4 21 2 25 29 0 20 22 3 14 10 6 19 
 Input registers: 

Component 1:
   Instructions: 3 
 Registers: 5 
 Input registers: 

Component 2:
   Instructions: 5 
 Registers: 24 
 Input registers: 

Component 3:
   Instructions: 19 
 Registers: 26 
 Input registers: 

Component 4:
   Instructions: 28 48 47 31 40 43 45 49 36 32 33 46 44 29 35 41 30 37 38 34 52 42 39 
 Registers: 5 15 7 19 21 2 3 8 13 9 20 14 11 31 0 12 6 1 10 16 18 4 17 
 Input registers: 

Component 5:
   Instructions: 50 
 Registers: 25 
 Input registers: 

Component 6:
   Instructions: 51 
 Registers: 22 
 Input registers: 

Component 7:
   Instructions: 53 62 68 65 76 69 54 63 61 56 59 77 71 64 73 70 58 72 60 57 66 55 
 Registers: 12 5 4 0 22 20 16 15 21 18 27 10 13 2 6 25 1 9 19 14 30 31 
 Input registers: 

Component 8:
   Instructions: 67 
 Registers: 3 
 Input registers: 

Component 9:
   Instructions: 74 
 Registers: 7 
 Input registers: 

Component 10:
   Instructions: 75 
 Registers: 8 
 Input registers: 

Component 11:
   Instructions: 78 86 96 92 82 87 94 90 91 80 101 84 89 79 83 85 81 
 Registers: 14 29 17 9 15 12 16 22 24 3 27 1 6 21 26 5 19 
 Input registers: 

Component 12:
   Instructions: 88 102 93 98 95 
 Registers: 8 25 13 10 7 
 Input registers: 

Component 13:
   Instructions: 97 
 Registers: 18 
 Input registers: 

Component 14:
   Instructions: 99 
 Registers: 2 
 Input registers: 

Component 15:
   Instructions: 100 
 Registers: 31 
 Input registers: 

Component 16:
   Instructions: 103 122 110 118 113 126 125 114 108 127 117 106 112 105 119 120 121 107 115 116 124 111 104 109 
 Registers: 14 8 31 11 18 15 20 6 19 3 0 28 2 12 27 13 24 29 16 1 26 10 30 23 
 Input registers: 

Component 17:
   Instructions: 123 
 Registers: 17 
 Input registers: 

*/

int main() {
   printf("Verification of sequence solution\n");
   printf("Seed: 42\n");
   printf("Registers: 32\n");

    float registers[32];
   bool initialized[32] = {false};
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
   registers[10] = NAN;
   registers[11] = NAN;
   registers[12] = NAN;
   registers[13] = NAN;
   registers[14] = NAN;
   registers[15] = NAN;
   registers[16] = NAN;
   registers[17] = NAN;
   registers[18] = NAN;
   registers[19] = NAN;
   registers[20] = NAN;
   registers[21] = NAN;
   registers[22] = NAN;
   registers[23] = NAN;
   registers[24] = NAN;
   registers[25] = NAN;
   registers[26] = NAN;
   registers[27] = NAN;
   registers[28] = NAN;
   registers[29] = NAN;
   registers[30] = NAN;
   registers[31] = NAN;

    print_header("Executing Instructions");

   registers[11] = -25.7317791f;
   initialized[11] = true;
   printf("INIT: reg[%d] = %.8f\n", 11, registers[11]);

   registers[25] = 1.51676381f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   registers[30] = 2.16166043f;
   initialized[30] = true;
   printf("INIT: reg[%d] = %.8f\n", 30, registers[30]);

   registers[5] = 0.122907817f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[23] = 0.453266948f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   registers[24] = 0.000960217323f;
   initialized[24] = true;
   printf("INIT: reg[%d] = %.8f\n", 24, registers[24]);

   registers[19] = 3.0130055f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   if (!initialized[23] || !initialized[25]) {
   print_error("Instruction 7: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[23];
   float src2 = registers[25];
   float  result = src1 * src2;
   registers[20] = result;
   initialized[20] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 20, 23, 25, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.687498927f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_1: expected %.8f, got %.8f\n", 0.687498927f, result);
       verification_errors++;
   } else {
       print_success("reg_20_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[25] || !initialized[11]) {
   print_error("Instruction 8: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[11];
 result = src1 - src2;
   registers[4] = result;
   initialized[4] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 4, 25, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 27.2485428f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_1: expected %.8f, got %.8f\n", 27.2485428f, result);
       verification_errors++;
   } else {
       print_success("reg_4_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[20]) {
   print_error("Instruction 9: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[20];
 result = src1 * src2;
   registers[14] = result;
   initialized[14] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 14, 23, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.311620533f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_1: expected %.8f, got %.8f\n", 0.311620533f, result);
       verification_errors++;
   } else {
       print_success("reg_14_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[19] || !initialized[25]) {
   print_error("Instruction 10: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[25];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 10");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[6] = result;
   initialized[6] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 6, 19, 25, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.98646975f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_1: expected %.8f, got %.8f\n", 1.98646975f, result);
       verification_errors++;
   } else {
       print_success("reg_6_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[20] || !initialized[11]) {
   print_error("Instruction 11: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[20];
src2 = registers[11];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 20, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 26.4192772f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_1: expected %.8f, got %.8f\n", 26.4192772f, result);
       verification_errors++;
   } else {
       print_success("reg_3_1 matches: ");       printf("                       %.8f", result);
   }

   registers[1] = 1.6622231f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   if (!initialized[1] || !initialized[30]) {
   print_error("Instruction 13: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[30];
 result = src1 - src2;
   registers[15] = result;
   initialized[15] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 15, 1, 30, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.499437332f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_1: expected %.8f, got %.8f\n", -0.499437332f, result);
       verification_errors++;
   } else {
       print_success("reg_15_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[30] || !initialized[15]) {
   print_error("Instruction 14: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[30];
src2 = registers[15];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 30, 15, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 2.66109776f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_1: expected %.8f, got %.8f\n", 2.66109776f, result);
       verification_errors++;
   } else {
       print_success("reg_27_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[23]) {
   print_error("Instruction 15: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[23];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 15");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[10] = result;
   initialized[10] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 10, 14, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.687498927f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_1: expected %.8f, got %.8f\n", 0.687498927f, result);
       verification_errors++;
   } else {
       print_success("reg_10_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[4] || !initialized[11]) {
   print_error("Instruction 16: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[11];
 result = src1 * src2;
   registers[21] = result;
   initialized[21] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 21, 4, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -701.153503f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_1: expected %.8f, got %.8f\n", -701.153503f, result);
       verification_errors++;
   } else {
       print_success("reg_21_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[11] || !initialized[23]) {
   print_error("Instruction 17: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[11];
src2 = registers[23];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 17");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[7] = result;
   initialized[7] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 7, 11, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -56.7695923f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_1: expected %.8f, got %.8f\n", -56.7695923f, result);
       verification_errors++;
   } else {
       print_success("reg_7_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[3] || !initialized[20]) {
   print_error("Instruction 18: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[20];
 result = src1 - src2;
   registers[22] = result;
   initialized[22] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 22, 3, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 25.7317791f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_22_1: expected %.8f, got %.8f\n", 25.7317791f, result);
       verification_errors++;
   } else {
       print_success("reg_22_1 matches: ");       printf("                       %.8f", result);
   }

   registers[26] = 0.0614547729f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[20] || !initialized[23]) {
   print_error("Instruction 20: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[20];
src2 = registers[23];
 result = src1 * src2;
   registers[0] = result;
   initialized[0] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 0, 20, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.311620533f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_1: expected %.8f, got %.8f\n", 0.311620533f, result);
       verification_errors++;
   } else {
       print_success("reg_0_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[25] || !initialized[21]) {
   print_error("Instruction 21: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[21];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 21");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[2] = result;
   initialized[2] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 2, 25, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00216324069f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_1: expected %.8f, got %.8f\n", -0.00216324069f, result);
       verification_errors++;
   } else {
       print_success("reg_2_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[4]) {
   print_error("Instruction 22: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 22");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[31] = result;
   initialized[31] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 31, 23, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0166345388f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_1: expected %.8f, got %.8f\n", 0.0166345388f, result);
       verification_errors++;
   } else {
       print_success("reg_31_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[31] || !initialized[15]) {
   print_error("Instruction 23: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[15];
 result = src1 * src2;
   registers[28] = result;
   initialized[28] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 28, 31, 15, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00830790959f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_28_1: expected %.8f, got %.8f\n", -0.00830790959f, result);
       verification_errors++;
   } else {
       print_success("reg_28_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[25] || !initialized[0]) {
   print_error("Instruction 24: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[0];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 24");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[29] = result;
   initialized[29] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 29, 25, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 4.86734247f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_29_1: expected %.8f, got %.8f\n", 4.86734247f, result);
       verification_errors++;
   } else {
       print_success("reg_29_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[23]) {
   print_error("Instruction 25: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[23];
 result = src1 * src2;
   registers[8] = result;
   initialized[8] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 8, 7, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -25.7317791f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_1: expected %.8f, got %.8f\n", -25.7317791f, result);
       verification_errors++;
   } else {
       print_success("reg_8_1 matches: ");       printf("                       %.8f", result);
   }

   registers[9] = -39.6199875f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[8] || !initialized[9]) {
   print_error("Instruction 27: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[8];
src2 = registers[9];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 27");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[12] = result;
   initialized[12] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 12, 8, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.649464607f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_12_1: expected %.8f, got %.8f\n", 0.649464607f, result);
       verification_errors++;
   } else {
       print_success("reg_12_1 matches: ");       printf("                       %.8f", result);
   }

   registers[5] = 3.78594232f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[31] = 0.00747582316f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   registers[6] = 120.724373f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[19] = 0.00296050962f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   registers[9] = 230.998489f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[9] || !initialized[31]) {
   print_error("Instruction 33: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[31];
 result = src1 * src2;
   registers[20] = result;
   initialized[20] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 20, 9, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.72690392f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_2: expected %.8f, got %.8f\n", 1.72690392f, result);
       verification_errors++;
   } else {
       print_success("reg_20_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[5] || !initialized[31]) {
   print_error("Instruction 34: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[31];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 34");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[16] = result;
   initialized[16] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 16, 5, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 506.424805f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_1: expected %.8f, got %.8f\n", 506.424805f, result);
       verification_errors++;
   } else {
       print_success("reg_16_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[31] || !initialized[19]) {
   print_error("Instruction 35: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[19];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 35");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[0] = result;
   initialized[0] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 0, 31, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 2.52518129f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_2: expected %.8f, got %.8f\n", 2.52518129f, result);
       verification_errors++;
   } else {
       print_success("reg_0_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[5] || !initialized[9]) {
   print_error("Instruction 36: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[9];
 result = src1 * src2;
   registers[13] = result;
   initialized[13] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 13, 5, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 874.546936f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_1: expected %.8f, got %.8f\n", 874.546936f, result);
       verification_errors++;
   } else {
       print_success("reg_13_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 37: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.26076102f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_2: expected %.8f, got %.8f\n", -1.26076102f, result);
       verification_errors++;
   } else {
       print_success("reg_1_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[19]) {
   print_error("Instruction 38: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[19];
 result = src1 * src2;
   registers[10] = result;
   initialized[10] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 10, 1, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00373249524f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_2: expected %.8f, got %.8f\n", -0.00373249524f, result);
       verification_errors++;
   } else {
       print_success("reg_10_2 matches: ");       printf("                       %.8f", result);
   }

   registers[17] = 0.467949778f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   if (!initialized[19] || !initialized[20]) {
   print_error("Instruction 40: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[20];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 40");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[21] = result;
   initialized[21] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 21, 19, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0017143453f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_2: expected %.8f, got %.8f\n", 0.0017143453f, result);
       verification_errors++;
   } else {
       print_success("reg_21_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[6] || !initialized[0]) {
   print_error("Instruction 41: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[6];
src2 = registers[0];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 41");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[12] = result;
   initialized[12] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 12, 6, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 47.8082008f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_12_2: expected %.8f, got %.8f\n", 47.8082008f, result);
       verification_errors++;
   } else {
       print_success("reg_12_2 matches: ");       printf("                       %.8f", result);
   }

   registers[4] = 1.754053f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   if (!initialized[21] || !initialized[17]) {
   print_error("Instruction 43: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[17];
 result = src1 * src2;
   registers[2] = result;
   initialized[2] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 2, 21, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000802227529f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_2: expected %.8f, got %.8f\n", 0.000802227529f, result);
       verification_errors++;
   } else {
       print_success("reg_2_2 matches: ");       printf("                       %.8f", result);
   }

   registers[11] = 1.63269615f;
   initialized[11] = true;
   printf("INIT: reg[%d] = %.8f\n", 11, registers[11]);

   if (!initialized[2] || !initialized[10]) {
   print_error("Instruction 45: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[10];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 45");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[3] = result;
   initialized[3] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 3, 2, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.214930624f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_2: expected %.8f, got %.8f\n", -0.214930624f, result);
       verification_errors++;
   } else {
       print_success("reg_3_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[11] || !initialized[20]) {
   print_error("Instruction 46: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[11];
src2 = registers[20];
 result = src1 - src2;
   registers[14] = result;
   initialized[14] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 14, 11, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0942077637f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_2: expected %.8f, got %.8f\n", -0.0942077637f, result);
       verification_errors++;
   } else {
       print_success("reg_14_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[10] || !initialized[19]) {
   print_error("Instruction 47: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[10];
src2 = registers[19];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 47");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[7] = result;
   initialized[7] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 7, 10, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.26076102f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_2: expected %.8f, got %.8f\n", -1.26076102f, result);
       verification_errors++;
   } else {
       print_success("reg_7_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[5] || !initialized[7]) {
   print_error("Instruction 48: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[7];
 result = src1 * src2;
   registers[15] = result;
   initialized[15] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 15, 5, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -4.77316856f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_2: expected %.8f, got %.8f\n", -4.77316856f, result);
       verification_errors++;
   } else {
       print_success("reg_15_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[3] || !initialized[13]) {
   print_error("Instruction 49: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[13];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 49");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[8] = result;
   initialized[8] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 8, 3, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000245762261f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_2: expected %.8f, got %.8f\n", -0.000245762261f, result);
       verification_errors++;
   } else {
       print_success("reg_8_2 matches: ");       printf("                       %.8f", result);
   }

   registers[25] = 0.000480108662f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   registers[22] = 0.0614539087f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[16] || !initialized[4]) {
   print_error("Instruction 52: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[16];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 52");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[18] = result;
   initialized[18] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 18, 16, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 288.716949f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_1: expected %.8f, got %.8f\n", 288.716949f, result);
       verification_errors++;
   } else {
       print_success("reg_18_1 matches: ");       printf("                       %.8f", result);
   }

   registers[12] = -0.0797135532f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[16] = 0.0771184489f;
   initialized[16] = true;
   printf("INIT: reg[%d] = %.8f\n", 16, registers[16]);

   registers[31] = -0.148117751f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   registers[18] = 9.76590252f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   registers[14] = 0.386873484f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   if (!initialized[16] || !initialized[12]) {
   print_error("Instruction 58: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[16];
src2 = registers[12];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 16, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00614738557f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_3: expected %.8f, got %.8f\n", -0.00614738557f, result);
       verification_errors++;
   } else {
       print_success("reg_1_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[12]) {
   print_error("Instruction 59: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[12];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 14, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.466587037f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_2: expected %.8f, got %.8f\n", 0.466587037f, result);
       verification_errors++;
   } else {
       print_success("reg_27_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[12] || !initialized[27]) {
   print_error("Instruction 60: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[27];
 result = src1 * src2;
   registers[19] = result;
   initialized[19] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 19, 12, 27, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0371933095f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_19_3: expected %.8f, got %.8f\n", -0.0371933095f, result);
       verification_errors++;
   } else {
       print_success("reg_19_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[27] || !initialized[18]) {
   print_error("Instruction 61: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[27];
src2 = registers[18];
 result = src1 - src2;
   registers[21] = result;
   initialized[21] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 21, 27, 18, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -9.29931545f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_3: expected %.8f, got %.8f\n", -9.29931545f, result);
       verification_errors++;
   } else {
       print_success("reg_21_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[31] || !initialized[12]) {
   print_error("Instruction 62: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[12];
 result = src1 - src2;
   registers[5] = result;
   initialized[5] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 5, 31, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0684041977f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_3: expected %.8f, got %.8f\n", -0.0684041977f, result);
       verification_errors++;
   } else {
       print_success("reg_5_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[21] || !initialized[16]) {
   print_error("Instruction 63: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[16];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 63");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[15] = result;
   initialized[15] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 15, 21, 16, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -120.584839f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_3: expected %.8f, got %.8f\n", -120.584839f, result);
       verification_errors++;
   } else {
       print_success("reg_15_3 matches: ");       printf("                       %.8f", result);
   }

   registers[2] = 0.737523258f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   if (!initialized[5] || !initialized[19]) {
   print_error("Instruction 65: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[19];
 result = src1 - src2;
   registers[0] = result;
   initialized[0] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 0, 5, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0312108882f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_3: expected %.8f, got %.8f\n", -0.0312108882f, result);
       verification_errors++;
   } else {
       print_success("reg_0_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[14]) {
   print_error("Instruction 66: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[14];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 66");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[30] = result;
   initialized[30] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 30, 0, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0806746632f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_30_2: expected %.8f, got %.8f\n", -0.0806746632f, result);
       verification_errors++;
   } else {
       print_success("reg_30_2 matches: ");       printf("                       %.8f", result);
   }

   registers[3] = 2.02680016f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 68: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00213495572f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_3: expected %.8f, got %.8f\n", 0.00213495572f, result);
       verification_errors++;
   } else {
       print_success("reg_4_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[16]) {
   print_error("Instruction 69: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[16];
 result = src1 - src2;
   registers[20] = result;
   initialized[20] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 20, 1, 16, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0832658336f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_3: expected %.8f, got %.8f\n", -0.0832658336f, result);
       verification_errors++;
   } else {
       print_success("reg_20_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[27] || !initialized[1]) {
   print_error("Instruction 70: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[27];
src2 = registers[1];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 70");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[25] = result;
   initialized[25] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 25, 27, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -75.9000778f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_3: expected %.8f, got %.8f\n", -75.9000778f, result);
       verification_errors++;
   } else {
       print_success("reg_25_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[2]) {
   print_error("Instruction 71: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[2];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 71");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[13] = result;
   initialized[13] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 13, 1, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00833517499f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_2: expected %.8f, got %.8f\n", -0.00833517499f, result);
       verification_errors++;
   } else {
       print_success("reg_13_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[2] || !initialized[0]) {
   print_error("Instruction 72: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[0];
 result = src1 * src2;
   registers[9] = result;
   initialized[9] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 9, 2, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.023018755f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_3: expected %.8f, got %.8f\n", -0.023018755f, result);
       verification_errors++;
   } else {
       print_success("reg_9_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[25] || !initialized[2]) {
   print_error("Instruction 73: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[2];
 result = src1 * src2;
   registers[6] = result;
   initialized[6] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 6, 25, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -55.9780731f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_3: expected %.8f, got %.8f\n", -55.9780731f, result);
       verification_errors++;
   } else {
       print_success("reg_6_3 matches: ");       printf("                       %.8f", result);
   }

   registers[7] = 0.000240054447f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   registers[8] = 0.0307269543f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   if (!initialized[20] || !initialized[0]) {
   print_error("Instruction 76: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[20];
src2 = registers[0];
 result = src1 - src2;
   registers[22] = result;
   initialized[22] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 22, 20, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0520549454f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_22_3: expected %.8f, got %.8f\n", -0.0520549454f, result);
       verification_errors++;
   } else {
       print_success("reg_22_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[13] || !initialized[27]) {
   print_error("Instruction 77: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[13];
src2 = registers[27];
 result = src1 * src2;
   registers[10] = result;
   initialized[10] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 10, 13, 27, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00388908456f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_3: expected %.8f, got %.8f\n", -0.00388908456f, result);
       verification_errors++;
   } else {
       print_success("reg_10_3 matches: ");       printf("                       %.8f", result);
   }

   registers[14] = 0.00364603125f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   registers[21] = 0.000199392336f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   registers[3] = 0.000227876953f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   registers[19] = -1.99635398f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   registers[15] = -0.00742003229f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[14] || !initialized[3]) {
   print_error("Instruction 83: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[3];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 83");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[26] = result;
   initialized[26] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 26, 14, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 16.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_2: expected %.8f, got %.8f\n", 16.0f, result);
       verification_errors++;
   } else {
       print_success("reg_26_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[3] || !initialized[14]) {
   print_error("Instruction 84: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[14];
 result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 3, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00341815432f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_4: expected %.8f, got %.8f\n", -0.00341815432f, result);
       verification_errors++;
   } else {
       print_success("reg_1_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[19] || !initialized[14]) {
   print_error("Instruction 85: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[14];
 result = src1 - src2;
   registers[5] = result;
   initialized[5] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 5, 19, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_4: expected %.8f, got %.8f\n", -2.0f, result);
       verification_errors++;
   } else {
       print_success("reg_5_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[5]) {
   print_error("Instruction 86: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[5];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 86");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[29] = result;
   initialized[29] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 29, 14, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00182301563f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_29_2: expected %.8f, got %.8f\n", -0.00182301563f, result);
       verification_errors++;
   } else {
       print_success("reg_29_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[15] || !initialized[3]) {
   print_error("Instruction 87: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[15];
src2 = registers[3];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 87");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[12] = result;
   initialized[12] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 12, 15, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -32.561573f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_12_4: expected %.8f, got %.8f\n", -32.561573f, result);
       verification_errors++;
   } else {
       print_success("reg_12_4 matches: ");       printf("                       %.8f", result);
   }

   registers[8] = -0.0585937463f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   if (!initialized[21] || !initialized[3]) {
   print_error("Instruction 89: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[3];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 89");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[6] = result;
   initialized[6] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 6, 21, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.875f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_4: expected %.8f, got %.8f\n", 0.875f, result);
       verification_errors++;
   } else {
       print_success("reg_6_4 matches: ");       printf("                       %.8f", result);
   }

   registers[22] = -0.000232965729f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[3] || !initialized[22]) {
   print_error("Instruction 91: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[22];
 result = src1 - src2;
   registers[24] = result;
   initialized[24] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 24, 3, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000460842683f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_2: expected %.8f, got %.8f\n", 0.000460842683f, result);
       verification_errors++;
   } else {
       print_success("reg_24_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[29] || !initialized[15]) {
   print_error("Instruction 92: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[15];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 92");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[9] = result;
   initialized[9] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 9, 29, 15, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.245688364f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_4: expected %.8f, got %.8f\n", 0.245688364f, result);
       verification_errors++;
   } else {
       print_success("reg_9_4 matches: ");       printf("                       %.8f", result);
   }

   registers[13] = -1.53122878f;
   initialized[13] = true;
   printf("INIT: reg[%d] = %.8f\n", 13, registers[13]);

   if (!initialized[12] || !initialized[22]) {
   print_error("Instruction 94: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[22];
 result = src1 * src2;
   registers[16] = result;
   initialized[16] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 16, 12, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0075857304f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_3: expected %.8f, got %.8f\n", 0.0075857304f, result);
       verification_errors++;
   } else {
       print_success("reg_16_3 matches: ");       printf("                       %.8f", result);
   }

   registers[7] = 32.5312843f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[29] || !initialized[9]) {
   print_error("Instruction 96: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[9];
 result = src1 - src2;
   registers[17] = result;
   initialized[17] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 17, 29, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.247511387f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_17_2: expected %.8f, got %.8f\n", -0.247511387f, result);
       verification_errors++;
   } else {
       print_success("reg_17_2 matches: ");       printf("                       %.8f", result);
   }

   registers[18] = 0.000120027165f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   if (!initialized[7] || !initialized[8]) {
   print_error("Instruction 98: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[8];
 result = src1 * src2;
   registers[10] = result;
   initialized[10] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 10, 7, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.90612984f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_4: expected %.8f, got %.8f\n", -1.90612984f, result);
       verification_errors++;
   } else {
       print_success("reg_10_4 matches: ");       printf("                       %.8f", result);
   }

   registers[2] = 0.00381469727f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   registers[31] = 0.000960217323f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   if (!initialized[3] || !initialized[1]) {
   print_error("Instruction 101: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[1];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 3, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00364603125f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_3: expected %.8f, got %.8f\n", 0.00364603125f, result);
       verification_errors++;
   } else {
       print_success("reg_27_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[13] || !initialized[8]) {
   print_error("Instruction 102: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[13];
src2 = registers[8];
 result = src1 - src2;
   registers[25] = result;
   initialized[25] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 25, 13, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.47263503f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_4: expected %.8f, got %.8f\n", -1.47263503f, result);
       verification_errors++;
   } else {
       print_success("reg_25_4 matches: ");       printf("                       %.8f", result);
   }

   registers[14] = 1.86391962f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   registers[30] = -0.224127337f;
   initialized[30] = true;
   printf("INIT: reg[%d] = %.8f\n", 30, registers[30]);

   registers[12] = 104.477097f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[28] = 0.515627384f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   registers[29] = 0.12906f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[19] = 15.767705f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   if (!initialized[30] || !initialized[14]) {
   print_error("Instruction 109: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[30];
src2 = registers[14];
 result = src1 - src2;
   registers[23] = result;
   initialized[23] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 23, 30, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.08804703f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_2: expected %.8f, got %.8f\n", -2.08804703f, result);
       verification_errors++;
   } else {
       print_success("reg_23_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[28] || !initialized[12]) {
   print_error("Instruction 110: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[12];
 result = src1 * src2;
   registers[31] = result;
   initialized[31] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 31, 28, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 53.8712502f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_5: expected %.8f, got %.8f\n", 53.8712502f, result);
       verification_errors++;
   } else {
       print_success("reg_31_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[30] || !initialized[19]) {
   print_error("Instruction 111: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[30];
src2 = registers[19];
 result = src1 - src2;
   registers[10] = result;
   initialized[10] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 10, 30, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -15.9918327f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_5: expected %.8f, got %.8f\n", -15.9918327f, result);
       verification_errors++;
   } else {
       print_success("reg_10_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[12] || !initialized[28]) {
   print_error("Instruction 112: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[28];
 result = src1 - src2;
   registers[2] = result;
   initialized[2] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 2, 12, 28, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 103.961472f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_5: expected %.8f, got %.8f\n", 103.961472f, result);
       verification_errors++;
   } else {
       print_success("reg_2_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[2] || !initialized[30]) {
   print_error("Instruction 113: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[30];
 result = src1 * src2;
   registers[18] = result;
   initialized[18] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 18, 2, 30, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -23.3006077f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_4: expected %.8f, got %.8f\n", -23.3006077f, result);
       verification_errors++;
   } else {
       print_success("reg_18_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[12] || !initialized[19]) {
   print_error("Instruction 114: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[19];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 114");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[6] = result;
   initialized[6] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 6, 12, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 6.62601805f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_5: expected %.8f, got %.8f\n", 6.62601805f, result);
       verification_errors++;
   } else {
       print_success("reg_6_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[10] || !initialized[29]) {
   print_error("Instruction 115: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[10];
src2 = registers[29];
 result = src1 * src2;
   registers[16] = result;
   initialized[16] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 16, 10, 29, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.06390595f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_4: expected %.8f, got %.8f\n", -2.06390595f, result);
       verification_errors++;
   } else {
       print_success("reg_16_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[16]) {
   print_error("Instruction 116: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[16];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 14, 16, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -3.84695482f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_5: expected %.8f, got %.8f\n", -3.84695482f, result);
       verification_errors++;
   } else {
       print_success("reg_1_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[28]) {
   print_error("Instruction 117: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[28];
 result = src1 * src2;
   registers[0] = result;
   initialized[0] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 0, 1, 28, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.98359525f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_4: expected %.8f, got %.8f\n", -1.98359525f, result);
       verification_errors++;
   } else {
       print_success("reg_0_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[18] || !initialized[31]) {
   print_error("Instruction 118: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[18];
src2 = registers[31];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 118");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[11] = result;
   initialized[11] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 11, 18, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.432523996f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_11_3: expected %.8f, got %.8f\n", -0.432523996f, result);
       verification_errors++;
   } else {
       print_success("reg_11_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[29] || !initialized[12]) {
   print_error("Instruction 119: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[12];
 result = src1 * src2;
   registers[27] = result;
   initialized[27] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 27, 29, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 13.4838142f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_4: expected %.8f, got %.8f\n", 13.4838142f, result);
       verification_errors++;
   } else {
       print_success("reg_27_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[27] || !initialized[14]) {
   print_error("Instruction 120: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[27];
src2 = registers[14];
 result = src1 * src2;
   registers[13] = result;
   initialized[13] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 13, 27, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 25.1327457f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_4: expected %.8f, got %.8f\n", 25.1327457f, result);
       verification_errors++;
   } else {
       print_success("reg_13_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[18] || !initialized[13]) {
   print_error("Instruction 121: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[18];
src2 = registers[13];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 121");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[24] = result;
   initialized[24] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 24, 18, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.927101552f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_3: expected %.8f, got %.8f\n", -0.927101552f, result);
       verification_errors++;
   } else {
       print_success("reg_24_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[31] || !initialized[14]) {
   print_error("Instruction 122: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[14];
 result = src1 - src2;
   registers[8] = result;
   initialized[8] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 8, 31, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 52.0073318f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_5: expected %.8f, got %.8f\n", 52.0073318f, result);
       verification_errors++;
   } else {
       print_success("reg_8_5 matches: ");       printf("                       %.8f", result);
   }

   registers[17] = 0.983262539f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   if (!initialized[1] || !initialized[19]) {
   print_error("Instruction 124: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[19];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 124");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[26] = result;
   initialized[26] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 26, 1, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.243976846f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_3: expected %.8f, got %.8f\n", -0.243976846f, result);
       verification_errors++;
   } else {
       print_success("reg_26_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[28] || !initialized[6]) {
   print_error("Instruction 125: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[6];
 result = src1 * src2;
   registers[20] = result;
   initialized[20] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 20, 28, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 3.41655636f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_4: expected %.8f, got %.8f\n", 3.41655636f, result);
       verification_errors++;
   } else {
       print_success("reg_20_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[18] || !initialized[20]) {
   print_error("Instruction 126: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[18];
src2 = registers[20];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 126");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[15] = result;
   initialized[15] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 15, 18, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -6.81991005f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_5: expected %.8f, got %.8f\n", -6.81991005f, result);
       verification_errors++;
   } else {
       print_success("reg_15_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[19] || !initialized[0]) {
   print_error("Instruction 127: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[0];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 127");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[3] = result;
   initialized[3] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 3, 19, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -7.94905376f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_5: expected %.8f, got %.8f\n", -7.94905376f, result);
       verification_errors++;
   } else {
       print_success("reg_3_5 matches: ");       printf("                       %.8f", result);
   }


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[0], -1.98359525f, EPSILON)) {
printf("[ERROR] Final reg[0] mismatch: expected -1.98359525, got %.8f\n", registers[0]);
       verification_errors++;
   } else {
       print_success("Final reg[0] matches: -1.98359525");
   }

   total_checks++;
   if (!float_equal(registers[1], -3.84695482f, EPSILON)) {
printf("[ERROR] Final reg[1] mismatch: expected -3.84695482, got %.8f\n", registers[1]);
       verification_errors++;
   } else {
       print_success("Final reg[1] matches: -3.84695482");
   }

   total_checks++;
   if (!float_equal(registers[2], 103.961472f, EPSILON)) {
printf("[ERROR] Final reg[2] mismatch: expected 103.961472, got %.8f\n", registers[2]);
       verification_errors++;
   } else {
       print_success("Final reg[2] matches: 103.961472");
   }

   total_checks++;
   if (!float_equal(registers[3], -7.94905376f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected -7.94905376, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: -7.94905376");
   }

   total_checks++;
   if (!float_equal(registers[4], 0.00213495572f, EPSILON)) {
printf("[ERROR] Final reg[4] mismatch: expected 0.00213495572, got %.8f\n", registers[4]);
       verification_errors++;
   } else {
       print_success("Final reg[4] matches: 0.00213495572");
   }

   total_checks++;
   if (!float_equal(registers[5], -2.0f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected -2.0, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: -2.0");
   }

   total_checks++;
   if (!float_equal(registers[6], 6.62601805f, EPSILON)) {
printf("[ERROR] Final reg[6] mismatch: expected 6.62601805, got %.8f\n", registers[6]);
       verification_errors++;
   } else {
       print_success("Final reg[6] matches: 6.62601805");
   }

   total_checks++;
   if (!float_equal(registers[7], 32.5312843f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected 32.5312843, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: 32.5312843");
   }

   total_checks++;
   if (!float_equal(registers[8], 52.0073318f, EPSILON)) {
printf("[ERROR] Final reg[8] mismatch: expected 52.0073318, got %.8f\n", registers[8]);
       verification_errors++;
   } else {
       print_success("Final reg[8] matches: 52.0073318");
   }

   total_checks++;
   if (!float_equal(registers[9], 0.245688364f, EPSILON)) {
printf("[ERROR] Final reg[9] mismatch: expected 0.245688364, got %.8f\n", registers[9]);
       verification_errors++;
   } else {
       print_success("Final reg[9] matches: 0.245688364");
   }

   total_checks++;
   if (!float_equal(registers[10], -15.9918327f, EPSILON)) {
printf("[ERROR] Final reg[10] mismatch: expected -15.9918327, got %.8f\n", registers[10]);
       verification_errors++;
   } else {
       print_success("Final reg[10] matches: -15.9918327");
   }

   total_checks++;
   if (!float_equal(registers[11], -0.432523996f, EPSILON)) {
printf("[ERROR] Final reg[11] mismatch: expected -0.432523996, got %.8f\n", registers[11]);
       verification_errors++;
   } else {
       print_success("Final reg[11] matches: -0.432523996");
   }

   total_checks++;
   if (!float_equal(registers[12], 104.477097f, EPSILON)) {
printf("[ERROR] Final reg[12] mismatch: expected 104.477097, got %.8f\n", registers[12]);
       verification_errors++;
   } else {
       print_success("Final reg[12] matches: 104.477097");
   }

   total_checks++;
   if (!float_equal(registers[13], 25.1327457f, EPSILON)) {
printf("[ERROR] Final reg[13] mismatch: expected 25.1327457, got %.8f\n", registers[13]);
       verification_errors++;
   } else {
       print_success("Final reg[13] matches: 25.1327457");
   }

   total_checks++;
   if (!float_equal(registers[14], 1.86391962f, EPSILON)) {
printf("[ERROR] Final reg[14] mismatch: expected 1.86391962, got %.8f\n", registers[14]);
       verification_errors++;
   } else {
       print_success("Final reg[14] matches: 1.86391962");
   }

   total_checks++;
   if (!float_equal(registers[15], -6.81991005f, EPSILON)) {
printf("[ERROR] Final reg[15] mismatch: expected -6.81991005, got %.8f\n", registers[15]);
       verification_errors++;
   } else {
       print_success("Final reg[15] matches: -6.81991005");
   }

   total_checks++;
   if (!float_equal(registers[16], -2.06390595f, EPSILON)) {
printf("[ERROR] Final reg[16] mismatch: expected -2.06390595, got %.8f\n", registers[16]);
       verification_errors++;
   } else {
       print_success("Final reg[16] matches: -2.06390595");
   }

   total_checks++;
   if (!float_equal(registers[17], 0.983262539f, EPSILON)) {
printf("[ERROR] Final reg[17] mismatch: expected 0.983262539, got %.8f\n", registers[17]);
       verification_errors++;
   } else {
       print_success("Final reg[17] matches: 0.983262539");
   }

   total_checks++;
   if (!float_equal(registers[18], -23.3006077f, EPSILON)) {
printf("[ERROR] Final reg[18] mismatch: expected -23.3006077, got %.8f\n", registers[18]);
       verification_errors++;
   } else {
       print_success("Final reg[18] matches: -23.3006077");
   }

   total_checks++;
   if (!float_equal(registers[19], 15.767705f, EPSILON)) {
printf("[ERROR] Final reg[19] mismatch: expected 15.767705, got %.8f\n", registers[19]);
       verification_errors++;
   } else {
       print_success("Final reg[19] matches: 15.767705");
   }

   total_checks++;
   if (!float_equal(registers[20], 3.41655636f, EPSILON)) {
printf("[ERROR] Final reg[20] mismatch: expected 3.41655636, got %.8f\n", registers[20]);
       verification_errors++;
   } else {
       print_success("Final reg[20] matches: 3.41655636");
   }

   total_checks++;
   if (!float_equal(registers[21], 0.000199392336f, EPSILON)) {
printf("[ERROR] Final reg[21] mismatch: expected 0.000199392336, got %.8f\n", registers[21]);
       verification_errors++;
   } else {
       print_success("Final reg[21] matches: 0.000199392336");
   }

   total_checks++;
   if (!float_equal(registers[22], -0.000232965729f, EPSILON)) {
printf("[ERROR] Final reg[22] mismatch: expected -0.000232965729, got %.8f\n", registers[22]);
       verification_errors++;
   } else {
       print_success("Final reg[22] matches: -0.000232965729");
   }

   total_checks++;
   if (!float_equal(registers[23], -2.08804703f, EPSILON)) {
printf("[ERROR] Final reg[23] mismatch: expected -2.08804703, got %.8f\n", registers[23]);
       verification_errors++;
   } else {
       print_success("Final reg[23] matches: -2.08804703");
   }

   total_checks++;
   if (!float_equal(registers[24], -0.927101552f, EPSILON)) {
printf("[ERROR] Final reg[24] mismatch: expected -0.927101552, got %.8f\n", registers[24]);
       verification_errors++;
   } else {
       print_success("Final reg[24] matches: -0.927101552");
   }

   total_checks++;
   if (!float_equal(registers[25], -1.47263503f, EPSILON)) {
printf("[ERROR] Final reg[25] mismatch: expected -1.47263503, got %.8f\n", registers[25]);
       verification_errors++;
   } else {
       print_success("Final reg[25] matches: -1.47263503");
   }

   total_checks++;
   if (!float_equal(registers[26], -0.243976846f, EPSILON)) {
printf("[ERROR] Final reg[26] mismatch: expected -0.243976846, got %.8f\n", registers[26]);
       verification_errors++;
   } else {
       print_success("Final reg[26] matches: -0.243976846");
   }

   total_checks++;
   if (!float_equal(registers[27], 13.4838142f, EPSILON)) {
printf("[ERROR] Final reg[27] mismatch: expected 13.4838142, got %.8f\n", registers[27]);
       verification_errors++;
   } else {
       print_success("Final reg[27] matches: 13.4838142");
   }

   total_checks++;
   if (!float_equal(registers[28], 0.515627384f, EPSILON)) {
printf("[ERROR] Final reg[28] mismatch: expected 0.515627384, got %.8f\n", registers[28]);
       verification_errors++;
   } else {
       print_success("Final reg[28] matches: 0.515627384");
   }

   total_checks++;
   if (!float_equal(registers[29], 0.12906f, EPSILON)) {
printf("[ERROR] Final reg[29] mismatch: expected 0.12906, got %.8f\n", registers[29]);
       verification_errors++;
   } else {
       print_success("Final reg[29] matches: 0.12906");
   }

   total_checks++;
   if (!float_equal(registers[30], -0.224127337f, EPSILON)) {
printf("[ERROR] Final reg[30] mismatch: expected -0.224127337, got %.8f\n", registers[30]);
       verification_errors++;
   } else {
       print_success("Final reg[30] matches: -0.224127337");
   }

   total_checks++;
   if (!float_equal(registers[31], 53.8712502f, EPSILON)) {
printf("[ERROR] Final reg[31] mismatch: expected 53.8712502, got %.8f\n", registers[31]);
       verification_errors++;
   } else {
       print_success("Final reg[31] matches: 53.8712502");
   }

   print_header("Verification Summary");
   printf("Total checks performed: %d\n", total_checks);
   printf("Verification errors: %d\n", verification_errors);
   if (verification_errors == 0) {
       print_success("All verifications passed!");
   } else {
   printf("[ERROR] Verification failed with  %d errors\n", verification_errors);
   print_register_state(registers, 32, "final");
   }

 return SUCCESS_CODE;
}
