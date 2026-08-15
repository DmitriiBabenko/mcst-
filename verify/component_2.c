#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r19 = -0x1.5e82a8p+4f;
    assert(r19 == -0x1.5e82a8p+4f);

    /* node 1: INIT */
    float r2 = 0x1.00707cp+6f;
    assert(r2 == 0x1.00707cp+6f);

    /* node 2: INIT */
    float r17 = -0x1.66ef5ep-12f;
    assert(r17 == -0x1.66ef5ep-12f);

    /* node 3: MUL */
    float r14 = r19 * r17;
    assert(r14 == 0x1.eb7274p-8f);

    /* node 4: SUB */
    float r10 = r17 - r14;
    assert(r10 == -0x1.00f0b4p-7f);

    /* node 5: DIV */
    float r11 = r14 / r10;
    assert(r11 == -0x1.e9a61p-1f);

    /* node 6: DIV */
    float r8 = r2 / r11;
    assert(r8 == -0x1.e8cf48p-7f);

    /* node 7: ADD */
    float r6 = r19 + r14;
    assert(r6 == -0x1.5e63fp+4f);

    /* node 8: SUB */
    float r15 = r19 - r17;
    assert(r15 == 0x1.5e8142p+4f);

    /* node 9: MUL */
    float r5 = r11 * r15;
    assert(r5 == -0x1.4f3422p+4f);

    /* node 10: DIV */
    float r12 = r17 / r11;
    assert(r12 == 0x1.7751dp-12f);

    /* node 11: ADD */
    float r3 = r17 + r14;
    assert(r3 == 0x1.d5037ep-8f);

    /* node 12: ADD */
    float r9 = r15 + r3;
    assert(r9 == 0x1.5e9e92p+4f);

    /* node 13: DIV */
    float r0 = r2 / r3;
    assert(r0 == 0x1.d435c4p-14f);

    /* node 14: MUL */
    float r7 = r15 * r0;
    assert(r7 == 0x1.4086f4p-9f);

    /* node 15: SUB */
    float r16 = r17 - r11;
    assert(r16 == 0x1.e97932p-1f);

    /* node 16: SUB */
    float r4 = r14 - r16;
    assert(r4 == -0x1.e5a24ep-1f);

    /* node 17: DIV */
    float r18 = r2 / r16;
    assert(r18 == 0x1.0c3dc4p+6f);

    /* node 18: MUL */
    float r13 = r14 * r18;
    assert(r13 == 0x1.017932p-1f);

    /* node 19: ADD */
    float r1 = r2 + r14;
    assert(r1 == 0x1.00782ap+6f);

    printf("OK: all 20 nodes verified\n");
    return 0;
}
