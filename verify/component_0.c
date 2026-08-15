#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r1 = 0x1.87aba4p+0f;
    assert(r1 == 0x1.87aba4p+0f);

    /* node 1: INIT */
    float r13 = -0x1.03cp-13f;
    assert(r13 == -0x1.03cp-13f);

    /* node 2: INIT */
    float r7 = 0x1.ffd044p-13f;
    assert(r7 == 0x1.ffd044p-13f);

    /* node 3: INIT */
    float r16 = -0x1.56a66p+1f;
    assert(r16 == -0x1.56a66p+1f);

    /* node 4: INIT */
    float r4 = 0x1.6e6f2ap+1f;
    assert(r4 == 0x1.6e6f2ap+1f);

    /* node 5: INIT */
    float r3 = 0x1.a36e2ep-14f;
    assert(r3 == 0x1.a36e2ep-14f);

    /* node 6: INIT */
    float r8 = -0x1.8a2b16p+0f;
    assert(r8 == -0x1.8a2b16p+0f);

    /* node 7: SUB */
    float r2 = r8 - r16;
    assert(r2 == 0x1.2321aap+0f);

    /* node 8: ADD */
    float r14 = r16 + r2;
    assert(r14 == -0x1.8a2b16p+0f);

    /* node 9: ADD */
    float r6 = r2 + r4;
    assert(r6 == 0x1p+2f);

    /* node 10: DIV */
    float r12 = r8 / r1;
    assert(r12 == -0x1.01a1f2p+0f);

    /* node 11: DIV */
    float r5 = r1 / r12;
    assert(r5 == -0x1.85304p+0f);

    /* node 12: MUL */
    float r19 = r5 * r7;
    assert(r19 == -0x1.850bf8p-12f);

    /* node 13: DIV */
    float r18 = r12 / r14;
    assert(r18 == 0x1.4ea60ep-1f);

    /* node 14: ADD */
    float r11 = r1 + r18;
    assert(r11 == 0x1.177f56p+1f);

    /* node 15: ADD */
    float r15 = r1 + r11;
    assert(r15 == 0x1.db5528p+1f);

    /* node 16: SUB */
    float r17 = r8 - r13;
    assert(r17 == -0x1.8a22f8p+0f);

    /* node 17: MUL */
    float r0 = r16 * r17;
    assert(r0 == 0x1.07c56ep+2f);

    /* node 18: ADD */
    float r10 = r8 + r0;
    assert(r10 == 0x1.4a755p+1f);

    /* node 19: DIV */
    float r9 = r1 / r12;
    assert(r9 == -0x1.85304p+0f);

    printf("OK: all 20 nodes verified\n");
    return 0;
}
