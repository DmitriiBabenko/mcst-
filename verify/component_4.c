#include <stdio.h>
#include <assert.h>
int main(void) {
    /* node 0: INIT */
    float r1 = 0x1.b6b19ep+2f;
    assert(r1 == 0x1.b6b19ep+2f);

    /* node 1: INIT */
    float r6 = 0x1.00001p+1f;
    assert(r6 == 0x1.00001p+1f);

    /* node 2: INIT */
    float r5 = 0x1.e01b22p+1f;
    assert(r5 == 0x1.e01b22p+1f);

    /* node 3: INIT */
    float r14 = 0x1.f72a6ap+2f;
    assert(r14 == 0x1.f72a6ap+2f);

    /* node 4: INIT */
    float r16 = -0x1p+9f;
    assert(r16 == -0x1p+9f);

    /* node 5: INIT */
    float r7 = -0x1.a36e2ep-14f;
    assert(r7 == -0x1.a36e2ep-14f);

    /* node 6: INIT */
    float r15 = 0x1.5101eep+1f;
    assert(r15 == 0x1.5101eep+1f);

    /* node 7: ADD */
    float r19 = r5 + r15;
    assert(r19 == 0x1.988e88p+2f);

    /* node 8: SUB */
    float r8 = r14 - r19;
    assert(r8 == -0x1.7a6f88p+0f);

    /* node 9: ADD */
    float r11 = r15 + r19;
    assert(r11 == 0x1.2087cp+3f);

    /* node 10: DIV */
    float r2 = r19 / r8;
    assert(r2 == -0x1.14604p+2f);

    /* node 11: SUB */
    float r17 = r5 - r15;
    assert(r17 == -0x1.1e3268p+0f);

    /* node 12: DIV */
    float r13 = r15 / r19;
    assert(r13 == 0x1.a655c8p-2f);

    /* node 13: INIT */
    float r4 = -0x1.323036p-6f;
    assert(r4 == -0x1.323036p-6f);

    /* node 14: DIV */
    float r18 = r14 / r4;
    assert(r18 == -0x1.a4b0aep+8f);

    /* node 15: ADD */
    float r3 = r19 + r18;
    assert(r3 == -0x1.9e4e74p+8f);

    /* node 16: SUB */
    float r10 = r5 - r3;
    assert(r10 == 0x1.a20eaap+8f);

    /* node 17: MUL */
    float r12 = r8 * r4;
    assert(r12 == 0x1.c4a096p-6f);

    /* node 18: DIV */
    float r0 = r5 / r11;
    assert(r0 == 0x1.a9fap-2f);

    /* node 19: MUL */
    float r9 = r1 * r0;
    assert(r9 == 0x1.6cfca4p+1f);

    printf("OK: all 20 nodes verified\n");
    return 0;
}
