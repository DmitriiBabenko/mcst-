#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r3 = 0.960963905f;
    assert(r3 == 0.960963905f);

    /* node 1: INIT */
    float r0 = 2.04518795f;
    assert(r0 == 2.04518795f);

    /* node 2: INIT */
    float r32 = -3.01196909f;
    assert(r32 == -3.01196909f);

    /* node 3: INIT */
    float r28 = 0.00146496086f;
    assert(r28 == 0.00146496086f);

    /* node 4: INIT */
    float r4 = 2.98254657f;
    assert(r4 == 2.98254657f);

    /* node 5: INIT */
    float r11 = 0.143075988f;
    assert(r11 == 0.143075988f);

    /* node 6: INIT */
    float r10 = -5.00151014f;
    assert(r10 == -5.00151014f);

    /* node 7: INIT */
    float r12 = 1.89792943f;
    assert(r12 == 1.89792943f);

    /* node 8: INIT */
    float r2 = 371.050049f;
    assert(r2 == 371.050049f);

    /* node 9: INIT */
    float r13 = 0.00052486558f;
    assert(r13 == 0.00052486558f);

    /* node 10: MUL */
    float r16 = r13 * r10;
    assert(r16 == -0.00262512057f);

    /* node 11: SUB */
    float r5 = r16 - r10;
    assert(r5 == 4.99888515f);

    /* node 12: INIT */
    float r19 = 0.000851025514f;
    assert(r19 == 0.000851025514f);

    /* node 13: DIV */
    float r24 = r12 / r3;
    assert(r24 == 1.97502673f);

    /* node 14: INIT */
    float r26 = -0.000259221619f;
    assert(r26 == -0.000259221619f);

    /* node 15: ADD */
    float r9 = r26 + r12;
    assert(r9 == 1.89767015f);

    /* node 16: ADD */
    float r14 = r9 + r12;
    assert(r14 == 3.79559946f);

    /* node 17: DIV */
    float r17 = r26 / r9;
    assert(r17 == -0.000136599934f);

    /* node 18: DIV */
    float r6 = r13 / r10;
    assert(r6 == -0.00010494142f);

    /* node 19: DIV */
    float r20 = r19 / r11;
    assert(r20 == 0.00594806671f);

    /* node 20: SUB */
    float r30 = r20 - r19;
    assert(r30 == 0.00509704137f);

    /* node 21: MUL */
    float r34 = r30 * r2;
    assert(r34 == 1.89125741f);

    /* node 22: SUB */
    float r15 = r2 - r34;
    assert(r15 == 369.158783f);

    /* node 23: MUL */
    float r7 = r34 * r0;
    assert(r7 == 3.8679769f);

    /* node 24: DIV */
    float r25 = r4 / r32;
    assert(r25 == -0.990231454f);

    /* node 25: INIT */
    float r8 = -0.749999762f;
    assert(r8 == -0.749999762f);

    /* node 26: ADD */
    float r31 = r28 + r8;
    assert(r31 == -0.748534799f);

    /* node 27: ADD */
    float r27 = r31 + r28;
    assert(r27 == -0.747069836f);

    /* node 28: DIV */
    float r22 = r28 / r8;
    assert(r22 == -0.0019532817f);

    /* node 29: ADD */
    float r23 = r31 + r22;
    assert(r23 == -0.750488102f);

    /* node 30: SUB */
    float r1 = r22 - r28;
    assert(r1 == -0.00341824256f);

    /* node 31: DIV */
    float r33 = r1 / r28;
    assert(r33 == -2.33333373f);

    /* node 32: MUL */
    float r18 = r33 * r31;
    assert(r18 == 1.74658144f);

    /* node 33: ADD */
    float r29 = r33 + r18;
    assert(r29 == -0.586752295f);

    /* node 34: MUL */
    float r21 = r7 * r0;
    assert(r21 == 7.9107399f);

    /* node 35: INIT */
    r16 = -127.915939f;
    assert(r16 == -127.915939f);

    /* node 36: MUL */
    r5 = r13 * r16;
    assert(r5 == -0.0671386719f);

    /* node 37: SUB */
    r3 = r16 - r5;
    assert(r3 == -127.848801f);

    /* node 38: ADD */
    r24 = r4 + r32;
    assert(r24 == -0.0294225216f);

    /* node 39: MUL */
    r26 = r24 * r25;
    assert(r26 == 0.0291351061f);

    /* node 40: MUL */
    r14 = r4 * r24;
    assert(r14 == -0.087754041f);

    /* node 41: SUB */
    r17 = r14 - r32;
    assert(r17 == 2.92421508f);

    /* node 42: SUB */
    r11 = r25 - r24;
    assert(r11 == -0.960808933f);

    /* node 43: SUB */
    r6 = r25 - r11;
    assert(r6 == -0.0294225216f);

    /* node 44: SUB */
    r19 = r24 - r11;
    assert(r19 == 0.931386411f);

    /* node 45: INIT */
    r20 = 1.51696587f;
    assert(r20 == 1.51696587f);

    /* node 46: MUL */
    r30 = r9 * r20;
    assert(r30 == 2.87870073f);

    /* node 47: DIV */
    r2 = r12 / r30;
    assert(r2 == 0.659300685f);

    /* node 48: MUL */
    r34 = r5 * r16;
    assert(r34 == 8.58810616f);

    /* node 49: SUB */
    r15 = r10 - r13;
    assert(r15 == -5.00203514f);

    printf("OK: all 50 nodes verified\n");
    return 0;
}
