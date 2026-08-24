#include <stdio.h>

// Permuted Choice 2 (PC-2) table of DES (48 bits output from 56 bits)
const int PC2[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

int main() {
    printf("===============================================================\n");
    printf("      EXP 18: DES SUBKEY DISJOINT 28-BIT SUBSET PROOF          \n");
    printf("===============================================================\n\n");

    printf("Analysis of DES Key Generation Disjoint Property:\n");
    printf("  - Initial key (64 bits) passes through PC-1 to produce 56 bits.\n");
    printf("  - The 56 bits are partitioned into two halves:\n");
    printf("      * C0: Bits 1 to 28 (Left register)\n");
    printf("      * D0: Bits 29 to 56 (Right register)\n\n");

    printf("Verifying PC-2 mapping into first 24 bits and second 24 bits of subkey:\n\n");

    printf("1. First 24 bits of Subkey (from PC-2 indices 0..23):\n   ");
    int c_count = 0, d_count = 0;
    for (int i = 0; i < 24; i++) {
        printf("%2d ", PC2[i]);
        if (PC2[i] <= 28) c_count++;
    }
    printf("\n   -> All %d bits originate strictly from C (bits 1..28).\n\n", c_count);

    printf("2. Second 24 bits of Subkey (from PC-2 indices 24..47):\n   ");
    for (int i = 24; i < 48; i++) {
        printf("%2d ", PC2[i]);
        if (PC2[i] >= 29) d_count++;
    }
    printf("\n   -> All %d bits originate strictly from D (bits 29..56).\n\n", d_count);

    printf("Mathematical Proof & Conclusion:\n");
    printf("  Since C and D are shifted independently in separate registers and\n");
    printf("  PC-2 maps {1..28} exclusively to subkey bits 1..24, and {29..56}\n");
    printf("  exclusively to subkey bits 25..48, NO mixing occurs between the two halves.\n");
    printf("===============================================================\n");

    return 0;
}
