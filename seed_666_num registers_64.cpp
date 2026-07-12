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
   Instructions: 0 14 10 13 2 11 9 4 6 5 3 16 15 12 8 1 7 
 Registers: 44 3 0 16 54 15 21 43 46 8 13 7 17 26 60 6 48 
 Input registers: 

Component 1:
   Instructions: 17 
 Registers: 29 
 Input registers: 

Component 2:
   Instructions: 18 
 Registers: 32 
 Input registers: 

Component 3:
   Instructions: 19 
 Registers: 14 
 Input registers: 

Component 4:
   Instructions: 20 31 25 23 30 22 28 26 27 24 21 
 Registers: 12 48 25 52 50 47 18 44 20 13 49 
 Input registers: 

Component 5:
   Instructions: 29 
 Registers: 9 
 Input registers: 

Component 6:
   Instructions: 32 35 34 39 37 36 43 38 33 
 Registers: 0 54 7 61 49 8 55 15 46 
 Input registers: 

Component 7:
   Instructions: 40 
 Registers: 1 
 Input registers: 

Component 8:
   Instructions: 41 
 Registers: 18 
 Input registers: 

Component 9:
   Instructions: 42 
 Registers: 47 
 Input registers: 

Component 10:
   Instructions: 44 52 48 54 45 46 49 47 53 51 
 Registers: 21 34 58 16 22 12 18 59 60 33 
 Input registers: 

Component 11:
   Instructions: 50 
 Registers: 62 
 Input registers: 

Component 12:
   Instructions: 55 
 Registers: 4 
 Input registers: 

Component 13:
   Instructions: 56 66 64 60 62 61 58 57 65 59 
 Registers: 37 35 52 56 40 21 20 17 18 29 
 Input registers: 

Component 14:
   Instructions: 63 
 Registers: 24 
 Input registers: 

Component 15:
   Instructions: 67 
 Registers: 48 
 Input registers: 

Component 16:
   Instructions: 68 78 75 76 79 69 74 71 73 70 72 
 Registers: 26 14 48 49 18 42 4 55 33 47 23 
 Input registers: 

Component 17:
   Instructions: 77 
 Registers: 21 
 Input registers: 

Component 18:
   Instructions: 80 86 90 82 87 91 89 83 84 85 81 
 Registers: 5 53 17 31 58 26 25 40 9 62 0 
 Input registers: 

Component 19:
   Instructions: 88 
 Registers: 12 
 Input registers: 

Component 20:
   Instructions: 92 95 93 97 100 101 99 102 96 94 98 
 Registers: 35 46 21 61 25 50 55 1 54 57 26 
 Input registers: 

Component 21:
   Instructions: 103 
 Registers: 28 
 Input registers: 

Component 22:
   Instructions: 104 115 113 105 109 107 112 106 108 
 Registers: 19 37 36 61 45 46 49 22 57 
 Input registers: 

Component 23:
   Instructions: 110 
 Registers: 50 
 Input registers: 

Component 24:
   Instructions: 111 
 Registers: 15 
 Input registers: 

Component 25:
   Instructions: 114 
 Registers: 26 
 Input registers: 

Component 26:
   Instructions: 116 127 125 124 122 118 120 121 123 117 
 Registers: 49 37 6 46 56 29 11 42 10 57 
 Input registers: 

Component 27:
   Instructions: 119 
 Registers: 7 
 Input registers: 

Component 28:
   Instructions: 126 
 Registers: 43 
 Input registers: 

*/

int main() {
   printf("Verification of sequence solution\n");
   printf("Seed: 666\n");
   printf("Registers: 64\n");

    float registers[64];
   bool initialized[64] = {false};
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
   registers[32] = NAN;
   registers[33] = NAN;
   registers[34] = NAN;
   registers[35] = NAN;
   registers[36] = NAN;
   registers[37] = NAN;
   registers[38] = NAN;
   registers[39] = NAN;
   registers[40] = NAN;
   registers[41] = NAN;
   registers[42] = NAN;
   registers[43] = NAN;
   registers[44] = NAN;
   registers[45] = NAN;
   registers[46] = NAN;
   registers[47] = NAN;
   registers[48] = NAN;
   registers[49] = NAN;
   registers[50] = NAN;
   registers[51] = NAN;
   registers[52] = NAN;
   registers[53] = NAN;
   registers[54] = NAN;
   registers[55] = NAN;
   registers[56] = NAN;
   registers[57] = NAN;
   registers[58] = NAN;
   registers[59] = NAN;
   registers[60] = NAN;
   registers[61] = NAN;
   registers[62] = NAN;
   registers[63] = NAN;

    print_header("Executing Instructions");

   registers[44] = 0.404884249f;
   initialized[44] = true;
   printf("INIT: reg[%d] = %.8f\n", 44, registers[44]);

   registers[6] = 3.18712974f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[54] = 0.575873494f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   registers[13] = -0.906677485f;
   initialized[13] = true;
   printf("INIT: reg[%d] = %.8f\n", 13, registers[13]);

   registers[43] = 0.238246635f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   if (!initialized[6] || !initialized[13]) {
   print_error("Instruction 5: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[6];
   float src2 = registers[13];
   float  result = src1 - src2;
   registers[8] = result;
   initialized[8] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 8, 6, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 4.09380722f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_1: expected %.8f, got %.8f\n", 4.09380722f, result);
       verification_errors++;
   } else {
       print_success("reg_8_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[43] || !initialized[8]) {
   print_error("Instruction 6: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[43];
src2 = registers[8];
 result = src1 * src2;
   registers[46] = result;
   initialized[46] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 46, 43, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.975335777f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_1: expected %.8f, got %.8f\n", 0.975335777f, result);
       verification_errors++;
   } else {
       print_success("reg_46_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[44] || !initialized[6]) {
   print_error("Instruction 7: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[6];
 result = src1 * src2;
   registers[48] = result;
   initialized[48] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 48, 44, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.29041862f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_48_1: expected %.8f, got %.8f\n", 1.29041862f, result);
       verification_errors++;
   } else {
       print_success("reg_48_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[54] || !initialized[44]) {
   print_error("Instruction 8: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[44];
 result = src1 * src2;
   registers[60] = result;
   initialized[60] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 60, 54, 44, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.233162105f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_60_1: expected %.8f, got %.8f\n", 0.233162105f, result);
       verification_errors++;
   } else {
       print_success("reg_60_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[44] || !initialized[43]) {
   print_error("Instruction 9: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[43];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 9");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[21] = result;
   initialized[21] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 21, 44, 43, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.69943321f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_1: expected %.8f, got %.8f\n", 1.69943321f, result);
       verification_errors++;
   } else {
       print_success("reg_21_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[54] || !initialized[48]) {
   print_error("Instruction 10: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[48];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 10");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[0] = result;
   initialized[0] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 0, 54, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.446268737f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_1: expected %.8f, got %.8f\n", 0.446268737f, result);
       verification_errors++;
   } else {
       print_success("reg_0_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[21] || !initialized[54]) {
   print_error("Instruction 11: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[54];
 result = src1 * src2;
   registers[15] = result;
   initialized[15] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 15, 21, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.978658557f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_1: expected %.8f, got %.8f\n", 0.978658557f, result);
       verification_errors++;
   } else {
       print_success("reg_15_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[60] || !initialized[13]) {
   print_error("Instruction 12: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[60];
src2 = registers[13];
 result = src1 * src2;
   registers[26] = result;
   initialized[26] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 26, 60, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.211402833f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_1: expected %.8f, got %.8f\n", -0.211402833f, result);
       verification_errors++;
   } else {
       print_success("reg_26_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[54] || !initialized[0]) {
   print_error("Instruction 13: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[0];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 13");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[16] = result;
   initialized[16] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 16, 54, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.29041862f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_1: expected %.8f, got %.8f\n", 1.29041862f, result);
       verification_errors++;
   } else {
       print_success("reg_16_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[44] || !initialized[0]) {
   print_error("Instruction 14: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[0];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 44, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0413844883f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_1: expected %.8f, got %.8f\n", -0.0413844883f, result);
       verification_errors++;
   } else {
       print_success("reg_3_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[17] = -2.39694071f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   if (!initialized[13] || !initialized[17]) {
   print_error("Instruction 16: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[13];
src2 = registers[17];
 result = src1 - src2;
   registers[7] = result;
   initialized[7] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 7, 13, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.49026322f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_1: expected %.8f, got %.8f\n", 1.49026322f, result);
       verification_errors++;
   } else {
       print_success("reg_7_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[29] = 0.0614539087f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[32] = 0.983262539f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   registers[14] = 0.000738964882f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   registers[12] = 1.79553866f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[49] = -0.940998316f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[49] || !initialized[12]) {
   print_error("Instruction 22: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[12];
 result = src1 - src2;
   registers[47] = result;
   initialized[47] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 47, 49, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.73653698f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_1: expected %.8f, got %.8f\n", -2.73653698f, result);
       verification_errors++;
   } else {
       print_success("reg_47_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[49] || !initialized[12]) {
   print_error("Instruction 23: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[12];
 result = src1 * src2;
   registers[52] = result;
   initialized[52] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 52, 49, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.68959892f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_1: expected %.8f, got %.8f\n", -1.68959892f, result);
       verification_errors++;
   } else {
       print_success("reg_52_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[49] || !initialized[52]) {
   print_error("Instruction 24: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[52];
 result = src1 * src2;
   registers[13] = result;
   initialized[13] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 13, 49, 52, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.58990979f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_2: expected %.8f, got %.8f\n", 1.58990979f, result);
       verification_errors++;
   } else {
       print_success("reg_13_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[25] = 30.5563946f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   registers[44] = 106.153206f;
   initialized[44] = true;
   printf("INIT: reg[%d] = %.8f\n", 44, registers[44]);

   if (!initialized[47] || !initialized[13]) {
   print_error("Instruction 27: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[13];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 27");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[20] = result;
   initialized[20] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 20, 47, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.72119009f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_1: expected %.8f, got %.8f\n", -1.72119009f, result);
       verification_errors++;
   } else {
       print_success("reg_20_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[44] || !initialized[47]) {
   print_error("Instruction 28: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[47];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 28");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[18] = result;
   initialized[18] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 18, 44, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -38.7910728f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_1: expected %.8f, got %.8f\n", -38.7910728f, result);
       verification_errors++;
   } else {
       print_success("reg_18_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[9] = 0.245815635f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[52] || !initialized[47]) {
   print_error("Instruction 30: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[52];
src2 = registers[47];
 result = src1 * src2;
   registers[50] = result;
   initialized[50] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 50, 52, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 4.62365007f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_50_1: expected %.8f, got %.8f\n", 4.62365007f, result);
       verification_errors++;
   } else {
       print_success("reg_50_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[12] || !initialized[25]) {
   print_error("Instruction 31: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[25];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 31");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[48] = result;
   initialized[48] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 48, 12, 25, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.05876147f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_48_2: expected %.8f, got %.8f\n", 0.05876147f, result);
       verification_errors++;
   } else {
       print_success("reg_48_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[0] = -29.0235596f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[46] = -1.9150579f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   registers[7] = -0.551368892f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[7] || !initialized[0]) {
   print_error("Instruction 35: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[0];
 result = src1 * src2;
   registers[54] = result;
   initialized[54] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 54, 7, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 16.0026875f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_54_2: expected %.8f, got %.8f\n", 16.0026875f, result);
       verification_errors++;
   } else {
       print_success("reg_54_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[46] || !initialized[7]) {
   print_error("Instruction 36: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[7];
 result = src1 * src2;
   registers[8] = result;
   initialized[8] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 8, 46, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.05590332f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_2: expected %.8f, got %.8f\n", 1.05590332f, result);
       verification_errors++;
   } else {
       print_success("reg_8_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[49] = -0.0354166068f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   registers[15] = 9.79710102f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[7] || !initialized[49]) {
   print_error("Instruction 39: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[49];
 result = src1 - src2;
   registers[61] = result;
   initialized[61] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 61, 7, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.515952289f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_1: expected %.8f, got %.8f\n", -0.515952289f, result);
       verification_errors++;
   } else {
       print_success("reg_61_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[1] = 0.000480108662f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   registers[18] = 0.00192043465f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   registers[47] = 0.0307269543f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   if (!initialized[15] || !initialized[8]) {
   print_error("Instruction 43: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[15];
src2 = registers[8];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 43");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 15, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 9.2784071f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_1: expected %.8f, got %.8f\n", 9.2784071f, result);
       verification_errors++;
   } else {
       print_success("reg_55_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[21] = 0.232832745f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   registers[22] = 0.668288052f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[22] || !initialized[21]) {
   print_error("Instruction 46: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[22];
src2 = registers[21];
 result = src1 - src2;
   registers[12] = result;
   initialized[12] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 12, 22, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.435455322f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_12_2: expected %.8f, got %.8f\n", 0.435455322f, result);
       verification_errors++;
   } else {
       print_success("reg_12_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[59] = 81.2188644f;
   initialized[59] = true;
   printf("INIT: reg[%d] = %.8f\n", 59, registers[59]);

   if (!initialized[21] || !initialized[12]) {
   print_error("Instruction 48: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[12];
 result = src1 - src2;
   registers[58] = result;
   initialized[58] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 58, 21, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.202622578f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_1: expected %.8f, got %.8f\n", -0.202622578f, result);
       verification_errors++;
   } else {
       print_success("reg_58_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[59] || !initialized[12]) {
   print_error("Instruction 49: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[59];
src2 = registers[12];
 result = src1 * src2;
   registers[18] = result;
   initialized[18] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 18, 59, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 35.3671875f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_3: expected %.8f, got %.8f\n", 35.3671875f, result);
       verification_errors++;
   } else {
       print_success("reg_18_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[62] = 0.491631269f;
   initialized[62] = true;
   printf("INIT: reg[%d] = %.8f\n", 62, registers[62]);

   if (!initialized[21] || !initialized[58]) {
   print_error("Instruction 51: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[58];
 result = src1 - src2;
   registers[33] = result;
   initialized[33] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 33, 21, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.435455322f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_33_1: expected %.8f, got %.8f\n", 0.435455322f, result);
       verification_errors++;
   } else {
       print_success("reg_33_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[58] || !initialized[21]) {
   print_error("Instruction 52: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[21];
 result = src1 * src2;
   registers[34] = result;
   initialized[34] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 34, 58, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0471771695f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_34_1: expected %.8f, got %.8f\n", -0.0471771695f, result);
       verification_errors++;
   } else {
       print_success("reg_34_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[33] || !initialized[58]) {
   print_error("Instruction 53: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[33];
src2 = registers[58];
 result = src1 * src2;
   registers[60] = result;
   initialized[60] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 60, 33, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0882330835f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_60_2: expected %.8f, got %.8f\n", -0.0882330835f, result);
       verification_errors++;
   } else {
       print_success("reg_60_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[58] || !initialized[22]) {
   print_error("Instruction 54: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[22];
 result = src1 - src2;
   registers[16] = result;
   initialized[16] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 16, 58, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.870910645f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_2: expected %.8f, got %.8f\n", -0.870910645f, result);
       verification_errors++;
   } else {
       print_success("reg_16_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[4] = 0.000480108662f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   registers[37] = -0.125166327f;
   initialized[37] = true;
   printf("INIT: reg[%d] = %.8f\n", 37, registers[37]);

   registers[17] = -0.000166329701f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   if (!initialized[37] || !initialized[17]) {
   print_error("Instruction 58: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[37];
src2 = registers[17];
 result = src1 - src2;
   registers[20] = result;
   initialized[20] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 20, 37, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.125f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_2: expected %.8f, got %.8f\n", -0.125f, result);
       verification_errors++;
   } else {
       print_success("reg_20_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[29] = -256.068665f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[56] = 26.0425701f;
   initialized[56] = true;
   printf("INIT: reg[%d] = %.8f\n", 56, registers[56]);

   if (!initialized[29] || !initialized[20]) {
   print_error("Instruction 61: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[20];
 result = src1 - src2;
   registers[21] = result;
   initialized[21] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 21, 29, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -255.943665f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_3: expected %.8f, got %.8f\n", -255.943665f, result);
       verification_errors++;
   } else {
       print_success("reg_21_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[17] || !initialized[21]) {
   print_error("Instruction 62: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[17];
src2 = registers[21];
 result = src1 * src2;
   registers[40] = result;
   initialized[40] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 40, 17, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0425710343f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_1: expected %.8f, got %.8f\n", 0.0425710343f, result);
       verification_errors++;
   } else {
       print_success("reg_40_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[24] = 0.491631269f;
   initialized[24] = true;
   printf("INIT: reg[%d] = %.8f\n", 24, registers[24]);

   if (!initialized[40] || !initialized[56]) {
   print_error("Instruction 64: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[56];
 result = src1 - src2;
   registers[52] = result;
   initialized[52] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 52, 40, 56, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -26.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_2: expected %.8f, got %.8f\n", -26.0f, result);
       verification_errors++;
   } else {
       print_success("reg_52_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[37] || !initialized[17]) {
   print_error("Instruction 65: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[37];
src2 = registers[17];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 65");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[18] = result;
   initialized[18] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 18, 37, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 752.519409f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_4: expected %.8f, got %.8f\n", 752.519409f, result);
       verification_errors++;
   } else {
       print_success("reg_18_4 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[52] || !initialized[37]) {
   print_error("Instruction 66: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[52];
src2 = registers[37];
 result = src1 * src2;
   registers[35] = result;
   initialized[35] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 35, 52, 37, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 3.25432444f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_1: expected %.8f, got %.8f\n", 3.25432444f, result);
       verification_errors++;
   } else {
       print_success("reg_35_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[48] = 0.122907817f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   registers[26] = 0.906509459f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   registers[42] = -1.29295993f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   if (!initialized[42] || !initialized[26]) {
   print_error("Instruction 70: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[26];
 result = src1 * src2;
   registers[47] = result;
   initialized[47] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 47, 42, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.1720804f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_3: expected %.8f, got %.8f\n", -1.1720804f, result);
       verification_errors++;
   } else {
       print_success("reg_47_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[47] || !initialized[26]) {
   print_error("Instruction 71: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[26];
 result = src1 * src2;
   registers[55] = result;
   initialized[55] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 55, 47, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.06250203f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_2: expected %.8f, got %.8f\n", -1.06250203f, result);
       verification_errors++;
   } else {
       print_success("reg_55_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[47] || !initialized[55]) {
   print_error("Instruction 72: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[55];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 72");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[23] = result;
   initialized[23] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 23, 47, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.10313237f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_1: expected %.8f, got %.8f\n", 1.10313237f, result);
       verification_errors++;
   } else {
       print_success("reg_23_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[55] || !initialized[47]) {
   print_error("Instruction 73: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[47];
 result = src1 * src2;
   registers[33] = result;
   initialized[33] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 33, 55, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.24533784f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_33_2: expected %.8f, got %.8f\n", 1.24533784f, result);
       verification_errors++;
   } else {
       print_success("reg_33_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[55] || !initialized[42]) {
   print_error("Instruction 74: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[42];
 result = src1 - src2;
   registers[4] = result;
   initialized[4] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 4, 55, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.230457902f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_2: expected %.8f, got %.8f\n", 0.230457902f, result);
       verification_errors++;
   } else {
       print_success("reg_4_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[48] = 128.76181f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   if (!initialized[33] || !initialized[48]) {
   print_error("Instruction 76: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[33];
src2 = registers[48];
 result = src1 - src2;
   registers[49] = result;
   initialized[49] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 49, 33, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -127.516472f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_49_3: expected %.8f, got %.8f\n", -127.516472f, result);
       verification_errors++;
   } else {
       print_success("reg_49_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[21] = 0.000120027165f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   if (!initialized[26] || !initialized[48]) {
   print_error("Instruction 78: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[26];
src2 = registers[48];
 result = src1 - src2;
   registers[14] = result;
   initialized[14] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 14, 26, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -127.855301f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_2: expected %.8f, got %.8f\n", -127.855301f, result);
       verification_errors++;
   } else {
       print_success("reg_14_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[49] || !initialized[42]) {
   print_error("Instruction 79: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[42];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 79");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[18] = result;
   initialized[18] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 18, 49, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 98.6236877f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_5: expected %.8f, got %.8f\n", 98.6236877f, result);
       verification_errors++;
   } else {
       print_success("reg_18_5 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[5] = -0.488473147f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[0] = -0.828124821f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   if (!initialized[5] || !initialized[0]) {
   print_error("Instruction 82: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[0];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 82");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[31] = result;
   initialized[31] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 31, 5, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.589854479f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_1: expected %.8f, got %.8f\n", 0.589854479f, result);
       verification_errors++;
   } else {
       print_success("reg_31_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 83: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 - src2;
   registers[40] = result;
   initialized[40] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 40, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.339651674f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_2: expected %.8f, got %.8f\n", -0.339651674f, result);
       verification_errors++;
   } else {
       print_success("reg_40_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[40] || !initialized[0]) {
   print_error("Instruction 84: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[0];
 result = src1 - src2;
   registers[9] = result;
   initialized[9] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 9, 40, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.488473147f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_2: expected %.8f, got %.8f\n", 0.488473147f, result);
       verification_errors++;
   } else {
       print_success("reg_9_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[5] || !initialized[9]) {
   print_error("Instruction 85: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[9];
 result = src1 * src2;
   registers[62] = result;
   initialized[62] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 62, 5, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.238606021f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_62_2: expected %.8f, got %.8f\n", -0.238606021f, result);
       verification_errors++;
   } else {
       print_success("reg_62_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[40] || !initialized[5]) {
   print_error("Instruction 86: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[5];
 result = src1 - src2;
   registers[53] = result;
   initialized[53] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 53, 40, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.148821473f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_1: expected %.8f, got %.8f\n", 0.148821473f, result);
       verification_errors++;
   } else {
       print_success("reg_53_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[40] || !initialized[31]) {
   print_error("Instruction 87: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[31];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 87");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[58] = result;
   initialized[58] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 58, 40, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.57582283f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_2: expected %.8f, got %.8f\n", -0.57582283f, result);
       verification_errors++;
   } else {
       print_success("reg_58_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[12] = 0.491631269f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[25] = -0.48142302f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   if (!initialized[31] || !initialized[53]) {
   print_error("Instruction 90: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[53];
 result = src1 - src2;
   registers[17] = result;
   initialized[17] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 17, 31, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.441033006f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_17_3: expected %.8f, got %.8f\n", 0.441033006f, result);
       verification_errors++;
   } else {
       print_success("reg_17_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[25] || !initialized[58]) {
   print_error("Instruction 91: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[58];
 result = src1 - src2;
   registers[26] = result;
   initialized[26] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 26, 25, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0943998098f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_3: expected %.8f, got %.8f\n", 0.0943998098f, result);
       verification_errors++;
   } else {
       print_success("reg_26_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[35] = -10.140625f;
   initialized[35] = true;
   printf("INIT: reg[%d] = %.8f\n", 35, registers[35]);

   registers[21] = -11.0625372f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   if (!initialized[21] || !initialized[35]) {
   print_error("Instruction 94: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[35];
 result = src1 - src2;
   registers[57] = result;
   initialized[57] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 57, 21, 35, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.921912193f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_57_1: expected %.8f, got %.8f\n", -0.921912193f, result);
       verification_errors++;
   } else {
       print_success("reg_57_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[35] || !initialized[21]) {
   print_error("Instruction 95: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[21];
 result = src1 - src2;
   registers[46] = result;
   initialized[46] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 46, 35, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.921912193f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_3: expected %.8f, got %.8f\n", 0.921912193f, result);
       verification_errors++;
   } else {
       print_success("reg_46_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[21] || !initialized[57]) {
   print_error("Instruction 96: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[57];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 96");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[54] = result;
   initialized[54] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 54, 21, 57, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 11.9995565f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_54_3: expected %.8f, got %.8f\n", 11.9995565f, result);
       verification_errors++;
   } else {
       print_success("reg_54_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[21] || !initialized[57]) {
   print_error("Instruction 97: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[57];
 result = src1 - src2;
   registers[61] = result;
   initialized[61] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 61, 21, 57, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -10.140625f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_2: expected %.8f, got %.8f\n", -10.140625f, result);
       verification_errors++;
   } else {
       print_success("reg_61_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[26] = 0.00435522338f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[54] || !initialized[61]) {
   print_error("Instruction 99: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[61];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 99");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 54, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.18331528f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_3: expected %.8f, got %.8f\n", -1.18331528f, result);
       verification_errors++;
   } else {
       print_success("reg_55_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[61] || !initialized[26]) {
   print_error("Instruction 100: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[61];
src2 = registers[26];
 result = src1 * src2;
   registers[25] = result;
   initialized[25] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 25, 61, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0441646874f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_3: expected %.8f, got %.8f\n", -0.0441646874f, result);
       verification_errors++;
   } else {
       print_success("reg_25_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[55] || !initialized[25]) {
   print_error("Instruction 101: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[25];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 101");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[50] = result;
   initialized[50] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 50, 55, 25, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 26.7932453f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_50_2: expected %.8f, got %.8f\n", 26.7932453f, result);
       verification_errors++;
   } else {
       print_success("reg_50_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[54] || !initialized[55]) {
   print_error("Instruction 102: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[55];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 54, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -14.1992588f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_2: expected %.8f, got %.8f\n", -14.1992588f, result);
       verification_errors++;
   } else {
       print_success("reg_1_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[28] = 0.000240054331f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   registers[19] = -399.980865f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   registers[61] = -0.0293556154f;
   initialized[61] = true;
   printf("INIT: reg[%d] = %.8f\n", 61, registers[61]);

   if (!initialized[61] || !initialized[19]) {
   print_error("Instruction 106: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[61];
src2 = registers[19];
 result = src1 * src2;
   registers[22] = result;
   initialized[22] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 22, 61, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 11.7416849f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_22_2: expected %.8f, got %.8f\n", 11.7416849f, result);
       verification_errors++;
   } else {
       print_success("reg_22_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[46] = -0.0256852694f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   if (!initialized[61] || !initialized[19]) {
   print_error("Instruction 108: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[61];
src2 = registers[19];
 result = src1 * src2;
   registers[57] = result;
   initialized[57] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 57, 61, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 11.7416849f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_57_2: expected %.8f, got %.8f\n", 11.7416849f, result);
       verification_errors++;
   } else {
       print_success("reg_57_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[46] || !initialized[61]) {
   print_error("Instruction 109: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[61];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 109");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[45] = result;
   initialized[45] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 45, 46, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.874969542f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_45_1: expected %.8f, got %.8f\n", 0.874969542f, result);
       verification_errors++;
   } else {
       print_success("reg_45_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[50] = 0.0614539087f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[15] = 0.983262539f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[46] || !initialized[22]) {
   print_error("Instruction 112: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[22];
 result = src1 * src2;
   registers[49] = result;
   initialized[49] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 49, 46, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.301588327f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_49_4: expected %.8f, got %.8f\n", -0.301588327f, result);
       verification_errors++;
   } else {
       print_success("reg_49_4 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[45] || !initialized[61]) {
   print_error("Instruction 113: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[45];
src2 = registers[61];
 result = src1 - src2;
   registers[36] = result;
   initialized[36] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 36, 45, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.904325128f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_36_1: expected %.8f, got %.8f\n", 0.904325128f, result);
       verification_errors++;
   } else {
       print_success("reg_36_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[26] = 0.000960217323f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[19] || !initialized[36]) {
   print_error("Instruction 115: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[36];
 result = src1 * src2;
   registers[37] = result;
   initialized[37] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 37, 19, 36, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -361.712738f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_2: expected %.8f, got %.8f\n", -361.712738f, result);
       verification_errors++;
   } else {
       print_success("reg_37_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[49] = 1.87494266f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   registers[57] = 315.626709f;
   initialized[57] = true;
   printf("INIT: reg[%d] = %.8f\n", 57, registers[57]);

   registers[29] = -14.1260338f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[7] = 0.245815635f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[29] || !initialized[49]) {
   print_error("Instruction 120: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[49];
 result = src1 - src2;
   registers[11] = result;
   initialized[11] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 11, 29, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -16.0009766f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_11_1: expected %.8f, got %.8f\n", -16.0009766f, result);
       verification_errors++;
   } else {
       print_success("reg_11_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[11] || !initialized[49]) {
   print_error("Instruction 121: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[11];
src2 = registers[49];
 result = src1 * src2;
   registers[42] = result;
   initialized[42] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 42, 11, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -30.0009136f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_42_2: expected %.8f, got %.8f\n", -30.0009136f, result);
       verification_errors++;
   } else {
       print_success("reg_42_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[29] || !initialized[49]) {
   print_error("Instruction 122: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[49];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 122");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[56] = result;
   initialized[56] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 56, 29, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -7.53411531f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_56_2: expected %.8f, got %.8f\n", -7.53411531f, result);
       verification_errors++;
   } else {
       print_success("reg_56_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[57] || !initialized[42]) {
   print_error("Instruction 123: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[57];
src2 = registers[42];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 123");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[10] = result;
   initialized[10] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 10, 57, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -10.5205698f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_1: expected %.8f, got %.8f\n", -10.5205698f, result);
       verification_errors++;
   } else {
       print_success("reg_10_1 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[46] = 2.90347528f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   if (!initialized[56] || !initialized[46]) {
   print_error("Instruction 125: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[56];
src2 = registers[46];
 result = src1 - src2;
   registers[6] = result;
   initialized[6] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 6, 56, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -10.4375906f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_2: expected %.8f, got %.8f\n", -10.4375906f, result);
       verification_errors++;
   } else {
       print_success("reg_6_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[43] = 0.245815635f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   if (!initialized[49] || !initialized[6]) {
   print_error("Instruction 127: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[6];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 127");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[37] = result;
   initialized[37] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 37, 49, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.179633662f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_3: expected %.8f, got %.8f\n", -0.179633662f, result);
       verification_errors++;
   } else {
       print_success("reg_37_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[0], -0.828124821f, EPSILON)) {
printf("[ERROR] Final reg[0] mismatch: expected -0.828124821, got %.8f\n", registers[0]);
       verification_errors++;
   } else {
       print_success("Final reg[0] matches: -0.828124821");
   }

   total_checks++;
   if (!float_equal(registers[1], -14.1992588f, EPSILON)) {
printf("[ERROR] Final reg[1] mismatch: expected -14.1992588, got %.8f\n", registers[1]);
       verification_errors++;
   } else {
       print_success("Final reg[1] matches: -14.1992588");
   }

   total_checks++;
   if (!float_equal(registers[3], -0.0413844883f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected -0.0413844883, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: -0.0413844883");
   }

   total_checks++;
   if (!float_equal(registers[4], 0.230457902f, EPSILON)) {
printf("[ERROR] Final reg[4] mismatch: expected 0.230457902, got %.8f\n", registers[4]);
       verification_errors++;
   } else {
       print_success("Final reg[4] matches: 0.230457902");
   }

   total_checks++;
   if (!float_equal(registers[5], -0.488473147f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected -0.488473147, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: -0.488473147");
   }

   total_checks++;
   if (!float_equal(registers[6], -10.4375906f, EPSILON)) {
printf("[ERROR] Final reg[6] mismatch: expected -10.4375906, got %.8f\n", registers[6]);
       verification_errors++;
   } else {
       print_success("Final reg[6] matches: -10.4375906");
   }

   total_checks++;
   if (!float_equal(registers[7], 0.245815635f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected 0.245815635, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: 0.245815635");
   }

   total_checks++;
   if (!float_equal(registers[8], 1.05590332f, EPSILON)) {
printf("[ERROR] Final reg[8] mismatch: expected 1.05590332, got %.8f\n", registers[8]);
       verification_errors++;
   } else {
       print_success("Final reg[8] matches: 1.05590332");
   }

   total_checks++;
   if (!float_equal(registers[9], 0.488473147f, EPSILON)) {
printf("[ERROR] Final reg[9] mismatch: expected 0.488473147, got %.8f\n", registers[9]);
       verification_errors++;
   } else {
       print_success("Final reg[9] matches: 0.488473147");
   }

   total_checks++;
   if (!float_equal(registers[10], -10.5205698f, EPSILON)) {
printf("[ERROR] Final reg[10] mismatch: expected -10.5205698, got %.8f\n", registers[10]);
       verification_errors++;
   } else {
       print_success("Final reg[10] matches: -10.5205698");
   }

   total_checks++;
   if (!float_equal(registers[11], -16.0009766f, EPSILON)) {
printf("[ERROR] Final reg[11] mismatch: expected -16.0009766, got %.8f\n", registers[11]);
       verification_errors++;
   } else {
       print_success("Final reg[11] matches: -16.0009766");
   }

   total_checks++;
   if (!float_equal(registers[12], 0.491631269f, EPSILON)) {
printf("[ERROR] Final reg[12] mismatch: expected 0.491631269, got %.8f\n", registers[12]);
       verification_errors++;
   } else {
       print_success("Final reg[12] matches: 0.491631269");
   }

   total_checks++;
   if (!float_equal(registers[13], 1.58990979f, EPSILON)) {
printf("[ERROR] Final reg[13] mismatch: expected 1.58990979, got %.8f\n", registers[13]);
       verification_errors++;
   } else {
       print_success("Final reg[13] matches: 1.58990979");
   }

   total_checks++;
   if (!float_equal(registers[14], -127.855301f, EPSILON)) {
printf("[ERROR] Final reg[14] mismatch: expected -127.855301, got %.8f\n", registers[14]);
       verification_errors++;
   } else {
       print_success("Final reg[14] matches: -127.855301");
   }

   total_checks++;
   if (!float_equal(registers[15], 0.983262539f, EPSILON)) {
printf("[ERROR] Final reg[15] mismatch: expected 0.983262539, got %.8f\n", registers[15]);
       verification_errors++;
   } else {
       print_success("Final reg[15] matches: 0.983262539");
   }

   total_checks++;
   if (!float_equal(registers[16], -0.870910645f, EPSILON)) {
printf("[ERROR] Final reg[16] mismatch: expected -0.870910645, got %.8f\n", registers[16]);
       verification_errors++;
   } else {
       print_success("Final reg[16] matches: -0.870910645");
   }

   total_checks++;
   if (!float_equal(registers[17], 0.441033006f, EPSILON)) {
printf("[ERROR] Final reg[17] mismatch: expected 0.441033006, got %.8f\n", registers[17]);
       verification_errors++;
   } else {
       print_success("Final reg[17] matches: 0.441033006");
   }

   total_checks++;
   if (!float_equal(registers[18], 98.6236877f, EPSILON)) {
printf("[ERROR] Final reg[18] mismatch: expected 98.6236877, got %.8f\n", registers[18]);
       verification_errors++;
   } else {
       print_success("Final reg[18] matches: 98.6236877");
   }

   total_checks++;
   if (!float_equal(registers[19], -399.980865f, EPSILON)) {
printf("[ERROR] Final reg[19] mismatch: expected -399.980865, got %.8f\n", registers[19]);
       verification_errors++;
   } else {
       print_success("Final reg[19] matches: -399.980865");
   }

   total_checks++;
   if (!float_equal(registers[20], -0.125f, EPSILON)) {
printf("[ERROR] Final reg[20] mismatch: expected -0.125, got %.8f\n", registers[20]);
       verification_errors++;
   } else {
       print_success("Final reg[20] matches: -0.125");
   }

   total_checks++;
   if (!float_equal(registers[21], -11.0625372f, EPSILON)) {
printf("[ERROR] Final reg[21] mismatch: expected -11.0625372, got %.8f\n", registers[21]);
       verification_errors++;
   } else {
       print_success("Final reg[21] matches: -11.0625372");
   }

   total_checks++;
   if (!float_equal(registers[22], 11.7416849f, EPSILON)) {
printf("[ERROR] Final reg[22] mismatch: expected 11.7416849, got %.8f\n", registers[22]);
       verification_errors++;
   } else {
       print_success("Final reg[22] matches: 11.7416849");
   }

   total_checks++;
   if (!float_equal(registers[23], 1.10313237f, EPSILON)) {
printf("[ERROR] Final reg[23] mismatch: expected 1.10313237, got %.8f\n", registers[23]);
       verification_errors++;
   } else {
       print_success("Final reg[23] matches: 1.10313237");
   }

   total_checks++;
   if (!float_equal(registers[24], 0.491631269f, EPSILON)) {
printf("[ERROR] Final reg[24] mismatch: expected 0.491631269, got %.8f\n", registers[24]);
       verification_errors++;
   } else {
       print_success("Final reg[24] matches: 0.491631269");
   }

   total_checks++;
   if (!float_equal(registers[25], -0.0441646874f, EPSILON)) {
printf("[ERROR] Final reg[25] mismatch: expected -0.0441646874, got %.8f\n", registers[25]);
       verification_errors++;
   } else {
       print_success("Final reg[25] matches: -0.0441646874");
   }

   total_checks++;
   if (!float_equal(registers[26], 0.000960217323f, EPSILON)) {
printf("[ERROR] Final reg[26] mismatch: expected 0.000960217323, got %.8f\n", registers[26]);
       verification_errors++;
   } else {
       print_success("Final reg[26] matches: 0.000960217323");
   }

   total_checks++;
   if (!float_equal(registers[28], 0.000240054331f, EPSILON)) {
printf("[ERROR] Final reg[28] mismatch: expected 0.000240054331, got %.8f\n", registers[28]);
       verification_errors++;
   } else {
       print_success("Final reg[28] matches: 0.000240054331");
   }

   total_checks++;
   if (!float_equal(registers[29], -14.1260338f, EPSILON)) {
printf("[ERROR] Final reg[29] mismatch: expected -14.1260338, got %.8f\n", registers[29]);
       verification_errors++;
   } else {
       print_success("Final reg[29] matches: -14.1260338");
   }

   total_checks++;
   if (!float_equal(registers[31], 0.589854479f, EPSILON)) {
printf("[ERROR] Final reg[31] mismatch: expected 0.589854479, got %.8f\n", registers[31]);
       verification_errors++;
   } else {
       print_success("Final reg[31] matches: 0.589854479");
   }

   total_checks++;
   if (!float_equal(registers[32], 0.983262539f, EPSILON)) {
printf("[ERROR] Final reg[32] mismatch: expected 0.983262539, got %.8f\n", registers[32]);
       verification_errors++;
   } else {
       print_success("Final reg[32] matches: 0.983262539");
   }

   total_checks++;
   if (!float_equal(registers[33], 1.24533784f, EPSILON)) {
printf("[ERROR] Final reg[33] mismatch: expected 1.24533784, got %.8f\n", registers[33]);
       verification_errors++;
   } else {
       print_success("Final reg[33] matches: 1.24533784");
   }

   total_checks++;
   if (!float_equal(registers[34], -0.0471771695f, EPSILON)) {
printf("[ERROR] Final reg[34] mismatch: expected -0.0471771695, got %.8f\n", registers[34]);
       verification_errors++;
   } else {
       print_success("Final reg[34] matches: -0.0471771695");
   }

   total_checks++;
   if (!float_equal(registers[35], -10.140625f, EPSILON)) {
printf("[ERROR] Final reg[35] mismatch: expected -10.140625, got %.8f\n", registers[35]);
       verification_errors++;
   } else {
       print_success("Final reg[35] matches: -10.140625");
   }

   total_checks++;
   if (!float_equal(registers[36], 0.904325128f, EPSILON)) {
printf("[ERROR] Final reg[36] mismatch: expected 0.904325128, got %.8f\n", registers[36]);
       verification_errors++;
   } else {
       print_success("Final reg[36] matches: 0.904325128");
   }

   total_checks++;
   if (!float_equal(registers[37], -0.179633662f, EPSILON)) {
printf("[ERROR] Final reg[37] mismatch: expected -0.179633662, got %.8f\n", registers[37]);
       verification_errors++;
   } else {
       print_success("Final reg[37] matches: -0.179633662");
   }

   total_checks++;
   if (!float_equal(registers[40], -0.339651674f, EPSILON)) {
printf("[ERROR] Final reg[40] mismatch: expected -0.339651674, got %.8f\n", registers[40]);
       verification_errors++;
   } else {
       print_success("Final reg[40] matches: -0.339651674");
   }

   total_checks++;
   if (!float_equal(registers[42], -30.0009136f, EPSILON)) {
printf("[ERROR] Final reg[42] mismatch: expected -30.0009136, got %.8f\n", registers[42]);
       verification_errors++;
   } else {
       print_success("Final reg[42] matches: -30.0009136");
   }

   total_checks++;
   if (!float_equal(registers[43], 0.245815635f, EPSILON)) {
printf("[ERROR] Final reg[43] mismatch: expected 0.245815635, got %.8f\n", registers[43]);
       verification_errors++;
   } else {
       print_success("Final reg[43] matches: 0.245815635");
   }

   total_checks++;
   if (!float_equal(registers[44], 106.153206f, EPSILON)) {
printf("[ERROR] Final reg[44] mismatch: expected 106.153206, got %.8f\n", registers[44]);
       verification_errors++;
   } else {
       print_success("Final reg[44] matches: 106.153206");
   }

   total_checks++;
   if (!float_equal(registers[45], 0.874969542f, EPSILON)) {
printf("[ERROR] Final reg[45] mismatch: expected 0.874969542, got %.8f\n", registers[45]);
       verification_errors++;
   } else {
       print_success("Final reg[45] matches: 0.874969542");
   }

   total_checks++;
   if (!float_equal(registers[46], 2.90347528f, EPSILON)) {
printf("[ERROR] Final reg[46] mismatch: expected 2.90347528, got %.8f\n", registers[46]);
       verification_errors++;
   } else {
       print_success("Final reg[46] matches: 2.90347528");
   }

   total_checks++;
   if (!float_equal(registers[47], -1.1720804f, EPSILON)) {
printf("[ERROR] Final reg[47] mismatch: expected -1.1720804, got %.8f\n", registers[47]);
       verification_errors++;
   } else {
       print_success("Final reg[47] matches: -1.1720804");
   }

   total_checks++;
   if (!float_equal(registers[48], 128.76181f, EPSILON)) {
printf("[ERROR] Final reg[48] mismatch: expected 128.76181, got %.8f\n", registers[48]);
       verification_errors++;
   } else {
       print_success("Final reg[48] matches: 128.76181");
   }

   total_checks++;
   if (!float_equal(registers[49], 1.87494266f, EPSILON)) {
printf("[ERROR] Final reg[49] mismatch: expected 1.87494266, got %.8f\n", registers[49]);
       verification_errors++;
   } else {
       print_success("Final reg[49] matches: 1.87494266");
   }

   total_checks++;
   if (!float_equal(registers[50], 0.0614539087f, EPSILON)) {
printf("[ERROR] Final reg[50] mismatch: expected 0.0614539087, got %.8f\n", registers[50]);
       verification_errors++;
   } else {
       print_success("Final reg[50] matches: 0.0614539087");
   }

   total_checks++;
   if (!float_equal(registers[52], -26.0f, EPSILON)) {
printf("[ERROR] Final reg[52] mismatch: expected -26.0, got %.8f\n", registers[52]);
       verification_errors++;
   } else {
       print_success("Final reg[52] matches: -26.0");
   }

   total_checks++;
   if (!float_equal(registers[53], 0.148821473f, EPSILON)) {
printf("[ERROR] Final reg[53] mismatch: expected 0.148821473, got %.8f\n", registers[53]);
       verification_errors++;
   } else {
       print_success("Final reg[53] matches: 0.148821473");
   }

   total_checks++;
   if (!float_equal(registers[54], 11.9995565f, EPSILON)) {
printf("[ERROR] Final reg[54] mismatch: expected 11.9995565, got %.8f\n", registers[54]);
       verification_errors++;
   } else {
       print_success("Final reg[54] matches: 11.9995565");
   }

   total_checks++;
   if (!float_equal(registers[55], -1.18331528f, EPSILON)) {
printf("[ERROR] Final reg[55] mismatch: expected -1.18331528, got %.8f\n", registers[55]);
       verification_errors++;
   } else {
       print_success("Final reg[55] matches: -1.18331528");
   }

   total_checks++;
   if (!float_equal(registers[56], -7.53411531f, EPSILON)) {
printf("[ERROR] Final reg[56] mismatch: expected -7.53411531, got %.8f\n", registers[56]);
       verification_errors++;
   } else {
       print_success("Final reg[56] matches: -7.53411531");
   }

   total_checks++;
   if (!float_equal(registers[57], 315.626709f, EPSILON)) {
printf("[ERROR] Final reg[57] mismatch: expected 315.626709, got %.8f\n", registers[57]);
       verification_errors++;
   } else {
       print_success("Final reg[57] matches: 315.626709");
   }

   total_checks++;
   if (!float_equal(registers[58], -0.57582283f, EPSILON)) {
printf("[ERROR] Final reg[58] mismatch: expected -0.57582283, got %.8f\n", registers[58]);
       verification_errors++;
   } else {
       print_success("Final reg[58] matches: -0.57582283");
   }

   total_checks++;
   if (!float_equal(registers[59], 81.2188644f, EPSILON)) {
printf("[ERROR] Final reg[59] mismatch: expected 81.2188644, got %.8f\n", registers[59]);
       verification_errors++;
   } else {
       print_success("Final reg[59] matches: 81.2188644");
   }

   total_checks++;
   if (!float_equal(registers[60], -0.0882330835f, EPSILON)) {
printf("[ERROR] Final reg[60] mismatch: expected -0.0882330835, got %.8f\n", registers[60]);
       verification_errors++;
   } else {
       print_success("Final reg[60] matches: -0.0882330835");
   }

   total_checks++;
   if (!float_equal(registers[61], -0.0293556154f, EPSILON)) {
printf("[ERROR] Final reg[61] mismatch: expected -0.0293556154, got %.8f\n", registers[61]);
       verification_errors++;
   } else {
       print_success("Final reg[61] matches: -0.0293556154");
   }

   total_checks++;
   if (!float_equal(registers[62], -0.238606021f, EPSILON)) {
printf("[ERROR] Final reg[62] mismatch: expected -0.238606021, got %.8f\n", registers[62]);
       verification_errors++;
   } else {
       print_success("Final reg[62] matches: -0.238606021");
   }

   print_header("Verification Summary");
   printf("Total checks performed: %d\n", total_checks);
   printf("Verification errors: %d\n", verification_errors);
   if (verification_errors == 0) {
       print_success("All verifications passed!");
   } else {
   printf("[ERROR] Verification failed with  %d errors\n", verification_errors);
   print_register_state(registers, 64, "final");
   }

 return SUCCESS_CODE;
}
