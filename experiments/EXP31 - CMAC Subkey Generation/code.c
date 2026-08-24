#include <stdio.h>
#include <stdint.h>

// Rb constants defined in NIST SP 800-38B (CMAC)
#define CONST_Rb_64  0x000000000000001BULL  // x^8 + x^4 + x^3 + x + 1 (for 64-bit block)
#define CONST_Rb_128 0x87                   // x^7 + x^4 + x + 1 (for 128-bit block)

// 64-bit CMAC Subkey Generation
void generateSubkeys64(uint64_t L, uint64_t *K1, uint64_t *K2) {
    // K1 = (L << 1) ^ (MSB(L) ? Rb_64 : 0)
    if ((L >> 63) & 1) {
        *K1 = (L << 1) ^ CONST_Rb_64;
    } else {
        *K1 = (L << 1);
    }

    // K2 = (K1 << 1) ^ (MSB(K1) ? Rb_64 : 0)
    if ((*K1 >> 63) & 1) {
        *K2 = (*K1 << 1) ^ CONST_Rb_64;
    } else {
        *K2 = (*K1 << 1);
    }
}

int main() {
    printf("===============================================================\n");
    printf("           EXP 31: CMAC SUBKEY GENERATION ALGORITHM            \n");
    printf("===============================================================\n\n");

    printf("a. Constants (Rb) Needed for Block Sizes:\n");
    printf("   - 64-bit block cipher (e.g. 3DES): Rb = 0x1B (binary: 0001 1011)\n");
    printf("     Polynomial: x^64 + x^4 + x^3 + x + 1\n");
    printf("   - 128-bit block cipher (e.g. AES):  Rb = 0x87 (binary: 1000 0111)\n");
    printf("     Polynomial: x^128 + x^7 + x^4 + x + 1\n\n");

    printf("b. Mathematical Explanation of Left Shift and XOR:\n");
    printf("   - Multiplying a polynomial by 'x' in GF(2^n) corresponds to a\n");
    printf("     1-bit left shift (multiplication by 2).\n");
    printf("   - If the most significant bit (MSB) before shift was 1 (overflowing x^n),\n");
    printf("     modulo reduction by the irreducible polynomial is performed via XOR with Rb.\n\n");

    // Demonstration with 64-bit block cipher
    uint64_t L = 0x8B7C3E1F5A29D460ULL; // Example L = E_K(0)
    uint64_t K1, K2;

    generateSubkeys64(L, &K1, &K2);

    printf("64-Bit Demonstration:\n");
    printf("  L  = E_K(0^64) = 0x%016llX (MSB = %d)\n", L, (int)((L >> 63) & 1));
    printf("  K1             = 0x%016llX (MSB = %d)\n", K1, (int)((K1 >> 63) & 1));
    printf("  K2             = 0x%016llX\n\n", K2);

    printf("===============================================================\n");

    return 0;
}
