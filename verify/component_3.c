#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r2 = 0x1.d3fc0ap-2f;
    assert(r2 == 0x1.d3fc0ap-2f);

    /* node 1: INIT */
    float r18 = -0x1.d852d6p-2f;
    assert(r18 == -0x1.d852d6p-2f);

    /* node 2: INIT */
    float r0 = 0x1.1a3d4ep-2f;
    assert(r0 == 0x1.1a3d4ep-2f);

    /* node 3: INIT */
    float r3 = 0x1.60cbc4p-5f;
    assert(r3 == 0x1.60cbc4p-5f);

    /* node 4: ADD */
    float r1 = r2 + r3;
    assert(r1 == 0x1.000ac2p-1f);

    /* node 5: MUL */
    float r6 = r2 * r1;
    assert(r6 == 0x1.d40fb4p-3f);

    /* node 6: DIV */
    float r4 = r2 / r3;
    assert(r4 == 0x1.81fa42p-4f);

    /* node 7: DIV */
    float r8 = r3 / r4;
    assert(r8 == 0x1.d3fc0ap-2f);

    /* node 8: SUB */
    float r14 = r1 - r8;
    assert(r14 == -0x1.60cbdp-5f);

    /* node 9: ADD */
    float r7 = r18 + r14;
    assert(r7 == -0x1.023628p-1f);

    /* node 10: ADD */
    float r10 = r2 + r4;
    assert(r10 == 0x1.1a3d4ep-1f);

    /* node 11: DIV */
    float r15 = r0 / r10;
    assert(r15 == 0x1p-1f);

    /* node 12: DIV */
    float r5 = r18 / r4;
    assert(r5 == -0x1.a26694p-3f);

    /* node 13: SUB */
    float r13 = r6 - r5;
    assert(r13 == 0x1.bb3b24p-2f);

    /* node 14: SUB */
    float r11 = r3 - r8;
    assert(r11 == -0x1.a7e292p-2f);

    /* node 15: DIV */
    float r16 = r4 / r11;
    assert(r16 == -0x1.d23668p-3f);

    /* node 16: MUL */
    float r17 = r14 * r16;
    assert(r17 == 0x1.413efep-7f);

    /* node 17: SUB */
    float r19 = r18 - r11;
    assert(r19 == 0x1.83822p-5f);

    /* node 18: ADD */
    float r12 = r18 + r19;
    assert(r12 == -0x1.a7e292p-2f);

    /* node 19: SUB */
    float r9 = r16 - r19;
    assert(r9 == 0x1.198b78p-2f);

    printf("OK: all 20 nodes verified\n");
    return 0;
}
