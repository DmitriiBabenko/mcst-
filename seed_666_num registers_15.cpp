#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<float.h>
#include<stdbool.h>
#include<string.h>
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
        return fabs(a - b) <= epsilon;
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
 Registers: 10 
 Input registers: 

Component 1:
   Instructions: 1 8 2 7 6 5 
 Registers: 12 5 10 3 7 3 
 Input registers: 

Component 2:
   Instructions: 3 
 Registers: 5 
 Input registers: 

Component 3:
   Instructions: 4 
 Registers: 3 
 Input registers: 

Component 4:
   Instructions: 9 
 Registers: 11 
 Input registers: 

*/

int main() {
   printf("Verification of sequence solution\n");
   printf("Seed: 666\n");
   printf("Registers: 15\n");

    float registers[15];
   bool initialized[15] = {false};
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

    print_header("Executing Instructions");

   registers[10] = 0.000960217323f;
   initialized[10] = true;
   printf("INIT: reg[%d] = %.8f\n", 10, registers[10]);

   registers[12] = 0.749878228f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   if (!initialized[12] || !initialized[12]) {
   print_error("Instruction 2: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[12];
   float src2 = registers[12];
   float  result = src1 * src2;
   registers[10] = result;
   initialized[10] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 10, 12, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.562317371f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_2: expected %.8f, got %.8f\n", 0.562317371f, result);
       verification_errors++;
   } else {
       print_success("reg_10_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[5] = 0.983262539f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[3] = 0.000738964882f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   if (!initialized[10] || !initialized[12]) {
   print_error("Instruction 5: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[10];
src2 = registers[12];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 10, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.187560856f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_2: expected %.8f, got %.8f\n", -0.187560856f, result);
       verification_errors++;
   } else {
       print_success("reg_3_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[7] = 1.77531457f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[7] || !initialized[10]) {
   print_error("Instruction 7: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[10];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 7, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.998290241f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_3: expected %.8f, got %.8f\n", 0.998290241f, result);
       verification_errors++;
   } else {
       print_success("reg_3_3 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   if (!initialized[12] || !initialized[10]) {
   print_error("Instruction 8: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[10];
 result = src1 - src2;
   registers[5] = result;
   initialized[5] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 5, 12, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.187560856f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_2: expected %.8f, got %.8f\n", 0.187560856f, result);
       verification_errors++;
   } else {
       print_success("reg_5_2 matches: %.8f");
       printf("                       %.8f\n", result);
   }

   registers[11] = 0.0305175781f;
   initialized[11] = true;
   printf("INIT: reg[%d] = %.8f\n", 11, registers[11]);


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[3], 0.998290241f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected 0.998290241, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: 0.998290241");
   }

   total_checks++;
   if (!float_equal(registers[5], 0.187560856f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected 0.187560856, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: 0.187560856");
   }

   total_checks++;
   if (!float_equal(registers[7], 1.77531457f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected 1.77531457, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: 1.77531457");
   }

   total_checks++;
   if (!float_equal(registers[10], 0.562317371f, EPSILON)) {
printf("[ERROR] Final reg[10] mismatch: expected 0.562317371, got %.8f\n", registers[10]);
       verification_errors++;
   } else {
       print_success("Final reg[10] matches: 0.562317371");
   }

   total_checks++;
   if (!float_equal(registers[11], 0.0305175781f, EPSILON)) {
printf("[ERROR] Final reg[11] mismatch: expected 0.0305175781, got %.8f\n", registers[11]);
       verification_errors++;
   } else {
       print_success("Final reg[11] matches: 0.0305175781");
   }

   total_checks++;
   if (!float_equal(registers[12], 0.749878228f, EPSILON)) {
printf("[ERROR] Final reg[12] mismatch: expected 0.749878228, got %.8f\n", registers[12]);
       verification_errors++;
   } else {
       print_success("Final reg[12] matches: 0.749878228");
   }

   print_header("Verification Summary");
   printf("Total checks performed: %d\n", total_checks);
   printf("Verification errors: %d\n", verification_errors);
   if (verification_errors == 0) {
       print_success("All verifications passed!");
   } else {
   printf("[ERROR] Verification failed with  %d errors\n", verification_errors);
   print_register_state(registers, 15, "final");
   }

 return SUCCESS_CODE;
}
