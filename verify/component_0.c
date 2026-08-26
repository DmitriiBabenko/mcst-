#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r3 = 1.7736659f;
    assert(r3 == 1.7736659f);

    /* node 1: INIT */
    float r0 = 129.162842f;
    assert(r0 == 129.162842f);

    /* node 2: INIT */
    float r32 = -0.0811018646f;
    assert(r32 == -0.0811018646f);

    /* node 3: INIT */
    float r28 = 0.000213678737f;
    assert(r28 == 0.000213678737f);

    /* node 4: INIT */
    float r4 = 0.718994379f;
    assert(r4 == 0.718994379f);

    /* node 5: INIT */
    float r11 = 257.726288f;
    assert(r11 == 257.726288f);

    /* node 6: INIT */
    float r10 = 0.0153047582f;
    assert(r10 == 0.0153047582f);

    /* node 7: INIT */
    float r12 = 0.712662578f;
    assert(r12 == 0.712662578f);

    /* node 8: INIT */
    float r2 = 0.00365118217f;
    assert(r2 == 0.00365118217f);

    /* node 9: INIT */
    float r13 = 196.312531f;
    assert(r13 == 196.312531f);

    /* node 10: INIT */
    float r16 = -126.138931f;
    assert(r16 == -126.138931f);

    /* node 11: INIT */
    float r5 = 0.225321278f;
    assert(r5 == 0.225321278f);

    /* node 12: INIT */
    float r19 = 0.00282742572f;
    assert(r19 == 0.00282742572f);

    /* node 13: INIT */
    float r24 = 2.82574391f;
    assert(r24 == 2.82574391f);

    /* node 14: INIT */
    float r26 = -0.380918831f;
    assert(r26 == -0.380918831f);

    /* node 15: INIT */
    float r9 = 127.1875f;
    assert(r9 == 127.1875f);

    /* node 16: INIT */
    float r14 = 0.000464164012f;
    assert(r14 == 0.000464164012f);

    /* node 17: INIT */
    float r17 = -400.406494f;
    assert(r17 == -400.406494f);

    /* node 18: DIV */
    float r6 = r19 / r2;
    assert(r6 == 0.774386346f);

    /* node 19: INIT */
    float r20 = 0.00010047113f;
    assert(r20 == 0.00010047113f);

    /* node 20: INIT */
    float r30 = -0.000576074992f;
    assert(r30 == -0.000576074992f);

    /* node 21: ADD */
    float r34 = r28 + r30;
    assert(r34 == -0.00036239624f);

    /* node 22: INIT */
    float r15 = -0.000811821548f;
    assert(r15 == -0.000811821548f);

    /* node 23: INIT */
    float r7 = -28.9117374f;
    assert(r7 == -28.9117374f);

    /* node 24: INIT */
    float r25 = 0.000487654062f;
    assert(r25 == 0.000487654062f);

    /* node 25: SUB */
    float r8 = r34 - r25;
    assert(r8 == -0.000850050303f);

    /* node 26: INIT */
    float r31 = -0.00700897677f;
    assert(r31 == -0.00700897677f);

    /* node 27: INIT */
    float r27 = -0.0312257931f;
    assert(r27 == -0.0312257931f);

    /* node 28: INIT */
    float r22 = 8.01569176f;
    assert(r22 == 8.01569176f);

    /* node 29: DIV */
    float r23 = r22 / r12;
    assert(r23 == 11.2475271f);

    /* node 30: INIT */
    float r1 = -22.1890011f;
    assert(r1 == -22.1890011f);

    /* node 31: INIT */
    float r33 = -0.0351741947f;
    assert(r33 == -0.0351741947f);

    /* node 32: DIV */
    float r18 = r6 / r33;
    assert(r18 == -22.0157528f);

    /* node 33: ADD */
    float r29 = r6 + r33;
    assert(r29 == 0.739212155f);

    /* node 34: INIT */
    float r21 = 0.410211563f;
    assert(r21 == 0.410211563f);

    /* node 35: INIT */
    r28 = -1.66891921f;
    assert(r28 == -1.66891921f);

    /* node 36: DIV */
    r30 = r19 / r2;
    assert(r30 == 0.774386346f);

    /* node 37: MUL */
    r12 = r30 * r2;
    assert(r12 == 0.00282742572f);

    /* node 38: ADD */
    r6 = r0 + r16;
    assert(r6 == 3.02391052f);

    /* node 39: SUB */
    r12 = r25 - r6;
    assert(r12 == -3.02342296f);

    /* node 40: MUL */
    r25 = r16 * r6;
    assert(r25 == -381.432831f);

    /* node 41: SUB */
    r6 = r16 - r25;
    assert(r6 == 255.2939f);

    /* node 42: INIT */
    r12 = 0.802578986f;
    assert(r12 == 0.802578986f);

    /* node 43: MUL */
    r16 = r12 * r32;
    assert(r16 == -0.0650906488f);

    /* node 44: DIV */
    r6 = r32 / r16;
    assert(r6 == 1.24598336f);

    /* node 45: MUL */
    r15 = r12 * r15;
    assert(r15 == -0.000651550887f);

    /* node 46: SUB */
    r12 = r15 - r16;
    assert(r12 == 0.0644390956f);

    /* node 47: ADD */
    r6 = r15 + r7;
    assert(r6 == -28.9123898f);

    /* node 48: DIV */
    r16 = r6 / r32;
    assert(r16 == 356.494751f);

    /* node 49: MUL */
    r7 = r5 * r16;
    assert(r7 == 80.3258514f);

    /* node 50: DIV */
    r15 = r16 / r22;
    assert(r15 == 44.4746094f);

    /* node 51: ADD */
    r12 = r16 + r6;
    assert(r12 == 327.582367f);

    /* node 52: MUL */
    r32 = r11 * r10;
    assert(r32 == 3.94443846f);

    /* node 53: INIT */
    r22 = -32.9282341f;
    assert(r22 == -32.9282341f);

    /* node 54: DIV */
    r7 = r28 / r22;
    assert(r7 == 0.0506835319f);

    /* node 55: INIT */
    r16 = 0.00722481543f;
    assert(r16 == 0.00722481543f);

    /* node 56: INIT */
    r15 = 286.809753f;
    assert(r15 == 286.809753f);

    /* node 57: DIV */
    r10 = r15 / r3;
    assert(r10 == 161.704498f);

    /* node 58: DIV */
    r12 = r18 / r1;
    assert(r12 == 0.992192149f);

    /* node 59: INIT */
    r32 = 315.68045f;
    assert(r32 == 315.68045f);

    /* node 60: SUB */
    r22 = r30 - r28;
    assert(r22 == 2.44330549f);

    /* node 61: MUL */
    r7 = r3 * r24;
    assert(r7 == 5.0119257f);

    /* node 62: INIT */
    r18 = -0.000100199672f;
    assert(r18 == -0.000100199672f);

    /* node 63: DIV */
    r10 = r29 / r30;
    assert(r10 == 0.954577982f);

    /* node 64: MUL */
    r12 = r10 * r33;
    assert(r12 == -0.0335765108f);

    /* node 65: INIT */
    r28 = 0.0158843566f;
    assert(r28 == 0.0158843566f);

    /* node 66: ADD */
    r3 = r27 + r28;
    assert(r3 == -0.0153414365f);

    /* node 67: DIV */
    r7 = r3 / r14;
    assert(r7 == -33.0517578f);

    /* node 68: MUL */
    r29 = r22 * r2;
    assert(r29 == 0.00892095361f);

    /* node 69: INIT */
    r30 = 289.993103f;
    assert(r30 == 289.993103f);

    /* node 70: ADD */
    r33 = r30 + r17;
    assert(r33 == -110.413391f);

    /* node 71: SUB */
    r10 = r30 - r15;
    assert(r10 == 3.18334961f);

    /* node 72: SUB */
    r12 = r10 - r9;
    assert(r12 == -124.00415f);

    /* node 73: MUL */
    r28 = r25 * r8;
    assert(r28 == 0.324237078f);

    /* node 74: MUL */
    r14 = r1 * r26;
    assert(r14 == 8.45220852f);

    /* node 75: SUB */
    r22 = r2 - r19;
    assert(r22 == 0.000823756447f);

    /* node 76: ADD */
    r7 = r32 + r13;
    assert(r7 == 511.992981f);

    /* node 77: SUB */
    r29 = r7 - r31;
    assert(r29 == 512.0f);

    /* node 78: MUL */
    r17 = r4 * r29;
    assert(r17 == 368.125122f);

    /* node 79: DIV */
    r15 = r32 / r29;
    assert(r15 == 0.61656338f);

    /* node 80: SUB */
    r33 = r18 - r20;
    assert(r33 == -0.000200670795f);

    /* node 81: MUL */
    r9 = r34 * r28;
    assert(r9 == -0.000117502299f);

    /* node 82: SUB */
    r8 = r3 - r20;
    assert(r8 == -0.0154419076f);

    /* node 83: ADD */
    r25 = r6 + r21;
    assert(r25 == -28.5021782f);

    /* node 84: MUL */
    r12 = r23 * r5;
    assert(r12 == 2.53430724f);

    /* node 85: INIT */
    r26 = -129.086044f;
    assert(r26 == -129.086044f);

    /* node 86: SUB */
    r1 = r26 - r0;
    assert(r1 == -258.248901f);

    /* node 87: DIV */
    r2 = r1 / r11;
    assert(r2 == -1.00202775f);

    /* node 88: DIV */
    r19 = r26 / r0;
    assert(r19 == -0.999405444f);

    /* node 89: INIT */
    r14 = 0.883044064f;
    assert(r14 == 0.883044064f);

    /* node 90: MUL */
    r13 = r14 * r30;
    assert(r13 == 256.076691f);

    /* node 91: MUL */
    r22 = r14 * r24;
    assert(r22 == 2.49525642f);

    /* node 92: SUB */
    r31 = r24 - r22;
    assert(r31 == 0.33048749f);

    /* node 93: DIV */
    r7 = r14 / r16;
    assert(r7 == 122.223755f);

    /* node 94: MUL */
    r32 = r7 * r16;
    assert(r32 == 0.883044064f);

    /* node 95: SUB */
    r29 = r24 - r14;
    assert(r29 == 1.94269991f);

    /* node 96: DIV */
    r17 = r10 / r14;
    assert(r17 == 3.6049726f);

    /* node 97: INIT */
    r18 = 0.0449370518f;
    assert(r18 == 0.0449370518f);

    /* node 98: DIV */
    r15 = r18 / r4;
    assert(r15 == 0.0624998659f);

    /* node 99: MUL */
    r34 = r27 * r18;
    assert(r34 == -0.00140319509f);

    printf("OK: all 100 nodes verified\n");
    return 0;
}
