#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r16 = 0x1.fdffcep-4f;
    assert(r16 == 0x1.fdffcep-4f);

    /* node 1: INIT */
    float r13 = -0x1.ff8686p-12f;
    assert(r13 == -0x1.ff8686p-12f);

    /* node 2: INIT */
    float r6 = 0x1.a36c2p+2f;
    assert(r6 == 0x1.a36c2p+2f);

    /* node 3: INIT */
    float r5 = -0x1.02884p-3f;
    assert(r5 == -0x1.02884p-3f);

    /* node 4: ADD */
    float r15 = r5 + r16;
    assert(r15 == -0x1.c42c8p-10f);

    /* node 5: SUB */
    float r7 = r16 - r15;
    assert(r7 == 0x1.02884p-3f);

    /* node 6: SUB */
    float r9 = r15 - r13;
    assert(r9 == -0x1.444adep-10f);

    /* node 7: SUB */
    float r11 = r15 - r13;
    assert(r11 == -0x1.444adep-10f);

    /* node 8: ADD */
    float r17 = r7 + r11;
    assert(r17 == 0x1.ffff54p-4f);

    /* node 9: MUL */
    float r1 = r5 * r17;
    assert(r1 == -0x1.0287eap-6f);

    /* node 10: MUL */
    float r3 = r16 * r1;
    assert(r3 == -0x1.018548p-9f);

    /* node 11: MUL */
    float r19 = r7 * r17;
    assert(r19 == 0x1.0287eap-6f);

    /* node 12: DIV */
    float r0 = r3 / r19;
    assert(r0 == -0x1.fdffccp-4f);

    /* node 13: ADD */
    float r14 = r17 + r19;
    assert(r14 == 0x1.2050a8p-3f);

    /* node 14: ADD */
    float r2 = r5 + r11;
    assert(r2 == -0x1.0510d6p-3f);

    /* node 15: ADD */
    float r18 = r2 + r3;
    assert(r18 == -0x1.0916ecp-3f);

    /* node 16: ADD */
    float r10 = r15 + r3;
    assert(r10 == -0x1.e39b88p-9f);

    /* node 17: SUB */
    float r4 = r5 - r15;
    assert(r4 == -0x1.fdffcep-4f);

    /* node 18: MUL */
    float r12 = r15 * r17;
    assert(r12 == -0x1.c42be8p-13f);

    /* node 19: SUB */
    float r8 = r17 - r12;
    assert(r8 == 0x1.0070b4p-3f);

    printf("OK: all 20 nodes verified\n");
    return 0;
}
