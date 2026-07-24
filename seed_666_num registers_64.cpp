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
   Instructions: 0 3 2 
 Registers: 44 13 54 
 Input registers: 

Component 1:
   Instructions: 1 
 Registers: 6 
 Input registers: 

Component 2:
   Instructions: 4 
 Registers: 43 
 Input registers: 

Component 3:
   Instructions: 5 9 8 7 6 
 Registers: 8 21 60 48 46 
 Input registers: 

Component 4:
   Instructions: 10 14 12 13 11 
 Registers: 0 3 26 16 15 
 Input registers: 

Component 5:
   Instructions: 15 18 17 
 Registers: 17 32 29 
 Input registers: 

Component 6:
   Instructions: 16 
 Registers: 6 
 Input registers: 

Component 7:
   Instructions: 19 
 Registers: 14 
 Input registers: 

Component 8:
   Instructions: 20 23 24 22 
 Registers: 12 52 13 47 
 Input registers: 

Component 9:
   Instructions: 21 
 Registers: 49 
 Input registers: 

Component 10:
   Instructions: 25 27 29 26 
 Registers: 25 20 9 44 
 Input registers: 

Component 11:
   Instructions: 28 
 Registers: 18 
 Input registers: 

Component 12:
   Instructions: 30 32 34 33 31 
 Registers: 49 0 7 46 47 
 Input registers: 

Component 13:
   Instructions: 35 39 36 38 37 
 Registers: 54 61 7 15 49 
 Input registers: 

Component 14:
   Instructions: 40 43 42 44 41 
 Registers: 1 54 46 21 18 
 Input registers: 

Component 15:
   Instructions: 45 
 Registers: 22 
 Input registers: 

Component 16:
   Instructions: 46 49 48 47 
 Registers: 12 18 58 59 
 Input registers: 

Component 17:
   Instructions: 50 54 51 
 Registers: 62 16 33 
 Input registers: 

Component 18:
   Instructions: 52 
 Registers: 34 
 Input registers: 

Component 19:
   Instructions: 53 
 Registers: 60 
 Input registers: 

Component 20:
   Instructions: 55 58 59 56 57 
 Registers: 4 20 29 37 17 
 Input registers: 

Component 21:
   Instructions: 60 63 61 62 
 Registers: 56 24 20 40 
 Input registers: 

Component 22:
   Instructions: 64 
 Registers: 52 
 Input registers: 

Component 23:
   Instructions: 65 68 66 67 
 Registers: 17 26 35 48 
 Input registers: 

Component 24:
   Instructions: 69 
 Registers: 42 
 Input registers: 

Component 25:
   Instructions: 70 72 71 
 Registers: 47 23 55 
 Input registers: 

Component 26:
   Instructions: 73 
 Registers: 33 
 Input registers: 

Component 27:
   Instructions: 74 
 Registers: 4 
 Input registers: 

Component 28:
   Instructions: 75 78 77 76 
 Registers: 48 14 21 49 
 Input registers: 

Component 29:
   Instructions: 79 
 Registers: 18 
 Input registers: 

Component 30:
   Instructions: 80 84 81 82 
 Registers: 5 9 0 31 
 Input registers: 

Component 31:
   Instructions: 83 
 Registers: 40 
 Input registers: 

Component 32:
   Instructions: 85 88 89 87 86 
 Registers: 62 12 25 58 53 
 Input registers: 

Component 33:
   Instructions: 90 92 94 93 91 
 Registers: 17 35 57 21 25 
 Input registers: 

Component 34:
   Instructions: 95 99 97 96 
 Registers: 46 55 61 54 
 Input registers: 

Component 35:
   Instructions: 98 
 Registers: 26 
 Input registers: 

Component 36:
   Instructions: 100 102 101 104 103 
 Registers: 25 1 50 19 28 
 Input registers: 

Component 37:
   Instructions: 105 108 106 107 
 Registers: 61 57 22 46 
 Input registers: 

Component 38:
   Instructions: 109 
 Registers: 45 
 Input registers: 

Component 39:
   Instructions: 110 112 113 111 
 Registers: 50 49 36 15 
 Input registers: 

Component 40:
   Instructions: 114 
 Registers: 26 
 Input registers: 

Component 41:
   Instructions: 115 118 116 119 117 
 Registers: 36 29 49 7 57 
 Input registers: 

Component 42:
   Instructions: 120 122 124 123 121 
 Registers: 11 56 46 10 42 
 Input registers: 

Component 43:
   Instructions: 125 128 127 126 
 Registers: 6 16 37 43 
 Input registers: 

Component 44:
   Instructions: 129 
 Registers: 55 
 Input registers: 

Component 45:
   Instructions: 130 133 131 134 132 
 Registers: 27 41 53 15 1 
 Input registers: 

Component 46:
   Instructions: 135 137 139 136 138 
 Registers: 33 0 51 32 18 
 Input registers: 

Component 47:
   Instructions: 140 142 141 144 143 
 Registers: 32 31 22 6 26 
 Input registers: 

Component 48:
   Instructions: 145 149 146 147 148 
 Registers: 12 13 28 40 62 
 Input registers: 

Component 49:
   Instructions: 150 152 151 
 Registers: 47 46 8 
 Input registers: 

Component 50:
   Instructions: 153 
 Registers: 48 
 Input registers: 

Component 51:
   Instructions: 154 
 Registers: 57 
 Input registers: 

Component 52:
   Instructions: 155 157 156 
 Registers: 21 33 61 
 Input registers: 

Component 53:
   Instructions: 158 
 Registers: 12 
 Input registers: 

Component 54:
   Instructions: 159 
 Registers: 56 
 Input registers: 

Component 55:
   Instructions: 160 164 161 162 
 Registers: 45 55 28 10 
 Input registers: 

Component 56:
   Instructions: 163 
 Registers: 15 
 Input registers: 

Component 57:
   Instructions: 165 169 167 166 168 
 Registers: 21 51 17 39 61 
 Input registers: 

Component 58:
   Instructions: 170 172 174 171 173 
 Registers: 33 2 46 3 8 
 Input registers: 

Component 59:
   Instructions: 175 178 177 179 176 
 Registers: 52 3 23 36 0 
 Input registers: 

Component 60:
   Instructions: 180 183 184 181 
 Registers: 63 28 60 53 
 Input registers: 

Component 61:
   Instructions: 182 
 Registers: 13 
 Input registers: 

Component 62:
   Instructions: 185 189 188 187 186 
 Registers: 13 45 63 35 28 
 Input registers: 

Component 63:
   Instructions: 190 193 191 194 192 
 Registers: 41 37 47 27 44 
 Input registers: 

Component 64:
   Instructions: 195 197 198 196 
 Registers: 35 5 7 10 
 Input registers: 

Component 65:
   Instructions: 199 
 Registers: 26 
 Input registers: 

Component 66:
   Instructions: 200 202 201 204 203 
 Registers: 60 58 40 25 7 
 Input registers: 

Component 67:
   Instructions: 205 208 207 206 
 Registers: 17 47 4 59 
 Input registers: 

Component 68:
   Instructions: 209 
 Registers: 10 
 Input registers: 

Component 69:
   Instructions: 210 212 214 213 211 
 Registers: 50 40 63 24 9 
 Input registers: 

Component 70:
   Instructions: 215 219 218 216 
 Registers: 45 1 6 30 
 Input registers: 

Component 71:
   Instructions: 217 
 Registers: 28 
 Input registers: 

Component 72:
   Instructions: 220 222 224 221 223 
 Registers: 55 48 19 63 58 
 Input registers: 

Component 73:
   Instructions: 225 227 229 228 226 
 Registers: 3 55 32 31 11 
 Input registers: 

Component 74:
   Instructions: 230 233 231 232 
 Registers: 2 31 0 30 
 Input registers: 

Component 75:
   Instructions: 234 
 Registers: 19 
 Input registers: 

Component 76:
   Instructions: 235 237 238 236 
 Registers: 35 17 59 58 
 Input registers: 

Component 77:
   Instructions: 239 
 Registers: 14 
 Input registers: 

Component 78:
   Instructions: 240 244 242 243 241 
 Registers: 29 5 14 42 61 
 Input registers: 

Component 79:
   Instructions: 245 249 247 248 246 
 Registers: 53 10 9 41 43 
 Input registers: 

Component 80:
   Instructions: 250 254 253 252 251 
 Registers: 0 1 23 4 19 
 Input registers: 

Component 81:
   Instructions: 255 258 256 257 
 Registers: 20 24 42 35 
 Input registers: 

Component 82:
   Instructions: 259 
 Registers: 29 
 Input registers: 

Component 83:
   Instructions: 260 263 262 261 
 Registers: 6 50 29 51 
 Input registers: 

Component 84:
   Instructions: 264 
 Registers: 41 
 Input registers: 

Component 85:
   Instructions: 265 267 266 
 Registers: 53 44 38 
 Input registers: 

Component 86:
   Instructions: 268 
 Registers: 50 
 Input registers: 

Component 87:
   Instructions: 269 
 Registers: 20 
 Input registers: 

Component 88:
   Instructions: 270 
 Registers: 51 
 Input registers: 

Component 89:
   Instructions: 271 
 Registers: 60 
 Input registers: 

Component 90:
   Instructions: 272 
 Registers: 43 
 Input registers: 

Component 91:
   Instructions: 273 
 Registers: 26 
 Input registers: 

Component 92:
   Instructions: 274 
 Registers: 28 
 Input registers: 

Component 93:
   Instructions: 275 278 279 277 276 
 Registers: 48 15 52 32 16 
 Input registers: 

Component 94:
   Instructions: 280 284 281 283 282 
 Registers: 53 39 31 11 23 
 Input registers: 

Component 95:
   Instructions: 285 287 286 
 Registers: 50 8 29 
 Input registers: 

Component 96:
   Instructions: 288 
 Registers: 31 
 Input registers: 

Component 97:
   Instructions: 289 
 Registers: 45 
 Input registers: 

Component 98:
   Instructions: 290 292 291 294 293 
 Registers: 45 41 24 61 46 
 Input registers: 

Component 99:
   Instructions: 295 298 299 297 296 
 Registers: 53 62 25 37 24 
 Input registers: 

Component 100:
   Instructions: 300 302 301 304 303 
 Registers: 23 35 25 2 9 
 Input registers: 

Component 101:
   Instructions: 305 308 309 306 307 
 Registers: 5 4 55 19 51 
 Input registers: 

Component 102:
   Instructions: 310 312 314 313 311 
 Registers: 29 26 27 48 56 
 Input registers: 

Component 103:
   Instructions: 315 319 316 318 317 
 Registers: 13 11 50 3 38 
 Input registers: 

Component 104:
   Instructions: 320 324 322 321 323 
 Registers: 57 23 20 10 27 
 Input registers: 

Component 105:
   Instructions: 325 328 329 326 327 
 Registers: 8 14 47 45 13 
 Input registers: 

Component 106:
   Instructions: 330 332 334 331 
 Registers: 35 20 46 39 
 Input registers: 

Component 107:
   Instructions: 333 
 Registers: 60 
 Input registers: 

Component 108:
   Instructions: 335 339 337 338 336 
 Registers: 48 32 1 49 60 
 Input registers: 

Component 109:
   Instructions: 340 344 341 342 343 
 Registers: 55 52 4 53 47 
 Input registers: 

Component 110:
   Instructions: 345 349 348 347 346 
 Registers: 52 56 44 58 40 
 Input registers: 

Component 111:
   Instructions: 350 354 351 353 352 
 Registers: 6 53 9 4 56 
 Input registers: 

Component 112:
   Instructions: 355 357 356 359 358 
 Registers: 6 41 26 47 49 
 Input registers: 

Component 113:
   Instructions: 360 363 364 361 362 
 Registers: 31 1 45 18 33 
 Input registers: 

Component 114:
   Instructions: 365 369 366 368 367 
 Registers: 4 9 7 28 38 
 Input registers: 

Component 115:
   Instructions: 370 372 373 374 371 
 Registers: 9 21 61 14 1 
 Input registers: 

Component 116:
   Instructions: 375 378 379 377 376 
 Registers: 61 27 43 42 32 
 Input registers: 

Component 117:
   Instructions: 380 382 384 381 383 
 Registers: 34 55 53 51 40 
 Input registers: 

Component 118:
   Instructions: 385 
 Registers: 31 
 Input registers: 

Component 119:
   Instructions: 386 389 388 
 Registers: 2 18 4 
 Input registers: 

Component 120:
   Instructions: 387 
 Registers: 53 
 Input registers: 

Component 121:
   Instructions: 390 
 Registers: 23 
 Input registers: 

Component 122:
   Instructions: 391 393 392 
 Registers: 39 41 47 
 Input registers: 

Component 123:
   Instructions: 394 
 Registers: 24 
 Input registers: 

Component 124:
   Instructions: 395 398 399 397 396 
 Registers: 60 24 62 34 9 
 Input registers: 

Component 125:
   Instructions: 400 404 402 403 401 
 Registers: 23 56 59 39 26 
 Input registers: 

Component 126:
   Instructions: 405 408 409 407 406 
 Registers: 40 4 42 22 41 
 Input registers: 

Component 127:
   Instructions: 410 413 414 412 411 
 Registers: 54 4 21 55 49 
 Input registers: 

Component 128:
   Instructions: 415 418 419 417 416 
 Registers: 32 53 10 40 41 
 Input registers: 

Component 129:
   Instructions: 420 422 423 424 421 
 Registers: 34 42 4 37 14 
 Input registers: 

Component 130:
   Instructions: 425 429 428 427 426 
 Registers: 46 40 14 13 26 
 Input registers: 

Component 131:
   Instructions: 430 433 434 432 431 
 Registers: 44 23 55 62 32 
 Input registers: 

Component 132:
   Instructions: 435 438 436 437 
 Registers: 21 35 54 15 
 Input registers: 

Component 133:
   Instructions: 439 
 Registers: 41 
 Input registers: 

Component 134:
   Instructions: 440 443 442 444 441 
 Registers: 27 50 11 26 23 
 Input registers: 

Component 135:
   Instructions: 445 449 447 
 Registers: 54 13 50 
 Input registers: 

Component 136:
   Instructions: 446 
 Registers: 43 
 Input registers: 

Component 137:
   Instructions: 448 
 Registers: 20 
 Input registers: 

Component 138:
   Instructions: 450 454 451 452 
 Registers: 55 5 46 53 
 Input registers: 

Component 139:
   Instructions: 453 
 Registers: 49 
 Input registers: 

Component 140:
   Instructions: 455 459 456 458 457 
 Registers: 39 44 38 55 17 
 Input registers: 

Component 141:
   Instructions: 460 464 461 462 
 Registers: 45 61 29 5 
 Input registers: 

Component 142:
   Instructions: 463 
 Registers: 57 
 Input registers: 

Component 143:
   Instructions: 465 469 468 467 466 
 Registers: 42 44 52 33 0 
 Input registers: 

Component 144:
   Instructions: 470 
 Registers: 33 
 Input registers: 

Component 145:
   Instructions: 471 474 472 473 
 Registers: 41 34 7 59 
 Input registers: 

Component 146:
   Instructions: 475 479 478 477 476 
 Registers: 9 26 14 59 42 
 Input registers: 

Component 147:
   Instructions: 480 484 481 483 482 
 Registers: 42 24 39 41 7 
 Input registers: 

Component 148:
   Instructions: 485 489 488 
 Registers: 63 34 18 
 Input registers: 

Component 149:
   Instructions: 486 
 Registers: 39 
 Input registers: 

Component 150:
   Instructions: 487 
 Registers: 33 
 Input registers: 

Component 151:
   Instructions: 490 493 492 491 
 Registers: 9 27 15 53 
 Input registers: 

Component 152:
   Instructions: 494 
 Registers: 36 
 Input registers: 

Component 153:
   Instructions: 495 497 498 496 
 Registers: 12 59 46 58 
 Input registers: 

Component 154:
   Instructions: 499 
 Registers: 37 
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

   registers[44] = -0.929698706f;
   initialized[44] = true;
   printf("INIT: reg[%d] = %.8f\n", 44, registers[44]);

   registers[6] = 9.99999975e-05f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[54] = -0.334022224f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   if (!initialized[44] || !initialized[54]) {
   print_error("Instruction 3: Using uninitialized register");
   return FLOAT_ERROR;
   }
   float src1 = registers[44];
   float src2 = registers[54];
   float  result = src1 - src2;
   registers[13] = result;
   initialized[13] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 13, 44, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.595676482f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_1: expected %.8f, got %.8f\n", -0.595676482f, result);
       verification_errors++;
   } else {
       print_success("reg_13_1 matches: ");       printf("                       %.8f", result);
   }

   registers[43] = 9.99999975e-05f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   registers[8] = 1.2779088f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   registers[46] = 1.25116742f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   if (!initialized[8] || !initialized[46]) {
   print_error("Instruction 7: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[8];
src2 = registers[46];
 result = src1 - src2;
   registers[48] = result;
   initialized[48] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 48, 8, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0267413855f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_48_1: expected %.8f, got %.8f\n", 0.0267413855f, result);
       verification_errors++;
   } else {
       print_success("reg_48_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[8] || !initialized[48]) {
   print_error("Instruction 8: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[8];
src2 = registers[48];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 8");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[60] = result;
   initialized[60] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 60, 8, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 47.7876816f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_60_1: expected %.8f, got %.8f\n", 47.7876816f, result);
       verification_errors++;
   } else {
       print_success("reg_60_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[60] || !initialized[8]) {
   print_error("Instruction 9: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[60];
src2 = registers[8];
 result = src1 * src2;
   registers[21] = result;
   initialized[21] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 21, 60, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 61.0682983f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_1: expected %.8f, got %.8f\n", 61.0682983f, result);
       verification_errors++;
   } else {
       print_success("reg_21_1 matches: ");       printf("                       %.8f", result);
   }

   registers[0] = -32.1683731f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[15] = 0.0842735097f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[15] || !initialized[0]) {
   print_error("Instruction 12: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[15];
src2 = registers[0];
 result = src1 * src2;
   registers[26] = result;
   initialized[26] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 26, 15, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.71094179f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_1: expected %.8f, got %.8f\n", -2.71094179f, result);
       verification_errors++;
   } else {
       print_success("reg_26_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[26]) {
   print_error("Instruction 13: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[26];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 13");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[16] = result;
   initialized[16] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 16, 0, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 11.8661242f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_1: expected %.8f, got %.8f\n", 11.8661242f, result);
       verification_errors++;
   } else {
       print_success("reg_16_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[26]) {
   print_error("Instruction 14: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[26];
 result = src1 - src2;
   registers[3] = result;
   initialized[3] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 3, 0, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -29.4574318f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_1: expected %.8f, got %.8f\n", -29.4574318f, result);
       verification_errors++;
   } else {
       print_success("reg_3_1 matches: ");       printf("                       %.8f", result);
   }

   registers[17] = -0.000498757872f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   registers[6] = 9.99999975e-05f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[29] = 0.000970735622f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   if (!initialized[17] || !initialized[29]) {
   print_error("Instruction 18: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[17];
src2 = registers[29];
 result = src1 - src2;
   registers[32] = result;
   initialized[32] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 32, 17, 29, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00146949349f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_32_1: expected %.8f, got %.8f\n", -0.00146949349f, result);
       verification_errors++;
   } else {
       print_success("reg_32_1 matches: ");       printf("                       %.8f", result);
   }

   registers[14] = 9.99999975e-05f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   registers[12] = 1.59691775f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[49] = 9.99999975e-05f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   registers[47] = 2.5040431f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   if (!initialized[12] || !initialized[47]) {
   print_error("Instruction 23: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[47];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 23");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[52] = result;
   initialized[52] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 52, 12, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.637735724f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_1: expected %.8f, got %.8f\n", 0.637735724f, result);
       verification_errors++;
   } else {
       print_success("reg_52_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[47] || !initialized[52]) {
   print_error("Instruction 24: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[52];
 result = src1 * src2;
   registers[13] = result;
   initialized[13] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 13, 47, 52, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.59691775f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_2: expected %.8f, got %.8f\n", 1.59691775f, result);
       verification_errors++;
   } else {
       print_success("reg_13_2 matches: ");       printf("                       %.8f", result);
   }

   registers[25] = 15.562253f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   registers[44] = 0.00520331878f;
   initialized[44] = true;
   printf("INIT: reg[%d] = %.8f\n", 44, registers[44]);

   if (!initialized[25] || !initialized[44]) {
   print_error("Instruction 27: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[44];
 result = src1 * src2;
   registers[20] = result;
   initialized[20] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 20, 25, 44, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0809753612f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_1: expected %.8f, got %.8f\n", 0.0809753612f, result);
       verification_errors++;
   } else {
       print_success("reg_20_1 matches: ");       printf("                       %.8f", result);
   }

   registers[18] = 9.99999975e-05f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   if (!initialized[44] || !initialized[20]) {
   print_error("Instruction 29: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[20];
 result = src1 * src2;
   registers[9] = result;
   initialized[9] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 9, 44, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000421340606f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_1: expected %.8f, got %.8f\n", 0.000421340606f, result);
       verification_errors++;
   } else {
       print_success("reg_9_1 matches: ");       printf("                       %.8f", result);
   }

   registers[49] = -31.9974194f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   registers[47] = -0.124999933f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   if (!initialized[47] || !initialized[49]) {
   print_error("Instruction 32: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[49];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 32");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[0] = result;
   initialized[0] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 0, 47, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00390656292f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_2: expected %.8f, got %.8f\n", 0.00390656292f, result);
       verification_errors++;
   } else {
       print_success("reg_0_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[47]) {
   print_error("Instruction 33: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[47];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 33");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[46] = result;
   initialized[46] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 46, 0, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.031252522f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_2: expected %.8f, got %.8f\n", -0.031252522f, result);
       verification_errors++;
   } else {
       print_success("reg_46_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[46]) {
   print_error("Instruction 34: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[46];
 result = src1 * src2;
   registers[7] = result;
   initialized[7] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 7, 0, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000122089943f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_1: expected %.8f, got %.8f\n", -0.000122089943f, result);
       verification_errors++;
   } else {
       print_success("reg_7_1 matches: ");       printf("                       %.8f", result);
   }

   registers[54] = 0.00586347189f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   registers[7] = 0.501949668f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   registers[49] = 0.756836534f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[49] || !initialized[54]) {
   print_error("Instruction 38: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[54];
 result = src1 - src2;
   registers[15] = result;
   initialized[15] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 15, 49, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.750973046f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_2: expected %.8f, got %.8f\n", 0.750973046f, result);
       verification_errors++;
   } else {
       print_success("reg_15_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[54]) {
   print_error("Instruction 39: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[54];
 result = src1 - src2;
   registers[61] = result;
   initialized[61] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 61, 7, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.49608621f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_1: expected %.8f, got %.8f\n", 0.49608621f, result);
       verification_errors++;
   } else {
       print_success("reg_61_1 matches: ");       printf("                       %.8f", result);
   }

   registers[1] = 23.9987602f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   registers[18] = -0.00123961782f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   if (!initialized[1] || !initialized[18]) {
   print_error("Instruction 42: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[18];
 result = src1 - src2;
   registers[46] = result;
   initialized[46] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 46, 1, 18, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 24.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_3: expected %.8f, got %.8f\n", 24.0f, result);
       verification_errors++;
   } else {
       print_success("reg_46_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[46] || !initialized[1]) {
   print_error("Instruction 43: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[1];
 result = src1 * src2;
   registers[54] = result;
   initialized[54] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 54, 46, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 575.970215f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_54_3: expected %.8f, got %.8f\n", 575.970215f, result);
       verification_errors++;
   } else {
       print_success("reg_54_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[18] || !initialized[46]) {
   print_error("Instruction 44: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[18];
src2 = registers[46];
 result = src1 * src2;
   registers[21] = result;
   initialized[21] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 21, 18, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0297508277f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_2: expected %.8f, got %.8f\n", -0.0297508277f, result);
       verification_errors++;
   } else {
       print_success("reg_21_2 matches: ");       printf("                       %.8f", result);
   }

   registers[22] = 9.99999975e-05f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   registers[12] = -1.59292901f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[59] = -3.51337028f;
   initialized[59] = true;
   printf("INIT: reg[%d] = %.8f\n", 59, registers[59]);

   if (!initialized[12] || !initialized[59]) {
   print_error("Instruction 48: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[59];
 result = src1 - src2;
   registers[58] = result;
   initialized[58] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 58, 12, 59, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.92044127f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_1: expected %.8f, got %.8f\n", 1.92044127f, result);
       verification_errors++;
   } else {
       print_success("reg_58_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[12] || !initialized[58]) {
   print_error("Instruction 49: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[58];
 result = src1 * src2;
   registers[18] = result;
   initialized[18] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 18, 12, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -3.05912662f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_3: expected %.8f, got %.8f\n", -3.05912662f, result);
       verification_errors++;
   } else {
       print_success("reg_18_3 matches: ");       printf("                       %.8f", result);
   }

   registers[62] = -13.9551878f;
   initialized[62] = true;
   printf("INIT: reg[%d] = %.8f\n", 62, registers[62]);

   registers[33] = -515.308411f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[34] = 9.99999975e-05f;
   initialized[34] = true;
   printf("INIT: reg[%d] = %.8f\n", 34, registers[34]);

   registers[60] = 9.99999975e-05f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   if (!initialized[33] || !initialized[62]) {
   print_error("Instruction 54: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[33];
src2 = registers[62];
 result = src1 - src2;
   registers[16] = result;
   initialized[16] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 16, 33, 62, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -501.35321f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_2: expected %.8f, got %.8f\n", -501.35321f, result);
       verification_errors++;
   } else {
       print_success("reg_16_2 matches: ");       printf("                       %.8f", result);
   }

   registers[4] = 0.0139732352f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   registers[37] = 0.0139811775f;
   initialized[37] = true;
   printf("INIT: reg[%d] = %.8f\n", 37, registers[37]);

   if (!initialized[37] || !initialized[4]) {
   print_error("Instruction 57: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[37];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 57");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[17] = result;
   initialized[17] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 17, 37, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.00056839f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_17_2: expected %.8f, got %.8f\n", 1.00056839f, result);
       verification_errors++;
   } else {
       print_success("reg_17_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[4] || !initialized[17]) {
   print_error("Instruction 58: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[17];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 58");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[20] = result;
   initialized[20] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 20, 4, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0139652975f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_2: expected %.8f, got %.8f\n", 0.0139652975f, result);
       verification_errors++;
   } else {
       print_success("reg_20_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[37] || !initialized[20]) {
   print_error("Instruction 59: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[37];
src2 = registers[20];
 result = src1 * src2;
   registers[29] = result;
   initialized[29] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 29, 37, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000195251298f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_29_2: expected %.8f, got %.8f\n", 0.000195251298f, result);
       verification_errors++;
   } else {
       print_success("reg_29_2 matches: ");       printf("                       %.8f", result);
   }

   registers[56] = -1.99996924f;
   initialized[56] = true;
   printf("INIT: reg[%d] = %.8f\n", 56, registers[56]);

   registers[20] = 0.00545174489f;
   initialized[20] = true;
   printf("INIT: reg[%d] = %.8f\n", 20, registers[20]);

   if (!initialized[20] || !initialized[56]) {
   print_error("Instruction 62: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[20];
src2 = registers[56];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 62");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[40] = result;
   initialized[40] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 40, 20, 56, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00272591435f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_1: expected %.8f, got %.8f\n", -0.00272591435f, result);
       verification_errors++;
   } else {
       print_success("reg_40_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[56] || !initialized[20]) {
   print_error("Instruction 63: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[56];
src2 = registers[20];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 63");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[24] = result;
   initialized[24] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 24, 56, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -366.849396f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_1: expected %.8f, got %.8f\n", -366.849396f, result);
       verification_errors++;
   } else {
       print_success("reg_24_1 matches: ");       printf("                       %.8f", result);
   }

   registers[52] = 9.99999975e-05f;
   initialized[52] = true;
   printf("INIT: reg[%d] = %.8f\n", 52, registers[52]);

   registers[17] = 0.00414929492f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   registers[35] = -56.9848824f;
   initialized[35] = true;
   printf("INIT: reg[%d] = %.8f\n", 35, registers[35]);

   if (!initialized[35] || !initialized[17]) {
   print_error("Instruction 67: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[17];
 result = src1 * src2;
   registers[48] = result;
   initialized[48] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 48, 35, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.236447081f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_48_2: expected %.8f, got %.8f\n", -0.236447081f, result);
       verification_errors++;
   } else {
       print_success("reg_48_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[35] || !initialized[17]) {
   print_error("Instruction 68: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[17];
 result = src1 - src2;
   registers[26] = result;
   initialized[26] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 26, 35, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -56.9890327f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_2: expected %.8f, got %.8f\n", -56.9890327f, result);
       verification_errors++;
   } else {
       print_success("reg_26_2 matches: ");       printf("                       %.8f", result);
   }

   registers[42] = 9.99999975e-05f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   registers[47] = -814.72998f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   registers[55] = -1.46460438f;
   initialized[55] = true;
   printf("INIT: reg[%d] = %.8f\n", 55, registers[55]);

   if (!initialized[47] || !initialized[55]) {
   print_error("Instruction 72: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[55];
 result = src1 - src2;
   registers[23] = result;
   initialized[23] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 23, 47, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -813.265381f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_1: expected %.8f, got %.8f\n", -813.265381f, result);
       verification_errors++;
   } else {
       print_success("reg_23_1 matches: ");       printf("                       %.8f", result);
   }

   registers[33] = 9.99999975e-05f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[4] = 9.99999975e-05f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   registers[48] = 0.0825173855f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   registers[49] = 8.07545376f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[49] || !initialized[48]) {
   print_error("Instruction 77: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[48];
 result = src1 - src2;
   registers[21] = result;
   initialized[21] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 21, 49, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 7.99293613f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_3: expected %.8f, got %.8f\n", 7.99293613f, result);
       verification_errors++;
   } else {
       print_success("reg_21_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[48] || !initialized[21]) {
   print_error("Instruction 78: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[21];
 result = src1 * src2;
   registers[14] = result;
   initialized[14] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 14, 48, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.65955621f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_2: expected %.8f, got %.8f\n", 0.65955621f, result);
       verification_errors++;
   } else {
       print_success("reg_14_2 matches: ");       printf("                       %.8f", result);
   }

   registers[18] = 9.99999975e-05f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   registers[5] = 0.000496618974f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[0] = 0.000701926474f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   if (!initialized[0] || !initialized[5]) {
   print_error("Instruction 82: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[5];
 result = src1 - src2;
   registers[31] = result;
   initialized[31] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 31, 0, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0002053075f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_1: expected %.8f, got %.8f\n", 0.0002053075f, result);
       verification_errors++;
   } else {
       print_success("reg_31_1 matches: ");       printf("                       %.8f", result);
   }

   registers[40] = 9.99999975e-05f;
   initialized[40] = true;
   printf("INIT: reg[%d] = %.8f\n", 40, registers[40]);

   if (!initialized[5] || !initialized[0]) {
   print_error("Instruction 84: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[0];
 result = src1 - src2;
   registers[9] = result;
   initialized[9] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 9, 5, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0002053075f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_2: expected %.8f, got %.8f\n", -0.0002053075f, result);
       verification_errors++;
   } else {
       print_success("reg_9_2 matches: ");       printf("                       %.8f", result);
   }

   registers[62] = -1.68739378f;
   initialized[62] = true;
   printf("INIT: reg[%d] = %.8f\n", 62, registers[62]);

   registers[53] = 0.351206601f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   if (!initialized[53] || !initialized[62]) {
   print_error("Instruction 87: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[62];
 result = src1 * src2;
   registers[58] = result;
   initialized[58] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 58, 53, 62, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.59262383f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_2: expected %.8f, got %.8f\n", -0.59262383f, result);
       verification_errors++;
   } else {
       print_success("reg_58_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[58] || !initialized[62]) {
   print_error("Instruction 88: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[62];
 result = src1 * src2;
   registers[12] = result;
   initialized[12] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 12, 58, 62, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.999989748f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_12_3: expected %.8f, got %.8f\n", 0.999989748f, result);
       verification_errors++;
   } else {
       print_success("reg_12_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[58] || !initialized[12]) {
   print_error("Instruction 89: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[12];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 89");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[25] = result;
   initialized[25] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 25, 58, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.59262991f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_2: expected %.8f, got %.8f\n", -0.59262991f, result);
       verification_errors++;
   } else {
       print_success("reg_25_2 matches: ");       printf("                       %.8f", result);
   }

   registers[17] = 0.153591439f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   registers[25] = 0.0155006982f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   if (!initialized[25] || !initialized[17]) {
   print_error("Instruction 92: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[17];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 92");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[35] = result;
   initialized[35] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 35, 25, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.100921631f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_2: expected %.8f, got %.8f\n", 0.100921631f, result);
       verification_errors++;
   } else {
       print_success("reg_35_2 matches: ");       printf("                       %.8f", result);
   }

   registers[21] = 0.000350529153f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   if (!initialized[35] || !initialized[21]) {
   print_error("Instruction 94: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[21];
 result = src1 - src2;
   registers[57] = result;
   initialized[57] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 57, 35, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.100571103f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_57_1: expected %.8f, got %.8f\n", 0.100571103f, result);
       verification_errors++;
   } else {
       print_success("reg_57_1 matches: ");       printf("                       %.8f", result);
   }

   registers[46] = -3.95699525f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   registers[54] = -3.45693564f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   if (!initialized[46] || !initialized[54]) {
   print_error("Instruction 97: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[54];
 result = src1 - src2;
   registers[61] = result;
   initialized[61] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 61, 46, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.500059605f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_2: expected %.8f, got %.8f\n", -0.500059605f, result);
       verification_errors++;
   } else {
       print_success("reg_61_2 matches: ");       printf("                       %.8f", result);
   }

   registers[26] = 9.99999975e-05f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[46] || !initialized[61]) {
   print_error("Instruction 99: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[61];
 result = src1 * src2;
   registers[55] = result;
   initialized[55] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 55, 46, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.97873342f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_2: expected %.8f, got %.8f\n", 1.97873342f, result);
       verification_errors++;
   } else {
       print_success("reg_55_2 matches: ");       printf("                       %.8f", result);
   }

   registers[25] = -0.000213846564f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   registers[50] = -73.066864f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   if (!initialized[50] || !initialized[25]) {
   print_error("Instruction 102: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[50];
src2 = registers[25];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 50, 25, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0156250987f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_2: expected %.8f, got %.8f\n", 0.0156250987f, result);
       verification_errors++;
   } else {
       print_success("reg_1_2 matches: ");       printf("                       %.8f", result);
   }

   registers[28] = 253.146606f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   if (!initialized[28] || !initialized[50]) {
   print_error("Instruction 104: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[50];
 result = src1 - src2;
   registers[19] = result;
   initialized[19] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 19, 28, 50, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 326.21347f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_19_1: expected %.8f, got %.8f\n", 326.21347f, result);
       verification_errors++;
   } else {
       print_success("reg_19_1 matches: ");       printf("                       %.8f", result);
   }

   registers[61] = -0.00365023944f;
   initialized[61] = true;
   printf("INIT: reg[%d] = %.8f\n", 61, registers[61]);

   registers[22] = -0.0579723194f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[61] || !initialized[22]) {
   print_error("Instruction 107: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[61];
src2 = registers[22];
 result = src1 * src2;
   registers[46] = result;
   initialized[46] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 46, 61, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000211612845f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_5: expected %.8f, got %.8f\n", 0.000211612845f, result);
       verification_errors++;
   } else {
       print_success("reg_46_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[22] || !initialized[61]) {
   print_error("Instruction 108: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[22];
src2 = registers[61];
 result = src1 - src2;
   registers[57] = result;
   initialized[57] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 57, 22, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0543220788f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_57_2: expected %.8f, got %.8f\n", -0.0543220788f, result);
       verification_errors++;
   } else {
       print_success("reg_57_2 matches: ");       printf("                       %.8f", result);
   }

   registers[45] = 9.99999975e-05f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[50] = -0.14130117f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[15] = -0.0163011719f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[50] || !initialized[15]) {
   print_error("Instruction 112: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[50];
src2 = registers[15];
 result = src1 - src2;
   registers[49] = result;
   initialized[49] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 49, 50, 15, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.125f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_49_5: expected %.8f, got %.8f\n", -0.125f, result);
       verification_errors++;
   } else {
       print_success("reg_49_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[15] || !initialized[49]) {
   print_error("Instruction 113: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[15];
src2 = registers[49];
 result = src1 - src2;
   registers[36] = result;
   initialized[36] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 36, 15, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.10869883f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_36_1: expected %.8f, got %.8f\n", 0.10869883f, result);
       verification_errors++;
   } else {
       print_success("reg_36_1 matches: ");       printf("                       %.8f", result);
   }

   registers[26] = 9.99999975e-05f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   registers[36] = -14.4803019f;
   initialized[36] = true;
   printf("INIT: reg[%d] = %.8f\n", 36, registers[36]);

   registers[49] = 7.24015093f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[49] || !initialized[36]) {
   print_error("Instruction 117: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[36];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 117");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[57] = result;
   initialized[57] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 57, 49, 36, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.5f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_57_3: expected %.8f, got %.8f\n", -0.5f, result);
       verification_errors++;
   } else {
       print_success("reg_57_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[36] || !initialized[49]) {
   print_error("Instruction 118: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[36];
src2 = registers[49];
 result = src1 - src2;
   registers[29] = result;
   initialized[29] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 29, 36, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -21.7204533f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_29_3: expected %.8f, got %.8f\n", -21.7204533f, result);
       verification_errors++;
   } else {
       print_success("reg_29_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[49] || !initialized[57]) {
   print_error("Instruction 119: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[57];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 119");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[7] = result;
   initialized[7] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 7, 49, 57, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -14.4803019f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_3: expected %.8f, got %.8f\n", -14.4803019f, result);
       verification_errors++;
   } else {
       print_success("reg_7_3 matches: ");       printf("                       %.8f", result);
   }

   registers[11] = -0.83856672f;
   initialized[11] = true;
   printf("INIT: reg[%d] = %.8f\n", 11, registers[11]);

   registers[42] = -881.689636f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   if (!initialized[11] || !initialized[42]) {
   print_error("Instruction 122: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[11];
src2 = registers[42];
 result = src1 * src2;
   registers[56] = result;
   initialized[56] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 56, 11, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 739.355591f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_56_2: expected %.8f, got %.8f\n", 739.355591f, result);
       verification_errors++;
   } else {
       print_success("reg_56_2 matches: ");       printf("                       %.8f", result);
   }

   registers[10] = -0.000253742794f;
   initialized[10] = true;
   printf("INIT: reg[%d] = %.8f\n", 10, registers[10]);

   if (!initialized[56] || !initialized[10]) {
   print_error("Instruction 124: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[56];
src2 = registers[10];
 result = src1 * src2;
   registers[46] = result;
   initialized[46] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 46, 56, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.187606156f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_6: expected %.8f, got %.8f\n", -0.187606156f, result);
       verification_errors++;
   } else {
       print_success("reg_46_6 matches: ");       printf("                       %.8f", result);
   }

   registers[6] = 127.578484f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[43] = -1.97119224f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   if (!initialized[43] || !initialized[6]) {
   print_error("Instruction 127: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[43];
src2 = registers[6];
 result = src1 * src2;
   registers[37] = result;
   initialized[37] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 37, 43, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -251.48172f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_2: expected %.8f, got %.8f\n", -251.48172f, result);
       verification_errors++;
   } else {
       print_success("reg_37_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[37] || !initialized[6]) {
   print_error("Instruction 128: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[37];
src2 = registers[6];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 128");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[16] = result;
   initialized[16] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 16, 37, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.97119224f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_16_3: expected %.8f, got %.8f\n", -1.97119224f, result);
       verification_errors++;
   } else {
       print_success("reg_16_3 matches: ");       printf("                       %.8f", result);
   }

   registers[55] = 9.99999975e-05f;
   initialized[55] = true;
   printf("INIT: reg[%d] = %.8f\n", 55, registers[55]);

   registers[27] = -6.09399366f;
   initialized[27] = true;
   printf("INIT: reg[%d] = %.8f\n", 27, registers[27]);

   registers[53] = -0.000762950804f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[1] = -0.430971891f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   if (!initialized[53] || !initialized[27]) {
   print_error("Instruction 133: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[27];
 result = src1 * src2;
   registers[41] = result;
   initialized[41] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 41, 53, 27, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00464941747f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_1: expected %.8f, got %.8f\n", 0.00464941747f, result);
       verification_errors++;
   } else {
       print_success("reg_41_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[53]) {
   print_error("Instruction 134: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[53];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 134");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[15] = result;
   initialized[15] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 15, 1, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 564.875061f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_4: expected %.8f, got %.8f\n", 564.875061f, result);
       verification_errors++;
   } else {
       print_success("reg_15_4 matches: ");       printf("                       %.8f", result);
   }

   registers[33] = -0.00352751301f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[32] = -0.00705495756f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   if (!initialized[32] || !initialized[33]) {
   print_error("Instruction 137: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[33];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 137");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[0] = result;
   initialized[0] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 0, 32, 33, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.99998057f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_0_4: expected %.8f, got %.8f\n", 1.99998057f, result);
       verification_errors++;
   } else {
       print_success("reg_0_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[32]) {
   print_error("Instruction 138: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[32];
 result = src1 * src2;
   registers[18] = result;
   initialized[18] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 18, 0, 32, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0141097782f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_5: expected %.8f, got %.8f\n", -0.0141097782f, result);
       verification_errors++;
   } else {
       print_success("reg_18_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[32] || !initialized[0]) {
   print_error("Instruction 139: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[0];
 result = src1 - src2;
   registers[51] = result;
   initialized[51] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 51, 32, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.00703549f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_51_1: expected %.8f, got %.8f\n", -2.00703549f, result);
       verification_errors++;
   } else {
       print_success("reg_51_1 matches: ");       printf("                       %.8f", result);
   }

   registers[32] = -128.000641f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   registers[22] = -0.000894427125f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[32] || !initialized[22]) {
   print_error("Instruction 142: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[22];
 result = src1 - src2;
   registers[31] = result;
   initialized[31] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 31, 32, 22, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -127.999748f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_2: expected %.8f, got %.8f\n", -127.999748f, result);
       verification_errors++;
   } else {
       print_success("reg_31_2 matches: ");       printf("                       %.8f", result);
   }

   registers[26] = -1.67907715f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[22] || !initialized[26]) {
   print_error("Instruction 144: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[22];
src2 = registers[26];
 result = src1 * src2;
   registers[6] = result;
   initialized[6] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 6, 22, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00150181213f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_4: expected %.8f, got %.8f\n", 0.00150181213f, result);
       verification_errors++;
   } else {
       print_success("reg_6_4 matches: ");       printf("                       %.8f", result);
   }

   registers[12] = -1.23268855f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[28] = -0.671073318f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   if (!initialized[12] || !initialized[28]) {
   print_error("Instruction 147: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[28];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 147");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[40] = result;
   initialized[40] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 40, 12, 28, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.83689106f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_3: expected %.8f, got %.8f\n", 1.83689106f, result);
       verification_errors++;
   } else {
       print_success("reg_40_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[12] || !initialized[40]) {
   print_error("Instruction 148: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[12];
src2 = registers[40];
 result = src1 - src2;
   registers[62] = result;
   initialized[62] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 62, 12, 40, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -3.0695796f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_62_3: expected %.8f, got %.8f\n", -3.0695796f, result);
       verification_errors++;
   } else {
       print_success("reg_62_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[28] || !initialized[12]) {
   print_error("Instruction 149: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[12];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 149");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[13] = result;
   initialized[13] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 13, 28, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.544398129f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_3: expected %.8f, got %.8f\n", 0.544398129f, result);
       verification_errors++;
   } else {
       print_success("reg_13_3 matches: ");       printf("                       %.8f", result);
   }

   registers[47] = -3.88179469f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   registers[8] = -3.26777935f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   if (!initialized[47] || !initialized[8]) {
   print_error("Instruction 152: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[8];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 152");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[46] = result;
   initialized[46] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 46, 47, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.18789983f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_7: expected %.8f, got %.8f\n", 1.18789983f, result);
       verification_errors++;
   } else {
       print_success("reg_46_7 matches: ");       printf("                       %.8f", result);
   }

   registers[48] = 9.99999975e-05f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   registers[57] = 9.99999975e-05f;
   initialized[57] = true;
   printf("INIT: reg[%d] = %.8f\n", 57, registers[57]);

   registers[21] = -0.000120172583f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   registers[61] = -0.0615234338f;
   initialized[61] = true;
   printf("INIT: reg[%d] = %.8f\n", 61, registers[61]);

   if (!initialized[21] || !initialized[61]) {
   print_error("Instruction 157: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[61];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 157");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[33] = result;
   initialized[33] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 33, 21, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00195328146f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_33_4: expected %.8f, got %.8f\n", 0.00195328146f, result);
       verification_errors++;
   } else {
       print_success("reg_33_4 matches: ");       printf("                       %.8f", result);
   }

   registers[12] = 9.99999975e-05f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[56] = 9.99999975e-05f;
   initialized[56] = true;
   printf("INIT: reg[%d] = %.8f\n", 56, registers[56]);

   registers[45] = 0.000781860144f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[28] = 0.00666299602f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   if (!initialized[28] || !initialized[45]) {
   print_error("Instruction 162: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[45];
 result = src1 - src2;
   registers[10] = result;
   initialized[10] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 10, 28, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00588113582f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_2: expected %.8f, got %.8f\n", 0.00588113582f, result);
       verification_errors++;
   } else {
       print_success("reg_10_2 matches: ");       printf("                       %.8f", result);
   }

   registers[15] = 9.99999975e-05f;
   initialized[15] = true;
   printf("INIT: reg[%d] = %.8f\n", 15, registers[15]);

   if (!initialized[45] || !initialized[28]) {
   print_error("Instruction 164: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[45];
src2 = registers[28];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 164");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 45, 28, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.117343634f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_4: expected %.8f, got %.8f\n", 0.117343634f, result);
       verification_errors++;
   } else {
       print_success("reg_55_4 matches: ");       printf("                       %.8f", result);
   }

   registers[21] = 1.32560253f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   registers[39] = 0.498499662f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   if (!initialized[39] || !initialized[21]) {
   print_error("Instruction 167: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[39];
src2 = registers[21];
 result = src1 * src2;
   registers[17] = result;
   initialized[17] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 17, 39, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.660812438f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_17_5: expected %.8f, got %.8f\n", 0.660812438f, result);
       verification_errors++;
   } else {
       print_success("reg_17_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[39] || !initialized[21]) {
   print_error("Instruction 168: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[39];
src2 = registers[21];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 168");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[61] = result;
   initialized[61] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 61, 39, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.376055151f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_5: expected %.8f, got %.8f\n", 0.376055151f, result);
       verification_errors++;
   } else {
       print_success("reg_61_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[21] || !initialized[17]) {
   print_error("Instruction 169: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[17];
 result = src1 * src2;
   registers[51] = result;
   initialized[51] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 51, 21, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.875974655f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_51_2: expected %.8f, got %.8f\n", 0.875974655f, result);
       verification_errors++;
   } else {
       print_success("reg_51_2 matches: ");       printf("                       %.8f", result);
   }

   registers[33] = 0.0482257344f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[3] = 0.00135073625f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   if (!initialized[33] || !initialized[3]) {
   print_error("Instruction 172: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[33];
src2 = registers[3];
 result = src1 - src2;
   registers[2] = result;
   initialized[2] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 2, 33, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.046875f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_1: expected %.8f, got %.8f\n", 0.046875f, result);
       verification_errors++;
   } else {
       print_success("reg_2_1 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[2] || !initialized[3]) {
   print_error("Instruction 173: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[2];
src2 = registers[3];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 173");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[8] = result;
   initialized[8] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 8, 2, 3, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 34.7032967f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_3: expected %.8f, got %.8f\n", 34.7032967f, result);
       verification_errors++;
   } else {
       print_success("reg_8_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[3] || !initialized[2]) {
   print_error("Instruction 174: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[2];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 174");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[46] = result;
   initialized[46] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 46, 3, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0288157072f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_8: expected %.8f, got %.8f\n", 0.0288157072f, result);
       verification_errors++;
   } else {
       print_success("reg_46_8 matches: ");       printf("                       %.8f", result);
   }

   registers[52] = -0.109604299f;
   initialized[52] = true;
   printf("INIT: reg[%d] = %.8f\n", 52, registers[52]);

   registers[0] = 0.0153956991f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   if (!initialized[0] || !initialized[52]) {
   print_error("Instruction 177: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[52];
 result = src1 - src2;
   registers[23] = result;
   initialized[23] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 23, 0, 52, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.125f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_2: expected %.8f, got %.8f\n", 0.125f, result);
       verification_errors++;
   } else {
       print_success("reg_23_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[52]) {
   print_error("Instruction 178: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[52];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 23, 52, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0137005374f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_3: expected %.8f, got %.8f\n", -0.0137005374f, result);
       verification_errors++;
   } else {
       print_success("reg_3_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[23]) {
   print_error("Instruction 179: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[23];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 179");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[36] = result;
   initialized[36] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 36, 0, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.123165593f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_36_3: expected %.8f, got %.8f\n", 0.123165593f, result);
       verification_errors++;
   } else {
       print_success("reg_36_3 matches: ");       printf("                       %.8f", result);
   }

   registers[63] = -0.0622262917f;
   initialized[63] = true;
   printf("INIT: reg[%d] = %.8f\n", 63, registers[63]);

   registers[53] = -94.3125229f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[13] = 9.99999975e-05f;
   initialized[13] = true;
   printf("INIT: reg[%d] = %.8f\n", 13, registers[13]);

   if (!initialized[63] || !initialized[53]) {
   print_error("Instruction 183: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[63];
src2 = registers[53];
 result = src1 * src2;
   registers[28] = result;
   initialized[28] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 28, 63, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 5.86871862f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_28_4: expected %.8f, got %.8f\n", 5.86871862f, result);
       verification_errors++;
   } else {
       print_success("reg_28_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[28] || !initialized[53]) {
   print_error("Instruction 184: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[53];
 result = src1 * src2;
   registers[60] = result;
   initialized[60] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 60, 28, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -553.493652f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_60_3: expected %.8f, got %.8f\n", -553.493652f, result);
       verification_errors++;
   } else {
       print_success("reg_60_3 matches: ");       printf("                       %.8f", result);
   }

   registers[13] = 0.0040244339f;
   initialized[13] = true;
   printf("INIT: reg[%d] = %.8f\n", 13, registers[13]);

   registers[28] = 0.0060300827f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   if (!initialized[28] || !initialized[13]) {
   print_error("Instruction 187: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[28];
src2 = registers[13];
 result = src1 - src2;
   registers[35] = result;
   initialized[35] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 35, 28, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0020056488f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_3: expected %.8f, got %.8f\n", 0.0020056488f, result);
       verification_errors++;
   } else {
       print_success("reg_35_3 matches: ");       printf("                       %.8f", result);
   }

   registers[63] = 1.94130874f;
   initialized[63] = true;
   printf("INIT: reg[%d] = %.8f\n", 63, registers[63]);

   if (!initialized[63] || !initialized[13]) {
   print_error("Instruction 189: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[63];
src2 = registers[13];
 result = src1 * src2;
   registers[45] = result;
   initialized[45] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 45, 63, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00781266857f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_45_3: expected %.8f, got %.8f\n", 0.00781266857f, result);
       verification_errors++;
   } else {
       print_success("reg_45_3 matches: ");       printf("                       %.8f", result);
   }

   registers[41] = -764.015503f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   registers[47] = 0.109339193f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   if (!initialized[47] || !initialized[41]) {
   print_error("Instruction 192: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[41];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 192");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[44] = result;
   initialized[44] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 44, 47, 41, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000143111218f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_44_3: expected %.8f, got %.8f\n", -0.000143111218f, result);
       verification_errors++;
   } else {
       print_success("reg_44_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[41] || !initialized[47]) {
   print_error("Instruction 193: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[41];
src2 = registers[47];
 result = src1 - src2;
   registers[37] = result;
   initialized[37] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 37, 41, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -764.124817f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_3: expected %.8f, got %.8f\n", -764.124817f, result);
       verification_errors++;
   } else {
       print_success("reg_37_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[44] || !initialized[47]) {
   print_error("Instruction 194: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[47];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 44, 47, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.109482303f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_2: expected %.8f, got %.8f\n", -0.109482303f, result);
       verification_errors++;
   } else {
       print_success("reg_27_2 matches: ");       printf("                       %.8f", result);
   }

   registers[35] = 0.00195312267f;
   initialized[35] = true;
   printf("INIT: reg[%d] = %.8f\n", 35, registers[35]);

   registers[10] = -0.000122070152f;
   initialized[10] = true;
   printf("INIT: reg[%d] = %.8f\n", 10, registers[10]);

   if (!initialized[35] || !initialized[10]) {
   print_error("Instruction 197: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[10];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 197");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[5] = result;
   initialized[5] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 5, 35, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -16.0000019f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_2: expected %.8f, got %.8f\n", -16.0000019f, result);
       verification_errors++;
   } else {
       print_success("reg_5_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[10] || !initialized[5]) {
   print_error("Instruction 198: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[10];
src2 = registers[5];
 result = src1 * src2;
   registers[7] = result;
   initialized[7] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 7, 10, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00195312267f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_4: expected %.8f, got %.8f\n", 0.00195312267f, result);
       verification_errors++;
   } else {
       print_success("reg_7_4 matches: ");       printf("                       %.8f", result);
   }

   registers[26] = 9.99999975e-05f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   registers[60] = 0.0714363679f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   registers[40] = 0.0114131905f;
   initialized[40] = true;
   printf("INIT: reg[%d] = %.8f\n", 40, registers[40]);

   if (!initialized[60] || !initialized[40]) {
   print_error("Instruction 202: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[60];
src2 = registers[40];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 202");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[58] = result;
   initialized[58] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 58, 60, 40, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 6.25910568f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_3: expected %.8f, got %.8f\n", 6.25910568f, result);
       verification_errors++;
   } else {
       print_success("reg_58_3 matches: ");       printf("                       %.8f", result);
   }

   registers[7] = 14.374382f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[40] || !initialized[7]) {
   print_error("Instruction 204: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[7];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 204");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[25] = result;
   initialized[25] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 25, 40, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000793995219f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_5: expected %.8f, got %.8f\n", 0.000793995219f, result);
       verification_errors++;
   } else {
       print_success("reg_25_5 matches: ");       printf("                       %.8f", result);
   }

   registers[17] = -0.0728802085f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   registers[59] = -0.108091205f;
   initialized[59] = true;
   printf("INIT: reg[%d] = %.8f\n", 59, registers[59]);

   if (!initialized[59] || !initialized[17]) {
   print_error("Instruction 207: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[59];
src2 = registers[17];
 result = src1 - src2;
   registers[4] = result;
   initialized[4] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 4, 59, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0352109969f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_3: expected %.8f, got %.8f\n", -0.0352109969f, result);
       verification_errors++;
   } else {
       print_success("reg_4_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[4] || !initialized[17]) {
   print_error("Instruction 208: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[17];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 208");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[47] = result;
   initialized[47] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 47, 4, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.483135223f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_6: expected %.8f, got %.8f\n", 0.483135223f, result);
       verification_errors++;
   } else {
       print_success("reg_47_6 matches: ");       printf("                       %.8f", result);
   }

   registers[10] = 9.99999975e-05f;
   initialized[10] = true;
   printf("INIT: reg[%d] = %.8f\n", 10, registers[10]);

   registers[50] = 0.0311617143f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[9] = -0.000118968077f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[9] || !initialized[50]) {
   print_error("Instruction 212: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[50];
 result = src1 - src2;
   registers[40] = result;
   initialized[40] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 40, 9, 50, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0312806815f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_5: expected %.8f, got %.8f\n", -0.0312806815f, result);
       verification_errors++;
   } else {
       print_success("reg_40_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[40] || !initialized[9]) {
   print_error("Instruction 213: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[9];
 result = src1 - src2;
   registers[24] = result;
   initialized[24] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 24, 40, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0311617143f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_2: expected %.8f, got %.8f\n", -0.0311617143f, result);
       verification_errors++;
   } else {
       print_success("reg_24_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[40] || !initialized[24]) {
   print_error("Instruction 214: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[24];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 214");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[63] = result;
   initialized[63] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 63, 40, 24, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.00381768f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_63_3: expected %.8f, got %.8f\n", 1.00381768f, result);
       verification_errors++;
   } else {
       print_success("reg_63_3 matches: ");       printf("                       %.8f", result);
   }

   registers[45] = -125.953117f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[30] = -1.97586274f;
   initialized[30] = true;
   printf("INIT: reg[%d] = %.8f\n", 30, registers[30]);

   registers[28] = 9.99999975e-05f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   if (!initialized[30] || !initialized[45]) {
   print_error("Instruction 218: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[30];
src2 = registers[45];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 218");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[6] = result;
   initialized[6] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 6, 30, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0156872869f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_6_5: expected %.8f, got %.8f\n", 0.0156872869f, result);
       verification_errors++;
   } else {
       print_success("reg_6_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[6] || !initialized[45]) {
   print_error("Instruction 219: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[6];
src2 = registers[45];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 6, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.97586274f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_4: expected %.8f, got %.8f\n", -1.97586274f, result);
       verification_errors++;
   } else {
       print_success("reg_1_4 matches: ");       printf("                       %.8f", result);
   }

   registers[55] = 0.00694414834f;
   initialized[55] = true;
   printf("INIT: reg[%d] = %.8f\n", 55, registers[55]);

   registers[63] = 0.00780858332f;
   initialized[63] = true;
   printf("INIT: reg[%d] = %.8f\n", 63, registers[63]);

   if (!initialized[63] || !initialized[55]) {
   print_error("Instruction 222: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[63];
src2 = registers[55];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 222");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[48] = result;
   initialized[48] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 48, 63, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.12448394f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_48_5: expected %.8f, got %.8f\n", 1.12448394f, result);
       verification_errors++;
   } else {
       print_success("reg_48_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[63] || !initialized[48]) {
   print_error("Instruction 223: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[63];
src2 = registers[48];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 223");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[58] = result;
   initialized[58] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 58, 63, 48, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00694414834f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_4: expected %.8f, got %.8f\n", 0.00694414834f, result);
       verification_errors++;
   } else {
       print_success("reg_58_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[48] || !initialized[63]) {
   print_error("Instruction 224: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[63];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 224");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[19] = result;
   initialized[19] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 19, 48, 63, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 144.006134f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_19_2: expected %.8f, got %.8f\n", 144.006134f, result);
       verification_errors++;
   } else {
       print_success("reg_19_2 matches: ");       printf("                       %.8f", result);
   }

   registers[3] = -432.793793f;
   initialized[3] = true;
   printf("INIT: reg[%d] = %.8f\n", 3, registers[3]);

   registers[11] = -1.12397051f;
   initialized[11] = true;
   printf("INIT: reg[%d] = %.8f\n", 11, registers[11]);

   if (!initialized[3] || !initialized[11]) {
   print_error("Instruction 227: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[3];
src2 = registers[11];
 result = src1 - src2;
   registers[55] = result;
   initialized[55] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 55, 3, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -431.66983f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_6: expected %.8f, got %.8f\n", -431.66983f, result);
       verification_errors++;
   } else {
       print_success("reg_55_6 matches: ");       printf("                       %.8f", result);
   }

   registers[31] = -293.275024f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   if (!initialized[31] || !initialized[55]) {
   print_error("Instruction 229: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[55];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 229");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[32] = result;
   initialized[32] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 32, 31, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.679396629f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_32_4: expected %.8f, got %.8f\n", 0.679396629f, result);
       verification_errors++;
   } else {
       print_success("reg_32_4 matches: ");       printf("                       %.8f", result);
   }

   registers[2] = 578.317505f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   registers[0] = 0.0458296388f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   if (!initialized[0] || !initialized[2]) {
   print_error("Instruction 232: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[2];
 result = src1 * src2;
   registers[30] = result;
   initialized[30] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 30, 0, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 26.5040817f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_30_2: expected %.8f, got %.8f\n", 26.5040817f, result);
       verification_errors++;
   } else {
       print_success("reg_30_2 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[0] || !initialized[2]) {
   print_error("Instruction 233: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[2];
 result = src1 * src2;
   registers[31] = result;
   initialized[31] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 31, 0, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 26.5040817f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_31_4: expected %.8f, got %.8f\n", 26.5040817f, result);
       verification_errors++;
   } else {
       print_success("reg_31_4 matches: ");       printf("                       %.8f", result);
   }

   registers[19] = 9.99999975e-05f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   registers[35] = 3.48915362f;
   initialized[35] = true;
   printf("INIT: reg[%d] = %.8f\n", 35, registers[35]);

   registers[58] = 127.874687f;
   initialized[58] = true;
   printf("INIT: reg[%d] = %.8f\n", 58, registers[58]);

   if (!initialized[35] || !initialized[58]) {
   print_error("Instruction 237: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[58];
 result = src1 * src2;
   registers[17] = result;
   initialized[17] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 17, 35, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 446.174438f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_17_7: expected %.8f, got %.8f\n", 446.174438f, result);
       verification_errors++;
   } else {
       print_success("reg_17_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[58] || !initialized[17]) {
   print_error("Instruction 238: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[17];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 238");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[59] = result;
   initialized[59] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 59, 58, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.286602437f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_59_3: expected %.8f, got %.8f\n", 0.286602437f, result);
       verification_errors++;
   } else {
       print_success("reg_59_3 matches: ");       printf("                       %.8f", result);
   }

   registers[14] = 9.99999975e-05f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   registers[29] = -0.000120185687f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[61] = -4.50392294f;
   initialized[61] = true;
   printf("INIT: reg[%d] = %.8f\n", 61, registers[61]);

   if (!initialized[29] || !initialized[61]) {
   print_error("Instruction 242: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[61];
 result = src1 * src2;
   registers[14] = result;
   initialized[14] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 14, 29, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00054130709f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_4: expected %.8f, got %.8f\n", 0.00054130709f, result);
       verification_errors++;
   } else {
       print_success("reg_14_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[61] || !initialized[14]) {
   print_error("Instruction 243: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[61];
src2 = registers[14];
 result = src1 - src2;
   registers[42] = result;
   initialized[42] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 42, 61, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -4.50446415f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_42_3: expected %.8f, got %.8f\n", -4.50446415f, result);
       verification_errors++;
   } else {
       print_success("reg_42_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[29] || !initialized[14]) {
   print_error("Instruction 244: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[14];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 244");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[5] = result;
   initialized[5] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 5, 29, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.222028658f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_3: expected %.8f, got %.8f\n", -0.222028658f, result);
       verification_errors++;
   } else {
       print_success("reg_5_3 matches: ");       printf("                       %.8f", result);
   }

   registers[53] = -8.0f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[43] = -20.8914509f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   if (!initialized[53] || !initialized[43]) {
   print_error("Instruction 247: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[43];
 result = src1 - src2;
   registers[9] = result;
   initialized[9] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 9, 53, 43, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 12.8914509f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_4: expected %.8f, got %.8f\n", 12.8914509f, result);
       verification_errors++;
   } else {
       print_success("reg_9_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[9] || !initialized[53]) {
   print_error("Instruction 248: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[53];
 result = src1 * src2;
   registers[41] = result;
   initialized[41] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 41, 9, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -103.131607f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_3: expected %.8f, got %.8f\n", -103.131607f, result);
       verification_errors++;
   } else {
       print_success("reg_41_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[9] || !initialized[53]) {
   print_error("Instruction 249: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[53];
 result = src1 * src2;
   registers[10] = result;
   initialized[10] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 10, 9, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -103.131607f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_5: expected %.8f, got %.8f\n", -103.131607f, result);
       verification_errors++;
   } else {
       print_success("reg_10_5 matches: ");       printf("                       %.8f", result);
   }

   registers[0] = 0.000953547831f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   registers[19] = 11.3373241f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   if (!initialized[0] || !initialized[19]) {
   print_error("Instruction 252: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[19];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 0, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0108106807f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_4: expected %.8f, got %.8f\n", 0.0108106807f, result);
       verification_errors++;
   } else {
       print_success("reg_4_4 matches: ");       printf("                       %.8f", result);
   }

   registers[23] = 7.00947475f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   if (!initialized[0] || !initialized[23]) {
   print_error("Instruction 254: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[0];
src2 = registers[23];
 result = src1 * src2;
   registers[1] = result;
   initialized[1] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 1, 0, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00668386929f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_5: expected %.8f, got %.8f\n", 0.00668386929f, result);
       verification_errors++;
   } else {
       print_success("reg_1_5 matches: ");       printf("                       %.8f", result);
   }

   registers[20] = -0.749953449f;
   initialized[20] = true;
   printf("INIT: reg[%d] = %.8f\n", 20, registers[20]);

   registers[42] = -0.701676548f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   if (!initialized[42] || !initialized[20]) {
   print_error("Instruction 257: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[20];
 result = src1 * src2;
   registers[35] = result;
   initialized[35] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 35, 42, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.526224732f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_6: expected %.8f, got %.8f\n", 0.526224732f, result);
       verification_errors++;
   } else {
       print_success("reg_35_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[20]) {
   print_error("Instruction 258: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[20];
 result = src1 * src2;
   registers[24] = result;
   initialized[24] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 24, 42, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.526224732f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_3: expected %.8f, got %.8f\n", 0.526224732f, result);
       verification_errors++;
   } else {
       print_success("reg_24_3 matches: ");       printf("                       %.8f", result);
   }

   registers[29] = 9.99999975e-05f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[6] = -7.65673971f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[51] = 62.4801979f;
   initialized[51] = true;
   printf("INIT: reg[%d] = %.8f\n", 51, registers[51]);

   if (!initialized[51] || !initialized[6]) {
   print_error("Instruction 262: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[51];
src2 = registers[6];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 262");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[29] = result;
   initialized[29] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 29, 51, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -8.1601572f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_29_6: expected %.8f, got %.8f\n", -8.1601572f, result);
       verification_errors++;
   } else {
       print_success("reg_29_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[29] || !initialized[6]) {
   print_error("Instruction 263: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[6];
 result = src1 - src2;
   registers[50] = result;
   initialized[50] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 50, 29, 6, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.503417492f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_50_4: expected %.8f, got %.8f\n", -0.503417492f, result);
       verification_errors++;
   } else {
       print_success("reg_50_4 matches: ");       printf("                       %.8f", result);
   }

   registers[41] = 9.99999975e-05f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   registers[53] = -0.000100195386f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[38] = -0.00389094325f;
   initialized[38] = true;
   printf("INIT: reg[%d] = %.8f\n", 38, registers[38]);

   if (!initialized[38] || !initialized[53]) {
   print_error("Instruction 267: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[38];
src2 = registers[53];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 267");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[44] = result;
   initialized[44] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 44, 38, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 38.8335571f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_44_4: expected %.8f, got %.8f\n", 38.8335571f, result);
       verification_errors++;
   } else {
       print_success("reg_44_4 matches: ");       printf("                       %.8f", result);
   }

   registers[50] = 9.99999975e-05f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[20] = 9.99999975e-05f;
   initialized[20] = true;
   printf("INIT: reg[%d] = %.8f\n", 20, registers[20]);

   registers[51] = 9.99999975e-05f;
   initialized[51] = true;
   printf("INIT: reg[%d] = %.8f\n", 51, registers[51]);

   registers[60] = 9.99999975e-05f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   registers[43] = 9.99999975e-05f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   registers[26] = 9.99999975e-05f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   registers[28] = 9.99999975e-05f;
   initialized[28] = true;
   printf("INIT: reg[%d] = %.8f\n", 28, registers[28]);

   registers[48] = -1.49798918f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   registers[16] = 0.00559213711f;
   initialized[16] = true;
   printf("INIT: reg[%d] = %.8f\n", 16, registers[16]);

   if (!initialized[48] || !initialized[16]) {
   print_error("Instruction 277: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[16];
 result = src1 - src2;
   registers[32] = result;
   initialized[32] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 32, 48, 16, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.50358129f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_32_5: expected %.8f, got %.8f\n", -1.50358129f, result);
       verification_errors++;
   } else {
       print_success("reg_32_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[48] || !initialized[16]) {
   print_error("Instruction 278: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[16];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 278");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[15] = result;
   initialized[15] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 15, 48, 16, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -267.874176f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_6: expected %.8f, got %.8f\n", -267.874176f, result);
       verification_errors++;
   } else {
       print_success("reg_15_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[32] || !initialized[15]) {
   print_error("Instruction 279: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[15];
 result = src1 - src2;
   registers[52] = result;
   initialized[52] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 52, 32, 15, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 266.370605f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_4: expected %.8f, got %.8f\n", 266.370605f, result);
       verification_errors++;
   } else {
       print_success("reg_52_4 matches: ");       printf("                       %.8f", result);
   }

   registers[53] = 1.01860917f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[31] = -1.98815489f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   if (!initialized[53] || !initialized[31]) {
   print_error("Instruction 282: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[31];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 282");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[23] = result;
   initialized[23] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 23, 53, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.512338936f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_4: expected %.8f, got %.8f\n", -0.512338936f, result);
       verification_errors++;
   } else {
       print_success("reg_23_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[31]) {
   print_error("Instruction 283: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[31];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 283");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[11] = result;
   initialized[11] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 11, 23, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.257695675f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_11_3: expected %.8f, got %.8f\n", 0.257695675f, result);
       verification_errors++;
   } else {
       print_success("reg_11_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[31] || !initialized[53]) {
   print_error("Instruction 284: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[31];
src2 = registers[53];
 result = src1 - src2;
   registers[39] = result;
   initialized[39] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 39, 31, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -3.00676394f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_39_2: expected %.8f, got %.8f\n", -3.00676394f, result);
       verification_errors++;
   } else {
       print_success("reg_39_2 matches: ");       printf("                       %.8f", result);
   }

   registers[50] = -0.99609369f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[29] = -1.12550163f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   if (!initialized[50] || !initialized[29]) {
   print_error("Instruction 287: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[50];
src2 = registers[29];
 result = src1 * src2;
   registers[8] = result;
   initialized[8] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 8, 50, 29, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.12110507f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_8_4: expected %.8f, got %.8f\n", 1.12110507f, result);
       verification_errors++;
   } else {
       print_success("reg_8_4 matches: ");       printf("                       %.8f", result);
   }

   registers[31] = 9.99999975e-05f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   registers[45] = 9.99999975e-05f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[45] = 14.9980392f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[24] = -0.248609185f;
   initialized[24] = true;
   printf("INIT: reg[%d] = %.8f\n", 24, registers[24]);

   if (!initialized[24] || !initialized[45]) {
   print_error("Instruction 292: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[24];
src2 = registers[45];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 292");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[41] = result;
   initialized[41] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 41, 24, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0165761132f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_5: expected %.8f, got %.8f\n", -0.0165761132f, result);
       verification_errors++;
   } else {
       print_success("reg_41_5 matches: ");       printf("                       %.8f", result);
   }

   registers[46] = 566.966736f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   if (!initialized[24] || !initialized[46]) {
   print_error("Instruction 294: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[24];
src2 = registers[46];
 result = src1 * src2;
   registers[61] = result;
   initialized[61] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 61, 24, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -140.95314f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_7: expected %.8f, got %.8f\n", -140.95314f, result);
       verification_errors++;
   } else {
       print_success("reg_61_7 matches: ");       printf("                       %.8f", result);
   }

   registers[53] = 254.035645f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[24] = 0.00295499386f;
   initialized[24] = true;
   printf("INIT: reg[%d] = %.8f\n", 24, registers[24]);

   if (!initialized[24] || !initialized[53]) {
   print_error("Instruction 297: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[24];
src2 = registers[53];
 result = src1 * src2;
   registers[37] = result;
   initialized[37] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 37, 24, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.750673771f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_4: expected %.8f, got %.8f\n", 0.750673771f, result);
       verification_errors++;
   } else {
       print_success("reg_37_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[53] || !initialized[37]) {
   print_error("Instruction 298: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[37];
 result = src1 - src2;
   registers[62] = result;
   initialized[62] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 62, 53, 37, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 253.284973f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_62_4: expected %.8f, got %.8f\n", 253.284973f, result);
       verification_errors++;
   } else {
       print_success("reg_62_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[62] || !initialized[37]) {
   print_error("Instruction 299: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[62];
src2 = registers[37];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 299");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[25] = result;
   initialized[25] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 25, 62, 37, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 337.410187f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_25_6: expected %.8f, got %.8f\n", 337.410187f, result);
       verification_errors++;
   } else {
       print_success("reg_25_6 matches: ");       printf("                       %.8f", result);
   }

   registers[23] = -7.94659185f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   registers[25] = -0.497876197f;
   initialized[25] = true;
   printf("INIT: reg[%d] = %.8f\n", 25, registers[25]);

   if (!initialized[25] || !initialized[23]) {
   print_error("Instruction 302: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[23];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 302");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[35] = result;
   initialized[35] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 35, 25, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0626527965f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_7: expected %.8f, got %.8f\n", 0.0626527965f, result);
       verification_errors++;
   } else {
       print_success("reg_35_7 matches: ");       printf("                       %.8f", result);
   }

   registers[9] = -9.99999975e-05f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[25] || !initialized[9]) {
   print_error("Instruction 304: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[25];
src2 = registers[9];
 result = src1 - src2;
   registers[2] = result;
   initialized[2] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 2, 25, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.49777621f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_2_3: expected %.8f, got %.8f\n", -0.49777621f, result);
       verification_errors++;
   } else {
       print_success("reg_2_3 matches: ");       printf("                       %.8f", result);
   }

   registers[5] = -1.74999988f;
   initialized[5] = true;
   printf("INIT: reg[%d] = %.8f\n", 5, registers[5]);

   registers[19] = 0.00347123155f;
   initialized[19] = true;
   printf("INIT: reg[%d] = %.8f\n", 19, registers[19]);

   if (!initialized[19] || !initialized[5]) {
   print_error("Instruction 307: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[19];
src2 = registers[5];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 307");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[51] = result;
   initialized[51] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 51, 19, 5, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00198356109f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_51_5: expected %.8f, got %.8f\n", -0.00198356109f, result);
       verification_errors++;
   } else {
       print_success("reg_51_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[5] || !initialized[51]) {
   print_error("Instruction 308: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[5];
src2 = registers[51];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 5, 51, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00347123155f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_5: expected %.8f, got %.8f\n", 0.00347123155f, result);
       verification_errors++;
   } else {
       print_success("reg_4_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[4] || !initialized[19]) {
   print_error("Instruction 309: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[19];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 309");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 4, 19, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_7: expected %.8f, got %.8f\n", 1.0f, result);
       verification_errors++;
   } else {
       print_success("reg_55_7 matches: ");       printf("                       %.8f", result);
   }

   registers[29] = -1.92067122f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   registers[56] = 0.172767833f;
   initialized[56] = true;
   printf("INIT: reg[%d] = %.8f\n", 56, registers[56]);

   if (!initialized[29] || !initialized[56]) {
   print_error("Instruction 312: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[56];
 result = src1 - src2;
   registers[26] = result;
   initialized[26] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 26, 29, 56, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.0934391f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_8: expected %.8f, got %.8f\n", -2.0934391f, result);
       verification_errors++;
   } else {
       print_success("reg_26_8 matches: ");       printf("                       %.8f", result);
   }

   registers[48] = -0.357890189f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   if (!initialized[48] || !initialized[26]) {
   print_error("Instruction 314: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[26];
 result = src1 * src2;
   registers[27] = result;
   initialized[27] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 27, 48, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.749221325f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_3: expected %.8f, got %.8f\n", 0.749221325f, result);
       verification_errors++;
   } else {
       print_success("reg_27_3 matches: ");       printf("                       %.8f", result);
   }

   registers[13] = 1.99607897f;
   initialized[13] = true;
   printf("INIT: reg[%d] = %.8f\n", 13, registers[13]);

   registers[50] = 0.0324856937f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[38] = 0.016365055f;
   initialized[38] = true;
   printf("INIT: reg[%d] = %.8f\n", 38, registers[38]);

   if (!initialized[13] || !initialized[38]) {
   print_error("Instruction 318: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[13];
src2 = registers[38];
 result = src1 * src2;
   registers[3] = result;
   initialized[3] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 3, 13, 38, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0326659419f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_3_5: expected %.8f, got %.8f\n", 0.0326659419f, result);
       verification_errors++;
   } else {
       print_success("reg_3_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[13] || !initialized[50]) {
   print_error("Instruction 319: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[13];
src2 = registers[50];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 319");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[11] = result;
   initialized[11] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 11, 13, 50, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 61.4448624f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_11_4: expected %.8f, got %.8f\n", 61.4448624f, result);
       verification_errors++;
   } else {
       print_success("reg_11_4 matches: ");       printf("                       %.8f", result);
   }

   registers[57] = 0.00195234688f;
   initialized[57] = true;
   printf("INIT: reg[%d] = %.8f\n", 57, registers[57]);

   registers[10] = -0.498535186f;
   initialized[10] = true;
   printf("INIT: reg[%d] = %.8f\n", 10, registers[10]);

   if (!initialized[10] || !initialized[57]) {
   print_error("Instruction 322: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[10];
src2 = registers[57];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 322");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[20] = result;
   initialized[20] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 20, 10, 57, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -255.351746f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_6: expected %.8f, got %.8f\n", -255.351746f, result);
       verification_errors++;
   } else {
       print_success("reg_20_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[57] || !initialized[10]) {
   print_error("Instruction 323: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[57];
src2 = registers[10];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 57, 10, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.500487506f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_4: expected %.8f, got %.8f\n", 0.500487506f, result);
       verification_errors++;
   } else {
       print_success("reg_27_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[57] || !initialized[20]) {
   print_error("Instruction 324: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[57];
src2 = registers[20];
 result = src1 - src2;
   registers[23] = result;
   initialized[23] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 23, 57, 20, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 255.353699f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_6: expected %.8f, got %.8f\n", 255.353699f, result);
       verification_errors++;
   } else {
       print_success("reg_23_6 matches: ");       printf("                       %.8f", result);
   }

   registers[8] = -0.0121073835f;
   initialized[8] = true;
   printf("INIT: reg[%d] = %.8f\n", 8, registers[8]);

   registers[45] = -150.363174f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   if (!initialized[45] || !initialized[8]) {
   print_error("Instruction 327: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[45];
src2 = registers[8];
 result = src1 - src2;
   registers[13] = result;
   initialized[13] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 13, 45, 8, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -150.351074f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_7: expected %.8f, got %.8f\n", -150.351074f, result);
       verification_errors++;
   } else {
       print_success("reg_13_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[8] || !initialized[13]) {
   print_error("Instruction 328: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[8];
src2 = registers[13];
 result = src1 * src2;
   registers[14] = result;
   initialized[14] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 14, 8, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.82035816f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_5: expected %.8f, got %.8f\n", 1.82035816f, result);
       verification_errors++;
   } else {
       print_success("reg_14_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[45]) {
   print_error("Instruction 329: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[45];
 result = src1 * src2;
   registers[47] = result;
   initialized[47] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 47, 14, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -273.714844f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_7: expected %.8f, got %.8f\n", -273.714844f, result);
       verification_errors++;
   } else {
       print_success("reg_47_7 matches: ");       printf("                       %.8f", result);
   }

   registers[35] = -118.780357f;
   initialized[35] = true;
   printf("INIT: reg[%d] = %.8f\n", 35, registers[35]);

   registers[39] = 16.7168465f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   if (!initialized[35] || !initialized[39]) {
   print_error("Instruction 332: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[35];
src2 = registers[39];
 result = src1 - src2;
   registers[20] = result;
   initialized[20] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 20, 35, 39, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -135.497208f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_20_7: expected %.8f, got %.8f\n", -135.497208f, result);
       verification_errors++;
   } else {
       print_success("reg_20_7 matches: ");       printf("                       %.8f", result);
   }

   registers[60] = 9.99999975e-05f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   if (!initialized[20] || !initialized[39]) {
   print_error("Instruction 334: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[20];
src2 = registers[39];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 334");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[46] = result;
   initialized[46] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 46, 20, 39, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -8.1054287f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_10: expected %.8f, got %.8f\n", -8.1054287f, result);
       verification_errors++;
   } else {
       print_success("reg_46_10 matches: ");       printf("                       %.8f", result);
   }

   registers[48] = -32.000103f;
   initialized[48] = true;
   printf("INIT: reg[%d] = %.8f\n", 48, registers[48]);

   registers[60] = -31.9991302f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   if (!initialized[48] || !initialized[60]) {
   print_error("Instruction 337: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[60];
 result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 48, 60, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000972747803f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_6: expected %.8f, got %.8f\n", -0.000972747803f, result);
       verification_errors++;
   } else {
       print_success("reg_1_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[48] || !initialized[1]) {
   print_error("Instruction 338: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[1];
 result = src1 - src2;
   registers[49] = result;
   initialized[49] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 49, 48, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -31.9991302f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_49_7: expected %.8f, got %.8f\n", -31.9991302f, result);
       verification_errors++;
   } else {
       print_success("reg_49_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[48] || !initialized[1]) {
   print_error("Instruction 339: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[48];
src2 = registers[1];
 result = src1 - src2;
   registers[32] = result;
   initialized[32] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 32, 48, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -31.9991302f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_32_6: expected %.8f, got %.8f\n", -31.9991302f, result);
       verification_errors++;
   } else {
       print_success("reg_32_6 matches: ");       printf("                       %.8f", result);
   }

   registers[55] = 1.15408885f;
   initialized[55] = true;
   printf("INIT: reg[%d] = %.8f\n", 55, registers[55]);

   registers[4] = 0.00315954699f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   if (!initialized[4] || !initialized[55]) {
   print_error("Instruction 342: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[55];
 result = src1 * src2;
   registers[53] = result;
   initialized[53] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 53, 4, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00364639796f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_8: expected %.8f, got %.8f\n", 0.00364639796f, result);
       verification_errors++;
   } else {
       print_success("reg_53_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[53] || !initialized[55]) {
   print_error("Instruction 343: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[55];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 343");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[47] = result;
   initialized[47] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 47, 53, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00315954699f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_8: expected %.8f, got %.8f\n", 0.00315954699f, result);
       verification_errors++;
   } else {
       print_success("reg_47_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[55] || !initialized[4]) {
   print_error("Instruction 344: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 344");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[52] = result;
   initialized[52] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 52, 55, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 365.270355f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_5: expected %.8f, got %.8f\n", 365.270355f, result);
       verification_errors++;
   } else {
       print_success("reg_52_5 matches: ");       printf("                       %.8f", result);
   }

   registers[52] = 0.284951925f;
   initialized[52] = true;
   printf("INIT: reg[%d] = %.8f\n", 52, registers[52]);

   registers[40] = -0.131061137f;
   initialized[40] = true;
   printf("INIT: reg[%d] = %.8f\n", 40, registers[40]);

   if (!initialized[52] || !initialized[40]) {
   print_error("Instruction 347: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[52];
src2 = registers[40];
 result = src1 - src2;
   registers[58] = result;
   initialized[58] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 58, 52, 40, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.416013062f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_58_6: expected %.8f, got %.8f\n", 0.416013062f, result);
       verification_errors++;
   } else {
       print_success("reg_58_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[40] || !initialized[58]) {
   print_error("Instruction 348: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[58];
 result = src1 - src2;
   registers[44] = result;
   initialized[44] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 44, 40, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.547074199f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_44_5: expected %.8f, got %.8f\n", -0.547074199f, result);
       verification_errors++;
   } else {
       print_success("reg_44_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[44] || !initialized[52]) {
   print_error("Instruction 349: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[44];
src2 = registers[52];
 result = src1 - src2;
   registers[56] = result;
   initialized[56] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 56, 44, 52, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.832026124f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_56_5: expected %.8f, got %.8f\n", -0.832026124f, result);
       verification_errors++;
   } else {
       print_success("reg_56_5 matches: ");       printf("                       %.8f", result);
   }

   registers[6] = 14.2553005f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[9] = 0.495550096f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   registers[56] = 0.000294775993f;
   initialized[56] = true;
   printf("INIT: reg[%d] = %.8f\n", 56, registers[56]);

   if (!initialized[9] || !initialized[56]) {
   print_error("Instruction 353: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[56];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 9, 56, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000146076272f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_7: expected %.8f, got %.8f\n", 0.000146076272f, result);
       verification_errors++;
   } else {
       print_success("reg_4_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[6] || !initialized[9]) {
   print_error("Instruction 354: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[6];
src2 = registers[9];
 result = src1 * src2;
   registers[53] = result;
   initialized[53] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 53, 6, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 7.06421566f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_9: expected %.8f, got %.8f\n", 7.06421566f, result);
       verification_errors++;
   } else {
       print_success("reg_53_9 matches: ");       printf("                       %.8f", result);
   }

   registers[6] = 99.1408691f;
   initialized[6] = true;
   printf("INIT: reg[%d] = %.8f\n", 6, registers[6]);

   registers[26] = 0.890871465f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[6] || !initialized[26]) {
   print_error("Instruction 357: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[6];
src2 = registers[26];
 result = src1 - src2;
   registers[41] = result;
   initialized[41] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 41, 6, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 98.25f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_6: expected %.8f, got %.8f\n", 98.25f, result);
       verification_errors++;
   } else {
       print_success("reg_41_6 matches: ");       printf("                       %.8f", result);
   }

   registers[49] = 0.0107630147f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[49] || !initialized[26]) {
   print_error("Instruction 359: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[49];
src2 = registers[26];
 result = src1 * src2;
   registers[47] = result;
   initialized[47] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 47, 49, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0095884623f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_47_9: expected %.8f, got %.8f\n", 0.0095884623f, result);
       verification_errors++;
   } else {
       print_success("reg_47_9 matches: ");       printf("                       %.8f", result);
   }

   registers[31] = -0.00310928794f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   registers[18] = 0.00739400461f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   if (!initialized[18] || !initialized[31]) {
   print_error("Instruction 362: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[18];
src2 = registers[31];
 result = src1 - src2;
   registers[33] = result;
   initialized[33] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 33, 18, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0105032921f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_33_6: expected %.8f, got %.8f\n", 0.0105032921f, result);
       verification_errors++;
   } else {
       print_success("reg_33_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[33] || !initialized[31]) {
   print_error("Instruction 363: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[33];
src2 = registers[31];
 result = src1 - src2;
   registers[1] = result;
   initialized[1] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 1, 33, 31, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0136125796f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_1_7: expected %.8f, got %.8f\n", 0.0136125796f, result);
       verification_errors++;
   } else {
       print_success("reg_1_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[18]) {
   print_error("Instruction 364: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[18];
 result = src1 * src2;
   registers[45] = result;
   initialized[45] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 45, 1, 18, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000100651479f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_45_8: expected %.8f, got %.8f\n", 0.000100651479f, result);
       verification_errors++;
   } else {
       print_success("reg_45_8 matches: ");       printf("                       %.8f", result);
   }

   registers[4] = 0.986712873f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   registers[7] = 1.21435535f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[4] || !initialized[7]) {
   print_error("Instruction 367: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[7];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 367");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[38] = result;
   initialized[38] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 38, 4, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.812540472f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_38_3: expected %.8f, got %.8f\n", 0.812540472f, result);
       verification_errors++;
   } else {
       print_success("reg_38_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[4]) {
   print_error("Instruction 368: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 368");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[28] = result;
   initialized[28] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 28, 7, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.23070788f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_28_8: expected %.8f, got %.8f\n", 1.23070788f, result);
       verification_errors++;
   } else {
       print_success("reg_28_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[4]) {
   print_error("Instruction 369: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 369");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[9] = result;
   initialized[9] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 9, 7, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.23070788f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_9_7: expected %.8f, got %.8f\n", 1.23070788f, result);
       verification_errors++;
   } else {
       print_success("reg_9_7 matches: ");       printf("                       %.8f", result);
   }

   registers[9] = 1.94061875f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   registers[1] = 0.000121874138f;
   initialized[1] = true;
   printf("INIT: reg[%d] = %.8f\n", 1, registers[1]);

   if (!initialized[9] || !initialized[1]) {
   print_error("Instruction 372: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[1];
 result = src1 * src2;
   registers[21] = result;
   initialized[21] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 21, 9, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000236511245f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_7: expected %.8f, got %.8f\n", 0.000236511245f, result);
       verification_errors++;
   } else {
       print_success("reg_21_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[21] || !initialized[1]) {
   print_error("Instruction 373: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[1];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 373");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[61] = result;
   initialized[61] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 61, 21, 1, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.94061875f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_8: expected %.8f, got %.8f\n", 1.94061875f, result);
       verification_errors++;
   } else {
       print_success("reg_61_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[1] || !initialized[61]) {
   print_error("Instruction 374: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[1];
src2 = registers[61];
 result = src1 * src2;
   registers[14] = result;
   initialized[14] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 14, 1, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000236511245f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_6: expected %.8f, got %.8f\n", 0.000236511245f, result);
       verification_errors++;
   } else {
       print_success("reg_14_6 matches: ");       printf("                       %.8f", result);
   }

   registers[61] = -0.124674402f;
   initialized[61] = true;
   printf("INIT: reg[%d] = %.8f\n", 61, registers[61]);

   registers[32] = -34.1255798f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   if (!initialized[32] || !initialized[61]) {
   print_error("Instruction 377: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[61];
 result = src1 - src2;
   registers[42] = result;
   initialized[42] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 42, 32, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -34.0009041f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_42_5: expected %.8f, got %.8f\n", -34.0009041f, result);
       verification_errors++;
   } else {
       print_success("reg_42_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[61]) {
   print_error("Instruction 378: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[61];
 result = src1 - src2;
   registers[27] = result;
   initialized[27] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 27, 42, 61, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -33.8762283f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_5: expected %.8f, got %.8f\n", -33.8762283f, result);
       verification_errors++;
   } else {
       print_success("reg_27_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[27]) {
   print_error("Instruction 379: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[27];
 result = src1 - src2;
   registers[43] = result;
   initialized[43] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 43, 42, 27, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.124675751f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_43_5: expected %.8f, got %.8f\n", -0.124675751f, result);
       verification_errors++;
   } else {
       print_success("reg_43_5 matches: ");       printf("                       %.8f", result);
   }

   registers[34] = -0.000448255771f;
   initialized[34] = true;
   printf("INIT: reg[%d] = %.8f\n", 34, registers[34]);

   registers[51] = -1.51726043f;
   initialized[51] = true;
   printf("INIT: reg[%d] = %.8f\n", 51, registers[51]);

   if (!initialized[34] || !initialized[51]) {
   print_error("Instruction 382: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[34];
src2 = registers[51];
 result = src1 * src2;
   registers[55] = result;
   initialized[55] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 55, 34, 51, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00068012072f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_9: expected %.8f, got %.8f\n", 0.00068012072f, result);
       verification_errors++;
   } else {
       print_success("reg_55_9 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[51] || !initialized[55]) {
   print_error("Instruction 383: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[51];
src2 = registers[55];
 result = src1 * src2;
   registers[40] = result;
   initialized[40] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 40, 51, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00103192031f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_7: expected %.8f, got %.8f\n", -0.00103192031f, result);
       verification_errors++;
   } else {
       print_success("reg_40_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[51] || !initialized[55]) {
   print_error("Instruction 384: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[51];
src2 = registers[55];
 result = src1 - src2;
   registers[53] = result;
   initialized[53] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 53, 51, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -1.51794052f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_10: expected %.8f, got %.8f\n", -1.51794052f, result);
       verification_errors++;
   } else {
       print_success("reg_53_10 matches: ");       printf("                       %.8f", result);
   }

   registers[31] = 9.99999975e-05f;
   initialized[31] = true;
   printf("INIT: reg[%d] = %.8f\n", 31, registers[31]);

   registers[2] = 54.4921265f;
   initialized[2] = true;
   printf("INIT: reg[%d] = %.8f\n", 2, registers[2]);

   registers[53] = 9.99999975e-05f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   registers[4] = -61.3125f;
   initialized[4] = true;
   printf("INIT: reg[%d] = %.8f\n", 4, registers[4]);

   if (!initialized[4] || !initialized[2]) {
   print_error("Instruction 389: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[4];
src2 = registers[2];
 result = src1 - src2;
   registers[18] = result;
   initialized[18] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 18, 4, 2, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -115.804626f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_18_7: expected %.8f, got %.8f\n", -115.804626f, result);
       verification_errors++;
   } else {
       print_success("reg_18_7 matches: ");       printf("                       %.8f", result);
   }

   registers[23] = 9.99999975e-05f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   registers[39] = 1.95941889f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   registers[47] = 0.0808939189f;
   initialized[47] = true;
   printf("INIT: reg[%d] = %.8f\n", 47, registers[47]);

   if (!initialized[47] || !initialized[39]) {
   print_error("Instruction 393: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[47];
src2 = registers[39];
 result = src1 * src2;
   registers[41] = result;
   initialized[41] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 41, 47, 39, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.158505067f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_7: expected %.8f, got %.8f\n", 0.158505067f, result);
       verification_errors++;
   } else {
       print_success("reg_41_7 matches: ");       printf("                       %.8f", result);
   }

   registers[24] = 9.99999975e-05f;
   initialized[24] = true;
   printf("INIT: reg[%d] = %.8f\n", 24, registers[24]);

   registers[60] = -2.89643407f;
   initialized[60] = true;
   printf("INIT: reg[%d] = %.8f\n", 60, registers[60]);

   registers[9] = -0.318346322f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   if (!initialized[60] || !initialized[9]) {
   print_error("Instruction 397: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[60];
src2 = registers[9];
 result = src1 * src2;
   registers[34] = result;
   initialized[34] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 34, 60, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.922069132f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_34_3: expected %.8f, got %.8f\n", 0.922069132f, result);
       verification_errors++;
   } else {
       print_success("reg_34_3 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[34] || !initialized[60]) {
   print_error("Instruction 398: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[34];
src2 = registers[60];
 result = src1 - src2;
   registers[24] = result;
   initialized[24] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 24, 34, 60, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 3.81850314f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_7: expected %.8f, got %.8f\n", 3.81850314f, result);
       verification_errors++;
   } else {
       print_success("reg_24_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[24] || !initialized[34]) {
   print_error("Instruction 399: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[24];
src2 = registers[34];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 399");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[62] = result;
   initialized[62] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 62, 24, 34, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 4.14123297f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_62_5: expected %.8f, got %.8f\n", 4.14123297f, result);
       verification_errors++;
   } else {
       print_success("reg_62_5 matches: ");       printf("                       %.8f", result);
   }

   registers[23] = 0.359835088f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   registers[26] = -0.0135696875f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[23] || !initialized[26]) {
   print_error("Instruction 402: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[26];
 result = src1 * src2;
   registers[59] = result;
   initialized[59] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 59, 23, 26, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00488284975f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_59_4: expected %.8f, got %.8f\n", -0.00488284975f, result);
       verification_errors++;
   } else {
       print_success("reg_59_4 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[26] || !initialized[59]) {
   print_error("Instruction 403: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[26];
src2 = registers[59];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 403");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[39] = result;
   initialized[39] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 39, 26, 59, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 2.77905083f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_39_5: expected %.8f, got %.8f\n", 2.77905083f, result);
       verification_errors++;
   } else {
       print_success("reg_39_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[59]) {
   print_error("Instruction 404: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[59];
 result = src1 - src2;
   registers[56] = result;
   initialized[56] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 56, 23, 59, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.364717931f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_56_7: expected %.8f, got %.8f\n", 0.364717931f, result);
       verification_errors++;
   } else {
       print_success("reg_56_7 matches: ");       printf("                       %.8f", result);
   }

   registers[40] = 2.99804664f;
   initialized[40] = true;
   printf("INIT: reg[%d] = %.8f\n", 40, registers[40]);

   registers[41] = 0.000124877013f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   registers[22] = 0.817843974f;
   initialized[22] = true;
   printf("INIT: reg[%d] = %.8f\n", 22, registers[22]);

   if (!initialized[41] || !initialized[40]) {
   print_error("Instruction 408: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[41];
src2 = registers[40];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 41, 40, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000374387106f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_10: expected %.8f, got %.8f\n", 0.000374387106f, result);
       verification_errors++;
   } else {
       print_success("reg_4_10 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[22] || !initialized[4]) {
   print_error("Instruction 409: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[22];
src2 = registers[4];
 result = src1 * src2;
   registers[42] = result;
   initialized[42] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 42, 22, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000306190224f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_42_6: expected %.8f, got %.8f\n", 0.000306190224f, result);
       verification_errors++;
   } else {
       print_success("reg_42_6 matches: ");       printf("                       %.8f", result);
   }

   registers[54] = 0.0529115573f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   registers[49] = 181.56636f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[54] || !initialized[49]) {
   print_error("Instruction 412: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[49];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 412");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 54, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000291417178f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_10: expected %.8f, got %.8f\n", 0.000291417178f, result);
       verification_errors++;
   } else {
       print_success("reg_55_10 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[54] || !initialized[49]) {
   print_error("Instruction 413: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[49];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 413");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[4] = result;
   initialized[4] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 4, 54, 49, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000291417178f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_11: expected %.8f, got %.8f\n", 0.000291417178f, result);
       verification_errors++;
   } else {
       print_success("reg_4_11 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[55] || !initialized[4]) {
   print_error("Instruction 414: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[4];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 414");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[21] = result;
   initialized[21] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 21, 55, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_21_8: expected %.8f, got %.8f\n", 1.0f, result);
       verification_errors++;
   } else {
       print_success("reg_21_8 matches: ");       printf("                       %.8f", result);
   }

   registers[32] = -0.0459079593f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   registers[41] = 0.0165920388f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   if (!initialized[41] || !initialized[32]) {
   print_error("Instruction 417: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[41];
src2 = registers[32];
 result = src1 * src2;
   registers[40] = result;
   initialized[40] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 40, 41, 32, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000761706615f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_9: expected %.8f, got %.8f\n", -0.000761706615f, result);
       verification_errors++;
   } else {
       print_success("reg_40_9 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[32] || !initialized[41]) {
   print_error("Instruction 418: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[41];
 result = src1 - src2;
   registers[53] = result;
   initialized[53] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 53, 32, 41, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0625f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_12: expected %.8f, got %.8f\n", -0.0625f, result);
       verification_errors++;
   } else {
       print_success("reg_53_12 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[40] || !initialized[53]) {
   print_error("Instruction 419: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[40];
src2 = registers[53];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 419");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[10] = result;
   initialized[10] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 10, 40, 53, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0121873058f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_10_7: expected %.8f, got %.8f\n", 0.0121873058f, result);
       verification_errors++;
   } else {
       print_success("reg_10_7 matches: ");       printf("                       %.8f", result);
   }

   registers[34] = 1.0f;
   initialized[34] = true;
   printf("INIT: reg[%d] = %.8f\n", 34, registers[34]);

   registers[14] = 0.472655892f;
   initialized[14] = true;
   printf("INIT: reg[%d] = %.8f\n", 14, registers[14]);

   if (!initialized[34] || !initialized[14]) {
   print_error("Instruction 422: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[34];
src2 = registers[14];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 422");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[42] = result;
   initialized[42] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 42, 34, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 2.11570406f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_42_7: expected %.8f, got %.8f\n", 2.11570406f, result);
       verification_errors++;
   } else {
       print_success("reg_42_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[14]) {
   print_error("Instruction 423: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[14];
 result = src1 * src2;
   registers[4] = result;
   initialized[4] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 4, 42, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_4_12: expected %.8f, got %.8f\n", 1.0f, result);
       verification_errors++;
   } else {
       print_success("reg_4_12 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[4]) {
   print_error("Instruction 424: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[4];
 result = src1 * src2;
   registers[37] = result;
   initialized[37] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 37, 14, 4, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.472655892f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_37_5: expected %.8f, got %.8f\n", 0.472655892f, result);
       verification_errors++;
   } else {
       print_success("reg_37_5 matches: ");       printf("                       %.8f", result);
   }

   registers[46] = 47.9877892f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   registers[26] = 0.199446365f;
   initialized[26] = true;
   printf("INIT: reg[%d] = %.8f\n", 26, registers[26]);

   if (!initialized[26] || !initialized[46]) {
   print_error("Instruction 427: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[26];
src2 = registers[46];
 result = src1 * src2;
   registers[13] = result;
   initialized[13] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 13, 26, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 9.57099056f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_8: expected %.8f, got %.8f\n", 9.57099056f, result);
       verification_errors++;
   } else {
       print_success("reg_13_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[46] || !initialized[13]) {
   print_error("Instruction 428: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[13];
 result = src1 - src2;
   registers[14] = result;
   initialized[14] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 14, 46, 13, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 38.4167976f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_8: expected %.8f, got %.8f\n", 38.4167976f, result);
       verification_errors++;
   } else {
       print_success("reg_14_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[14] || !initialized[46]) {
   print_error("Instruction 429: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[14];
src2 = registers[46];
 result = src1 - src2;
   registers[40] = result;
   initialized[40] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 40, 14, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -9.57099152f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_40_10: expected %.8f, got %.8f\n", -9.57099152f, result);
       verification_errors++;
   } else {
       print_success("reg_40_10 matches: ");       printf("                       %.8f", result);
   }

   registers[44] = 2.63429952f;
   initialized[44] = true;
   printf("INIT: reg[%d] = %.8f\n", 44, registers[44]);

   registers[32] = -509.521942f;
   initialized[32] = true;
   printf("INIT: reg[%d] = %.8f\n", 32, registers[32]);

   if (!initialized[32] || !initialized[44]) {
   print_error("Instruction 432: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[44];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 432");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[62] = result;
   initialized[62] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 62, 32, 44, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -193.418381f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_62_6: expected %.8f, got %.8f\n", -193.418381f, result);
       verification_errors++;
   } else {
       print_success("reg_62_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[32] || !initialized[44]) {
   print_error("Instruction 433: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[32];
src2 = registers[44];
 result = src1 - src2;
   registers[23] = result;
   initialized[23] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 23, 32, 44, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -512.15625f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_23_9: expected %.8f, got %.8f\n", -512.15625f, result);
       verification_errors++;
   } else {
       print_success("reg_23_9 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[62] || !initialized[23]) {
   print_error("Instruction 434: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[62];
src2 = registers[23];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 434");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[55] = result;
   initialized[55] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 55, 62, 23, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.377655029f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_11: expected %.8f, got %.8f\n", 0.377655029f, result);
       verification_errors++;
   } else {
       print_success("reg_55_11 matches: ");       printf("                       %.8f", result);
   }

   registers[21] = 0.00191965303f;
   initialized[21] = true;
   printf("INIT: reg[%d] = %.8f\n", 21, registers[21]);

   registers[54] = 0.00243757362f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   if (!initialized[54] || !initialized[21]) {
   print_error("Instruction 437: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[21];
 result = src1 - src2;
   registers[15] = result;
   initialized[15] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 15, 54, 21, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000517920591f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_7: expected %.8f, got %.8f\n", 0.000517920591f, result);
       verification_errors++;
   } else {
       print_success("reg_15_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[21] || !initialized[54]) {
   print_error("Instruction 438: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[21];
src2 = registers[54];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 438");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[35] = result;
   initialized[35] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 35, 21, 54, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.78752619f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_35_9: expected %.8f, got %.8f\n", 0.78752619f, result);
       verification_errors++;
   } else {
       print_success("reg_35_9 matches: ");       printf("                       %.8f", result);
   }

   registers[41] = 9.99999975e-05f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   registers[27] = 516.050537f;
   initialized[27] = true;
   printf("INIT: reg[%d] = %.8f\n", 27, registers[27]);

   registers[23] = -0.000453432673f;
   initialized[23] = true;
   printf("INIT: reg[%d] = %.8f\n", 23, registers[23]);

   if (!initialized[23] || !initialized[27]) {
   print_error("Instruction 442: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[27];
 result = src1 * src2;
   registers[11] = result;
   initialized[11] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 11, 23, 27, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.233994171f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_11_5: expected %.8f, got %.8f\n", -0.233994171f, result);
       verification_errors++;
   } else {
       print_success("reg_11_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[27] || !initialized[11]) {
   print_error("Instruction 443: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[27];
src2 = registers[11];
 result = src1 - src2;
   registers[50] = result;
   initialized[50] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 50, 27, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 516.284546f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_50_8: expected %.8f, got %.8f\n", 516.284546f, result);
       verification_errors++;
   } else {
       print_success("reg_50_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[23] || !initialized[11]) {
   print_error("Instruction 444: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[23];
src2 = registers[11];
 result = src1 * src2;
   registers[26] = result;
   initialized[26] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 26, 23, 11, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000106100604f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_12: expected %.8f, got %.8f\n", 0.000106100604f, result);
       verification_errors++;
   } else {
       print_success("reg_26_12 matches: ");       printf("                       %.8f", result);
   }

   registers[54] = -7.9981451f;
   initialized[54] = true;
   printf("INIT: reg[%d] = %.8f\n", 54, registers[54]);

   registers[43] = 9.99999975e-05f;
   initialized[43] = true;
   printf("INIT: reg[%d] = %.8f\n", 43, registers[43]);

   registers[50] = 192.624893f;
   initialized[50] = true;
   printf("INIT: reg[%d] = %.8f\n", 50, registers[50]);

   registers[20] = 9.99999975e-05f;
   initialized[20] = true;
   printf("INIT: reg[%d] = %.8f\n", 20, registers[20]);

   if (!initialized[54] || !initialized[50]) {
   print_error("Instruction 449: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[54];
src2 = registers[50];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 449");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[13] = result;
   initialized[13] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 13, 54, 50, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.0415218659f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_13_9: expected %.8f, got %.8f\n", -0.0415218659f, result);
       verification_errors++;
   } else {
       print_success("reg_13_9 matches: ");       printf("                       %.8f", result);
   }

   registers[55] = 0.000551782665f;
   initialized[55] = true;
   printf("INIT: reg[%d] = %.8f\n", 55, registers[55]);

   registers[46] = 0.0039062479f;
   initialized[46] = true;
   printf("INIT: reg[%d] = %.8f\n", 46, registers[46]);

   if (!initialized[46] || !initialized[55]) {
   print_error("Instruction 452: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[46];
src2 = registers[55];
 result = src1 - src2;
   registers[53] = result;
   initialized[53] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 53, 46, 55, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.00335446512f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_53_13: expected %.8f, got %.8f\n", 0.00335446512f, result);
       verification_errors++;
   } else {
       print_success("reg_53_13 matches: ");       printf("                       %.8f", result);
   }

   registers[49] = 9.99999975e-05f;
   initialized[49] = true;
   printf("INIT: reg[%d] = %.8f\n", 49, registers[49]);

   if (!initialized[55] || !initialized[46]) {
   print_error("Instruction 454: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[55];
src2 = registers[46];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 454");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[5] = result;
   initialized[5] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 5, 55, 46, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.141256437f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_5: expected %.8f, got %.8f\n", 0.141256437f, result);
       verification_errors++;
   } else {
       print_success("reg_5_5 matches: ");       printf("                       %.8f", result);
   }

   registers[39] = 0.99878037f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   registers[38] = -128.157837f;
   initialized[38] = true;
   printf("INIT: reg[%d] = %.8f\n", 38, registers[38]);

   registers[17] = -8.25386715f;
   initialized[17] = true;
   printf("INIT: reg[%d] = %.8f\n", 17, registers[17]);

   if (!initialized[38] || !initialized[17]) {
   print_error("Instruction 458: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[38];
src2 = registers[17];
 result = src1 - src2;
   registers[55] = result;
   initialized[55] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 55, 38, 17, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -119.903969f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_55_13: expected %.8f, got %.8f\n", -119.903969f, result);
       verification_errors++;
   } else {
       print_success("reg_55_13 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[39] || !initialized[38]) {
   print_error("Instruction 459: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[39];
src2 = registers[38];
 result = src1 * src2;
   registers[44] = result;
   initialized[44] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 44, 39, 38, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -128.001526f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_44_7: expected %.8f, got %.8f\n", -128.001526f, result);
       verification_errors++;
   } else {
       print_success("reg_44_7 matches: ");       printf("                       %.8f", result);
   }

   registers[45] = -405.493561f;
   initialized[45] = true;
   printf("INIT: reg[%d] = %.8f\n", 45, registers[45]);

   registers[29] = 554.506409f;
   initialized[29] = true;
   printf("INIT: reg[%d] = %.8f\n", 29, registers[29]);

   if (!initialized[29] || !initialized[45]) {
   print_error("Instruction 462: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[29];
src2 = registers[45];
 result = src1 - src2;
   registers[5] = result;
   initialized[5] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 5, 29, 45, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 960.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_5_6: expected %.8f, got %.8f\n", 960.0f, result);
       verification_errors++;
   } else {
       print_success("reg_5_6 matches: ");       printf("                       %.8f", result);
   }

   registers[57] = 9.99999975e-05f;
   initialized[57] = true;
   printf("INIT: reg[%d] = %.8f\n", 57, registers[57]);

   if (!initialized[45] || !initialized[29]) {
   print_error("Instruction 464: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[45];
src2 = registers[29];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 464");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[61] = result;
   initialized[61] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 61, 45, 29, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.73126936f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_61_10: expected %.8f, got %.8f\n", -0.73126936f, result);
       verification_errors++;
   } else {
       print_success("reg_61_10 matches: ");       printf("                       %.8f", result);
   }

   registers[42] = -0.00209294399f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   registers[0] = -447.941071f;
   initialized[0] = true;
   printf("INIT: reg[%d] = %.8f\n", 0, registers[0]);

   if (!initialized[42] || !initialized[0]) {
   print_error("Instruction 467: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[0];
 result = src1 * src2;
   registers[33] = result;
   initialized[33] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 33, 42, 0, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.937515557f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_33_7: expected %.8f, got %.8f\n", 0.937515557f, result);
       verification_errors++;
   } else {
       print_success("reg_33_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[33]) {
   print_error("Instruction 468: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[33];
 result = src1 * src2;
   registers[52] = result;
   initialized[52] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 52, 42, 33, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00196216744f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_52_7: expected %.8f, got %.8f\n", -0.00196216744f, result);
       verification_errors++;
   } else {
       print_success("reg_52_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[52] || !initialized[42]) {
   print_error("Instruction 469: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[52];
src2 = registers[42];
 result = src1 - src2;
   registers[44] = result;
   initialized[44] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 44, 52, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000130776549f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_44_8: expected %.8f, got %.8f\n", 0.000130776549f, result);
       verification_errors++;
   } else {
       print_success("reg_44_8 matches: ");       printf("                       %.8f", result);
   }

   registers[33] = 9.99999975e-05f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[41] = 15.9431877f;
   initialized[41] = true;
   printf("INIT: reg[%d] = %.8f\n", 41, registers[41]);

   registers[7] = 0.124978684f;
   initialized[7] = true;
   printf("INIT: reg[%d] = %.8f\n", 7, registers[7]);

   if (!initialized[41] || !initialized[7]) {
   print_error("Instruction 473: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[41];
src2 = registers[7];
 result = src1 * src2;
   registers[59] = result;
   initialized[59] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 59, 41, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.9925586f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_59_5: expected %.8f, got %.8f\n", 1.9925586f, result);
       verification_errors++;
   } else {
       print_success("reg_59_5 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[41] || !initialized[7]) {
   print_error("Instruction 474: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[41];
src2 = registers[7];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 474");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[34] = result;
   initialized[34] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 34, 41, 7, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 127.567253f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_34_5: expected %.8f, got %.8f\n", 127.567253f, result);
       verification_errors++;
   } else {
       print_success("reg_34_5 matches: ");       printf("                       %.8f", result);
   }

   registers[9] = 0.96912545f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   registers[42] = 272.543976f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   if (!initialized[42] || !initialized[9]) {
   print_error("Instruction 477: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[9];
 result = src1 * src2;
   registers[59] = result;
   initialized[59] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 59, 42, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 264.129303f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_59_6: expected %.8f, got %.8f\n", 264.129303f, result);
       verification_errors++;
   } else {
       print_success("reg_59_6 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[42] || !initialized[59]) {
   print_error("Instruction 478: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[42];
src2 = registers[59];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 478");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[14] = result;
   initialized[14] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 14, 42, 59, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.03185821f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_14_9: expected %.8f, got %.8f\n", 1.03185821f, result);
       verification_errors++;
   } else {
       print_success("reg_14_9 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[9] || !initialized[14]) {
   print_error("Instruction 479: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[9];
src2 = registers[14];
 result = src1 * src2;
   registers[26] = result;
   initialized[26] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 26, 9, 14, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.0f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_26_13: expected %.8f, got %.8f\n", 1.0f, result);
       verification_errors++;
   } else {
       print_success("reg_26_13 matches: ");       printf("                       %.8f", result);
   }

   registers[42] = 0.0509747267f;
   initialized[42] = true;
   printf("INIT: reg[%d] = %.8f\n", 42, registers[42]);

   registers[39] = -0.124999531f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   if (!initialized[39] || !initialized[42]) {
   print_error("Instruction 482: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[39];
src2 = registers[42];
 result = src1 - src2;
   registers[7] = result;
   initialized[7] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 7, 39, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.17597425f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_7_8: expected %.8f, got %.8f\n", -0.17597425f, result);
       verification_errors++;
   } else {
       print_success("reg_7_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[7] || !initialized[39]) {
   print_error("Instruction 483: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[7];
src2 = registers[39];
 result = src1 * src2;
   registers[41] = result;
   initialized[41] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 41, 7, 39, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.0219966993f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_41_12: expected %.8f, got %.8f\n", 0.0219966993f, result);
       verification_errors++;
   } else {
       print_success("reg_41_12 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[39] || !initialized[42]) {
   print_error("Instruction 484: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[39];
src2 = registers[42];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 484");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[24] = result;
   initialized[24] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 24, 39, 42, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -2.45218635f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_24_8: expected %.8f, got %.8f\n", -2.45218635f, result);
       verification_errors++;
   } else {
       print_success("reg_24_8 matches: ");       printf("                       %.8f", result);
   }

   registers[63] = 0.00854635146f;
   initialized[63] = true;
   printf("INIT: reg[%d] = %.8f\n", 63, registers[63]);

   registers[39] = 9.99999975e-05f;
   initialized[39] = true;
   printf("INIT: reg[%d] = %.8f\n", 39, registers[39]);

   registers[33] = 9.99999975e-05f;
   initialized[33] = true;
   printf("INIT: reg[%d] = %.8f\n", 33, registers[33]);

   registers[18] = 0.0142833246f;
   initialized[18] = true;
   printf("INIT: reg[%d] = %.8f\n", 18, registers[18]);

   if (!initialized[63] || !initialized[18]) {
   print_error("Instruction 489: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[63];
src2 = registers[18];
 result = src1 * src2;
   registers[34] = result;
   initialized[34] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 34, 63, 18, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 0.000122070312f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_34_6: expected %.8f, got %.8f\n", 0.000122070312f, result);
       verification_errors++;
   } else {
       print_success("reg_34_6 matches: ");       printf("                       %.8f", result);
   }

   registers[9] = 315.999847f;
   initialized[9] = true;
   printf("INIT: reg[%d] = %.8f\n", 9, registers[9]);

   registers[53] = 1.56303787f;
   initialized[53] = true;
   printf("INIT: reg[%d] = %.8f\n", 53, registers[53]);

   if (!initialized[53] || !initialized[9]) {
   print_error("Instruction 492: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[53];
src2 = registers[9];
 result = src1 * src2;
   registers[15] = result;
   initialized[15] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 15, 53, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 493.919739f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_15_8: expected %.8f, got %.8f\n", 493.919739f, result);
       verification_errors++;
   } else {
       print_success("reg_15_8 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[15] || !initialized[9]) {
   print_error("Instruction 493: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[15];
src2 = registers[9];
   if (src2 == 0.0f) {
       print_error("Divizion by zero at instruction 493");
       return FLOAT_ERROR;
   }
 result = src1 / src2;
   registers[27] = result;
   initialized[27] = true;
   printf("DIV: reg[%d] = reg[%d] / reg[%d] = %.8f / %.8f = %.8f\n", 27, 15, 9, src1, src2, result);
   total_checks++;
   if (!float_equal(result, 1.56303787f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_27_7: expected %.8f, got %.8f\n", 1.56303787f, result);
       verification_errors++;
   } else {
       print_success("reg_27_7 matches: ");       printf("                       %.8f", result);
   }

   registers[36] = 9.99999975e-05f;
   initialized[36] = true;
   printf("INIT: reg[%d] = %.8f\n", 36, registers[36]);

   registers[12] = 0.251716465f;
   initialized[12] = true;
   printf("INIT: reg[%d] = %.8f\n", 12, registers[12]);

   registers[58] = 0.248461053f;
   initialized[58] = true;
   printf("INIT: reg[%d] = %.8f\n", 58, registers[58]);

   if (!initialized[58] || !initialized[12]) {
   print_error("Instruction 497: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[58];
src2 = registers[12];
 result = src1 - src2;
   registers[59] = result;
   initialized[59] = true;
   printf("SUB: reg[%d] = reg[%d] - reg[%d] = %.8f - %.8f = %.8f\n", 59, 58, 12, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.00325541198f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_59_7: expected %.8f, got %.8f\n", -0.00325541198f, result);
       verification_errors++;
   } else {
       print_success("reg_59_7 matches: ");       printf("                       %.8f", result);
   }

   if (!initialized[59] || !initialized[58]) {
   print_error("Instruction 498: Using uninitialized register");
   return FLOAT_ERROR;
   }
src1 = registers[59];
src2 = registers[58];
 result = src1 * src2;
   registers[46] = result;
   initialized[46] = true;
   printf("MUL: reg[%d] = reg[%d] * reg[%d] = %.8f * %.8f = %.8f\n", 46, 59, 58, src1, src2, result);
   total_checks++;
   if (!float_equal(result, -0.000808843062f, EPSILON)) {
   printf("[ERROR] Mismatch at reg_46_13: expected %.8f, got %.8f\n", -0.000808843062f, result);
       verification_errors++;
   } else {
       print_success("reg_46_13 matches: ");       printf("                       %.8f", result);
   }

   registers[37] = 9.99999975e-05f;
   initialized[37] = true;
   printf("INIT: reg[%d] = %.8f\n", 37, registers[37]);


    print_header("Final Verification");

   total_checks++;
   if (!float_equal(registers[0], -447.941071f, EPSILON)) {
printf("[ERROR] Final reg[0] mismatch: expected -447.941071, got %.8f\n", registers[0]);
       verification_errors++;
   } else {
       print_success("Final reg[0] matches: -447.941071");
   }

   total_checks++;
   if (!float_equal(registers[1], 0.000121874138f, EPSILON)) {
printf("[ERROR] Final reg[1] mismatch: expected 0.000121874138, got %.8f\n", registers[1]);
       verification_errors++;
   } else {
       print_success("Final reg[1] matches: 0.000121874138");
   }

   total_checks++;
   if (!float_equal(registers[2], 54.4921265f, EPSILON)) {
printf("[ERROR] Final reg[2] mismatch: expected 54.4921265, got %.8f\n", registers[2]);
       verification_errors++;
   } else {
       print_success("Final reg[2] matches: 54.4921265");
   }

   total_checks++;
   if (!float_equal(registers[3], 0.0326659419f, EPSILON)) {
printf("[ERROR] Final reg[3] mismatch: expected 0.0326659419, got %.8f\n", registers[3]);
       verification_errors++;
   } else {
       print_success("Final reg[3] matches: 0.0326659419");
   }

   total_checks++;
   if (!float_equal(registers[4], 1.0f, EPSILON)) {
printf("[ERROR] Final reg[4] mismatch: expected 1.0, got %.8f\n", registers[4]);
       verification_errors++;
   } else {
       print_success("Final reg[4] matches: 1.0");
   }

   total_checks++;
   if (!float_equal(registers[5], 960.0f, EPSILON)) {
printf("[ERROR] Final reg[5] mismatch: expected 960.0, got %.8f\n", registers[5]);
       verification_errors++;
   } else {
       print_success("Final reg[5] matches: 960.0");
   }

   total_checks++;
   if (!float_equal(registers[6], 99.1408691f, EPSILON)) {
printf("[ERROR] Final reg[6] mismatch: expected 99.1408691, got %.8f\n", registers[6]);
       verification_errors++;
   } else {
       print_success("Final reg[6] matches: 99.1408691");
   }

   total_checks++;
   if (!float_equal(registers[7], -0.17597425f, EPSILON)) {
printf("[ERROR] Final reg[7] mismatch: expected -0.17597425, got %.8f\n", registers[7]);
       verification_errors++;
   } else {
       print_success("Final reg[7] matches: -0.17597425");
   }

   total_checks++;
   if (!float_equal(registers[8], -0.0121073835f, EPSILON)) {
printf("[ERROR] Final reg[8] mismatch: expected -0.0121073835, got %.8f\n", registers[8]);
       verification_errors++;
   } else {
       print_success("Final reg[8] matches: -0.0121073835");
   }

   total_checks++;
   if (!float_equal(registers[9], 315.999847f, EPSILON)) {
printf("[ERROR] Final reg[9] mismatch: expected 315.999847, got %.8f\n", registers[9]);
       verification_errors++;
   } else {
       print_success("Final reg[9] matches: 315.999847");
   }

   total_checks++;
   if (!float_equal(registers[10], 0.0121873058f, EPSILON)) {
printf("[ERROR] Final reg[10] mismatch: expected 0.0121873058, got %.8f\n", registers[10]);
       verification_errors++;
   } else {
       print_success("Final reg[10] matches: 0.0121873058");
   }

   total_checks++;
   if (!float_equal(registers[11], -0.233994171f, EPSILON)) {
printf("[ERROR] Final reg[11] mismatch: expected -0.233994171, got %.8f\n", registers[11]);
       verification_errors++;
   } else {
       print_success("Final reg[11] matches: -0.233994171");
   }

   total_checks++;
   if (!float_equal(registers[12], 0.251716465f, EPSILON)) {
printf("[ERROR] Final reg[12] mismatch: expected 0.251716465, got %.8f\n", registers[12]);
       verification_errors++;
   } else {
       print_success("Final reg[12] matches: 0.251716465");
   }

   total_checks++;
   if (!float_equal(registers[13], -0.0415218659f, EPSILON)) {
printf("[ERROR] Final reg[13] mismatch: expected -0.0415218659, got %.8f\n", registers[13]);
       verification_errors++;
   } else {
       print_success("Final reg[13] matches: -0.0415218659");
   }

   total_checks++;
   if (!float_equal(registers[14], 1.03185821f, EPSILON)) {
printf("[ERROR] Final reg[14] mismatch: expected 1.03185821, got %.8f\n", registers[14]);
       verification_errors++;
   } else {
       print_success("Final reg[14] matches: 1.03185821");
   }

   total_checks++;
   if (!float_equal(registers[15], 493.919739f, EPSILON)) {
printf("[ERROR] Final reg[15] mismatch: expected 493.919739, got %.8f\n", registers[15]);
       verification_errors++;
   } else {
       print_success("Final reg[15] matches: 493.919739");
   }

   total_checks++;
   if (!float_equal(registers[16], 0.00559213711f, EPSILON)) {
printf("[ERROR] Final reg[16] mismatch: expected 0.00559213711, got %.8f\n", registers[16]);
       verification_errors++;
   } else {
       print_success("Final reg[16] matches: 0.00559213711");
   }

   total_checks++;
   if (!float_equal(registers[17], -8.25386715f, EPSILON)) {
printf("[ERROR] Final reg[17] mismatch: expected -8.25386715, got %.8f\n", registers[17]);
       verification_errors++;
   } else {
       print_success("Final reg[17] matches: -8.25386715");
   }

   total_checks++;
   if (!float_equal(registers[18], 0.0142833246f, EPSILON)) {
printf("[ERROR] Final reg[18] mismatch: expected 0.0142833246, got %.8f\n", registers[18]);
       verification_errors++;
   } else {
       print_success("Final reg[18] matches: 0.0142833246");
   }

   total_checks++;
   if (!float_equal(registers[19], 0.00347123155f, EPSILON)) {
printf("[ERROR] Final reg[19] mismatch: expected 0.00347123155, got %.8f\n", registers[19]);
       verification_errors++;
   } else {
       print_success("Final reg[19] matches: 0.00347123155");
   }

   total_checks++;
   if (!float_equal(registers[20], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[20] mismatch: expected 9.99999975e-05, got %.8f\n", registers[20]);
       verification_errors++;
   } else {
       print_success("Final reg[20] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[21], 0.00191965303f, EPSILON)) {
printf("[ERROR] Final reg[21] mismatch: expected 0.00191965303, got %.8f\n", registers[21]);
       verification_errors++;
   } else {
       print_success("Final reg[21] matches: 0.00191965303");
   }

   total_checks++;
   if (!float_equal(registers[22], 0.817843974f, EPSILON)) {
printf("[ERROR] Final reg[22] mismatch: expected 0.817843974, got %.8f\n", registers[22]);
       verification_errors++;
   } else {
       print_success("Final reg[22] matches: 0.817843974");
   }

   total_checks++;
   if (!float_equal(registers[23], -0.000453432673f, EPSILON)) {
printf("[ERROR] Final reg[23] mismatch: expected -0.000453432673, got %.8f\n", registers[23]);
       verification_errors++;
   } else {
       print_success("Final reg[23] matches: -0.000453432673");
   }

   total_checks++;
   if (!float_equal(registers[24], -2.45218635f, EPSILON)) {
printf("[ERROR] Final reg[24] mismatch: expected -2.45218635, got %.8f\n", registers[24]);
       verification_errors++;
   } else {
       print_success("Final reg[24] matches: -2.45218635");
   }

   total_checks++;
   if (!float_equal(registers[25], -0.497876197f, EPSILON)) {
printf("[ERROR] Final reg[25] mismatch: expected -0.497876197, got %.8f\n", registers[25]);
       verification_errors++;
   } else {
       print_success("Final reg[25] matches: -0.497876197");
   }

   total_checks++;
   if (!float_equal(registers[26], 1.0f, EPSILON)) {
printf("[ERROR] Final reg[26] mismatch: expected 1.0, got %.8f\n", registers[26]);
       verification_errors++;
   } else {
       print_success("Final reg[26] matches: 1.0");
   }

   total_checks++;
   if (!float_equal(registers[27], 1.56303787f, EPSILON)) {
printf("[ERROR] Final reg[27] mismatch: expected 1.56303787, got %.8f\n", registers[27]);
       verification_errors++;
   } else {
       print_success("Final reg[27] matches: 1.56303787");
   }

   total_checks++;
   if (!float_equal(registers[28], 1.23070788f, EPSILON)) {
printf("[ERROR] Final reg[28] mismatch: expected 1.23070788, got %.8f\n", registers[28]);
       verification_errors++;
   } else {
       print_success("Final reg[28] matches: 1.23070788");
   }

   total_checks++;
   if (!float_equal(registers[29], 554.506409f, EPSILON)) {
printf("[ERROR] Final reg[29] mismatch: expected 554.506409, got %.8f\n", registers[29]);
       verification_errors++;
   } else {
       print_success("Final reg[29] matches: 554.506409");
   }

   total_checks++;
   if (!float_equal(registers[30], 26.5040817f, EPSILON)) {
printf("[ERROR] Final reg[30] mismatch: expected 26.5040817, got %.8f\n", registers[30]);
       verification_errors++;
   } else {
       print_success("Final reg[30] matches: 26.5040817");
   }

   total_checks++;
   if (!float_equal(registers[31], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[31] mismatch: expected 9.99999975e-05, got %.8f\n", registers[31]);
       verification_errors++;
   } else {
       print_success("Final reg[31] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[32], -509.521942f, EPSILON)) {
printf("[ERROR] Final reg[32] mismatch: expected -509.521942, got %.8f\n", registers[32]);
       verification_errors++;
   } else {
       print_success("Final reg[32] matches: -509.521942");
   }

   total_checks++;
   if (!float_equal(registers[33], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[33] mismatch: expected 9.99999975e-05, got %.8f\n", registers[33]);
       verification_errors++;
   } else {
       print_success("Final reg[33] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[34], 0.000122070312f, EPSILON)) {
printf("[ERROR] Final reg[34] mismatch: expected 0.000122070312, got %.8f\n", registers[34]);
       verification_errors++;
   } else {
       print_success("Final reg[34] matches: 0.000122070312");
   }

   total_checks++;
   if (!float_equal(registers[35], 0.78752619f, EPSILON)) {
printf("[ERROR] Final reg[35] mismatch: expected 0.78752619, got %.8f\n", registers[35]);
       verification_errors++;
   } else {
       print_success("Final reg[35] matches: 0.78752619");
   }

   total_checks++;
   if (!float_equal(registers[36], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[36] mismatch: expected 9.99999975e-05, got %.8f\n", registers[36]);
       verification_errors++;
   } else {
       print_success("Final reg[36] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[37], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[37] mismatch: expected 9.99999975e-05, got %.8f\n", registers[37]);
       verification_errors++;
   } else {
       print_success("Final reg[37] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[38], -128.157837f, EPSILON)) {
printf("[ERROR] Final reg[38] mismatch: expected -128.157837, got %.8f\n", registers[38]);
       verification_errors++;
   } else {
       print_success("Final reg[38] matches: -128.157837");
   }

   total_checks++;
   if (!float_equal(registers[39], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[39] mismatch: expected 9.99999975e-05, got %.8f\n", registers[39]);
       verification_errors++;
   } else {
       print_success("Final reg[39] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[40], -9.57099152f, EPSILON)) {
printf("[ERROR] Final reg[40] mismatch: expected -9.57099152, got %.8f\n", registers[40]);
       verification_errors++;
   } else {
       print_success("Final reg[40] matches: -9.57099152");
   }

   total_checks++;
   if (!float_equal(registers[41], 0.0219966993f, EPSILON)) {
printf("[ERROR] Final reg[41] mismatch: expected 0.0219966993, got %.8f\n", registers[41]);
       verification_errors++;
   } else {
       print_success("Final reg[41] matches: 0.0219966993");
   }

   total_checks++;
   if (!float_equal(registers[42], 0.0509747267f, EPSILON)) {
printf("[ERROR] Final reg[42] mismatch: expected 0.0509747267, got %.8f\n", registers[42]);
       verification_errors++;
   } else {
       print_success("Final reg[42] matches: 0.0509747267");
   }

   total_checks++;
   if (!float_equal(registers[43], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[43] mismatch: expected 9.99999975e-05, got %.8f\n", registers[43]);
       verification_errors++;
   } else {
       print_success("Final reg[43] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[44], 0.000130776549f, EPSILON)) {
printf("[ERROR] Final reg[44] mismatch: expected 0.000130776549, got %.8f\n", registers[44]);
       verification_errors++;
   } else {
       print_success("Final reg[44] matches: 0.000130776549");
   }

   total_checks++;
   if (!float_equal(registers[45], -405.493561f, EPSILON)) {
printf("[ERROR] Final reg[45] mismatch: expected -405.493561, got %.8f\n", registers[45]);
       verification_errors++;
   } else {
       print_success("Final reg[45] matches: -405.493561");
   }

   total_checks++;
   if (!float_equal(registers[46], -0.000808843062f, EPSILON)) {
printf("[ERROR] Final reg[46] mismatch: expected -0.000808843062, got %.8f\n", registers[46]);
       verification_errors++;
   } else {
       print_success("Final reg[46] matches: -0.000808843062");
   }

   total_checks++;
   if (!float_equal(registers[47], 0.0808939189f, EPSILON)) {
printf("[ERROR] Final reg[47] mismatch: expected 0.0808939189, got %.8f\n", registers[47]);
       verification_errors++;
   } else {
       print_success("Final reg[47] matches: 0.0808939189");
   }

   total_checks++;
   if (!float_equal(registers[48], -32.000103f, EPSILON)) {
printf("[ERROR] Final reg[48] mismatch: expected -32.000103, got %.8f\n", registers[48]);
       verification_errors++;
   } else {
       print_success("Final reg[48] matches: -32.000103");
   }

   total_checks++;
   if (!float_equal(registers[49], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[49] mismatch: expected 9.99999975e-05, got %.8f\n", registers[49]);
       verification_errors++;
   } else {
       print_success("Final reg[49] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[50], 192.624893f, EPSILON)) {
printf("[ERROR] Final reg[50] mismatch: expected 192.624893, got %.8f\n", registers[50]);
       verification_errors++;
   } else {
       print_success("Final reg[50] matches: 192.624893");
   }

   total_checks++;
   if (!float_equal(registers[51], -1.51726043f, EPSILON)) {
printf("[ERROR] Final reg[51] mismatch: expected -1.51726043, got %.8f\n", registers[51]);
       verification_errors++;
   } else {
       print_success("Final reg[51] matches: -1.51726043");
   }

   total_checks++;
   if (!float_equal(registers[52], -0.00196216744f, EPSILON)) {
printf("[ERROR] Final reg[52] mismatch: expected -0.00196216744, got %.8f\n", registers[52]);
       verification_errors++;
   } else {
       print_success("Final reg[52] matches: -0.00196216744");
   }

   total_checks++;
   if (!float_equal(registers[53], 1.56303787f, EPSILON)) {
printf("[ERROR] Final reg[53] mismatch: expected 1.56303787, got %.8f\n", registers[53]);
       verification_errors++;
   } else {
       print_success("Final reg[53] matches: 1.56303787");
   }

   total_checks++;
   if (!float_equal(registers[54], -7.9981451f, EPSILON)) {
printf("[ERROR] Final reg[54] mismatch: expected -7.9981451, got %.8f\n", registers[54]);
       verification_errors++;
   } else {
       print_success("Final reg[54] matches: -7.9981451");
   }

   total_checks++;
   if (!float_equal(registers[55], -119.903969f, EPSILON)) {
printf("[ERROR] Final reg[55] mismatch: expected -119.903969, got %.8f\n", registers[55]);
       verification_errors++;
   } else {
       print_success("Final reg[55] matches: -119.903969");
   }

   total_checks++;
   if (!float_equal(registers[56], 0.364717931f, EPSILON)) {
printf("[ERROR] Final reg[56] mismatch: expected 0.364717931, got %.8f\n", registers[56]);
       verification_errors++;
   } else {
       print_success("Final reg[56] matches: 0.364717931");
   }

   total_checks++;
   if (!float_equal(registers[57], 9.99999975e-05f, EPSILON)) {
printf("[ERROR] Final reg[57] mismatch: expected 9.99999975e-05, got %.8f\n", registers[57]);
       verification_errors++;
   } else {
       print_success("Final reg[57] matches: 9.99999975e-05");
   }

   total_checks++;
   if (!float_equal(registers[58], 0.248461053f, EPSILON)) {
printf("[ERROR] Final reg[58] mismatch: expected 0.248461053, got %.8f\n", registers[58]);
       verification_errors++;
   } else {
       print_success("Final reg[58] matches: 0.248461053");
   }

   total_checks++;
   if (!float_equal(registers[59], -0.00325541198f, EPSILON)) {
printf("[ERROR] Final reg[59] mismatch: expected -0.00325541198, got %.8f\n", registers[59]);
       verification_errors++;
   } else {
       print_success("Final reg[59] matches: -0.00325541198");
   }

   total_checks++;
   if (!float_equal(registers[60], -2.89643407f, EPSILON)) {
printf("[ERROR] Final reg[60] mismatch: expected -2.89643407, got %.8f\n", registers[60]);
       verification_errors++;
   } else {
       print_success("Final reg[60] matches: -2.89643407");
   }

   total_checks++;
   if (!float_equal(registers[61], -0.73126936f, EPSILON)) {
printf("[ERROR] Final reg[61] mismatch: expected -0.73126936, got %.8f\n", registers[61]);
       verification_errors++;
   } else {
       print_success("Final reg[61] matches: -0.73126936");
   }

   total_checks++;
   if (!float_equal(registers[62], -193.418381f, EPSILON)) {
printf("[ERROR] Final reg[62] mismatch: expected -193.418381, got %.8f\n", registers[62]);
       verification_errors++;
   } else {
       print_success("Final reg[62] matches: -193.418381");
   }

   total_checks++;
   if (!float_equal(registers[63], 0.00854635146f, EPSILON)) {
printf("[ERROR] Final reg[63] mismatch: expected 0.00854635146, got %.8f\n", registers[63]);
       verification_errors++;
   } else {
       print_success("Final reg[63] matches: 0.00854635146");
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
