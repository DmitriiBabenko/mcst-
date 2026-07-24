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
   Instructions: 0 7 1 6 2 3 5 
 Registers: 5 4 0 3 6 1 2 
 Input registers: 

Component 1:
   Instructions: 4 
 Registers: 7 
 Input registers: 

Component 2:
   Instructions: 8 13 11 10 12 9 
 Registers: 7 4 1 0 3 2 
 Input registers: 

Component 3:
   Instructions: 14 18 17 16 15 
 Registers: 0 4 3 1 2 
 Input registers: 

Component 4:
   Instructions: 19 
 Registers: 5 
 Input registers: 

Component 5:
   Instructions: 20 25 22 24 23 
 Registers: 1 3 5 2 7 
 Input registers: 

Component 6:
   Instructions: 21 
 Registers: 6 
 Input registers: 

Component 7:
   Instructions: 26 28 30 31 29 27 
 Registers: 5 3 6 7 1 2 
 Input registers: 

*/

int main() {
   printf("Verification of sequence solution\n");
   printf("Seed: 666\n");
   printf("Registers: 8\n");

    float registers[8];
   bool initialized[8] = {false};
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

    print_header("Executing Instructions");

   registers[5] = -251.807449f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[0] = -0.000337636448f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[6] = 0.0623950586f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   if (!initialized[5] || !initialized[6]) {
   print_error("Instruction 3: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[5];
   float src2 = registers[6];
   float  result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 5, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -251.869843f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_1: expected %.8f, got %.8f\n", -251.869843f, result);
       verification_errors++;
   } else {
       print_success("reg_1_1 matches: ");       printf("                       %.8f", result);
   }

   registers[7] = 9.99999975e-05f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 5: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 - src2;
   registers[2] = result;
   initialized[2] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 2, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 251.807114f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_1: expected %.8f, got %.8f\n", 251.807114f, result);
       verification_errors++;
   } else {
       print_success("reg_2_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[6] || !initialized[0]) {
   print_error("Instruction 6: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[6];
src2 = registers[0];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 6, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0627326965f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_1: expected %.8f, got %.8f\n", 0.0627326965f, result);
       verification_errors++;
   } else {
       print_success("reg_3_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 7: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0850193724f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_1: expected %.8f, got %.8f\n", 0.0850193724f, result);
       verification_errors++;
   } else {
       print_success("reg_4_1 matches: ");       printf("                       %.8f", result);
   }

   registers[7] = 0.811625719f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   registers[2] = 0.24093549f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   if (!initialized[2] || !initialized[7]) {
   print_error("Instruction 10: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[7];
 result = src1 - src2;
   registers[0] = result;
   initialized[0] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 0, 2, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.570690215f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_2: expected %.8f, got %.8f\n", -0.570690215f, result);
       verification_errors++;
   } else {
       print_success("reg_0_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[7]) {
   print_error("Instruction 11: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[7];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 0, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.46318686f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_2: expected %.8f, got %.8f\n", -0.46318686f, result);
       verification_errors++;
   } else {
       print_success("reg_1_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[2]) {
   print_error("Instruction 12: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[2];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 0, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.137499526f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_2: expected %.8f, got %.8f\n", -0.137499526f, result);
       verification_errors++;
   } else {
       print_success("reg_3_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[1]) {
   print_error("Instruction 13: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[1];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 13");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[4] = result;
   initialized[4] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 4, 7, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.75226414f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_2: expected %.8f, got %.8f\n", -1.75226414f, result);
       verification_errors++;
   } else {
       print_success("reg_4_2 matches: ");       printf("                       %.8f", result);
   }

   registers[0] = 245.544815f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[2] = -0.000192438674f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   if (!initialized[0] || !initialized[2]) {
   print_error("Instruction 16: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[2];
 result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 0, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 245.545013f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_3: expected %.8f, got %.8f\n", 245.545013f, result);
       verification_errors++;
   } else {
       print_success("reg_1_3 matches: ");       printf("                       %.8f", result);
   }

   registers[3] = 245.541855f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   if (!initialized[0] || !initialized[3]) {
   print_error("Instruction 18: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[3];
 result = src1 - src2;
   registers[4] = result;
   initialized[4] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 4, 0, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00296020508f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_3: expected %.8f, got %.8f\n", 0.00296020508f, result);
       verification_errors++;
   } else {
       print_success("reg_4_3 matches: ");       printf("                       %.8f", result);
   }

   registers[5] = 0.00135225221f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[1] = -0.0296856631f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   registers[6] = 9.99999975e-05f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[5] = -95.9991837f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   if (!initialized[1] || !initialized[5]) {
   print_error("Instruction 23: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[5];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 23");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[7] = result;
   initialized[7] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 7, 1, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000309228286f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_3: expected %.8f, got %.8f\n", 0.000309228286f, result);
       verification_errors++;
   } else {
       print_success("reg_7_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[5] || !initialized[7]) {
   print_error("Instruction 24: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[7];
 result = src1 * src2;
   registers[2] = result;
   initialized[2] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 2, 5, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0296856631f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_4: expected %.8f, got %.8f\n", -0.0296856631f, result);
       verification_errors++;
   } else {
       print_success("reg_2_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[5]) {
   print_error("Instruction 25: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[5];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 1, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 2.84979939f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_4: expected %.8f, got %.8f\n", 2.84979939f, result);
       verification_errors++;
   } else {
       print_success("reg_3_4 matches: ");       printf("                       %.8f", result);
   }

   registers[5] = 4.99123621f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[2] = 1.18016851f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   if (!initialized[5] || !initialized[2]) {
   print_error("Instruction 28: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[2];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 5, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 5.89049959f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_5: expected %.8f, got %.8f\n", 5.89049959f, result);
       verification_errors++;
   } else {
       print_success("reg_3_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[2] || !initialized[3]) {
   print_error("Instruction 29: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[3];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 2, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 6.95178223f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_5: expected %.8f, got %.8f\n", 6.95178223f, result);
       verification_errors++;
   } else {
       print_success("reg_1_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[3] || !initialized[1]) {
   print_error("Instruction 30: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[1];
 result = src1 * src2;
   registers[6] = result;
   initialized[6] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 6, 3, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 40.9494705f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_3: expected %.8f, got %.8f\n", 40.9494705f, result);
       verification_errors++;
   } else {
       print_success("reg_6_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[6]) {
   print_error("Instruction 31: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[6];
 result = src1 * src2;
   registers[7] = result;
   initialized[7] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 7, 1, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 284.671814f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_4: expected %.8f, got %.8f\n", 284.671814f, result);
       verification_errors++;
   } else {
       print_success("reg_7_4 matches: ");       printf("                       %.8f", result);
   }


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[0], 245.544815f, EPSILON)) {
printf("[ERROR] Final reg[0] mismatch: expected 245.544815, got %.8f\n", registers[0]);
       verification_errors++;
   } else {
       print_success("Final reg[0] matches: 245.544815");
   }

   total_checks++;
   if (!float_equal(registers[1], 6.95178223f, EPSILON)) {
printf("[ERROR] Final reg[1] mismatch: expected 6.95178223, got %.8f\n", registers[1]);
       verification_errors++;
   } else {
       print_success("Final reg[1] matches: 6.95178223");
   }

   total_checks++;
   if (!float_equal(registers[2], 1.18016851f, EPSILON)) {
printf("[ERROR] Final reg[2] mismatch: expected 1.18016851, got %.8f\n", registers[2]);
       verification_errors++;
   } else {
       print_success("Final reg[2] matches: 1.18016851");
   }

   total_checks++;
   if (!float_equal(registers[3], 5.89049959f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected 5.89049959, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: 5.89049959");
   }

   total_checks++;
   if (!float_equal(registers[4], 0.00296020508f, EPSILON)) {
printf("[ERROR] Final reg[4] mismatch: expected 0.00296020508, got %.8f\n", registers[4]);
       verification_errors++;
   } else {
       print_success("Final reg[4] matches: 0.00296020508");
   }

   total_checks++;
   if (!float_equal(registers[5], 4.99123621f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected 4.99123621, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: 4.99123621");
   }

   total_checks++;
   if (!float_equal(registers[6], 40.9494705f, EPSILON)) {
printf("[ERROR] Final reg[6] mismatch: expected 40.9494705, got %.8f\n", registers[6]);
       verification_errors++;
   } else {
       print_success("Final reg[6] matches: 40.9494705");
   }

   total_checks++;
   if (!float_equal(registers[7], 284.671814f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected 284.671814, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: 284.671814");
   }

   print_header("Verification Summary");
   printf("Total checks performed: %d\n", total_checks);
   printf("Verification errors: %d\n", verification_errors);
   if (verification_errors == 0) {
       print_success("All verifications passed!");
   } else {
   printf("[ERROR] Verification failed with  %d errors\n", verification_errors);
   print_register_state(registers, 8, "final");
   }

 return SUCCESS_CODE;
}
