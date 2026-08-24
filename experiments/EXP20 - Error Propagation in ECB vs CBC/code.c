#include <stdio.h>
#include <stdint.h>

// Mock block cipher encryption / decryption
uint32_t encryptBlock(uint32_t p, uint32_t k) {
    return (p * 0x45D9F3B + k) ^ 0x9E3779B9;
}

uint32_t decryptBlock(uint32_t c, uint32_t k) {
    uint32_t t = c ^ 0x9E3779B9;
    t -= k;
    return t * 0x119DE1F; // modular inverse of 0x45D9F3B modulo 2^32
}

int main() {
    printf("===============================================================\n");
    printf("     EXP 20: ERROR PROPAGATION IN ECB VS CBC MODES             \n");
    printf("===============================================================\n\n");

    uint32_t key = 0x12345678;
    uint32_t iv = 0xAABBCCDD;
    uint32_t P[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444444};
    uint32_t C[4], Dec[4];

    // CBC Encryption
    uint32_t prev = iv;
    for (int i = 0; i < 4; i++) {
        C[i] = encryptBlock(P[i] ^ prev, key);
        prev = C[i];
    }

    printf("1. Normal CBC Encryption:\n");
    for (int i = 0; i < 4; i++) {
        printf("  P[%d] = 0x%08X  -->  C[%d] = 0x%08X\n", i + 1, P[i], i + 1, C[i]);
    }

    // Simulate bit flip in transmitted C1 (e.g. flip bit 0)
    printf("\n2. Transmission Bit Error introduced in C1 (0x%08X -> 0x%08X):\n", C[0], C[0] ^ 1);
    C[0] ^= 1; // 1-bit error in C1

    // CBC Decryption with corrupted C1
    prev = iv;
    for (int i = 0; i < 4; i++) {
        Dec[i] = decryptBlock(C[i], key) ^ prev;
        prev = C[i];
    }

    printf("  Decrypted Plaintext at Receiver:\n");
    for (int i = 0; i < 4; i++) {
        printf("  Dec[P%d] = 0x%08X %s\n", 
               i + 1, Dec[i], (Dec[i] == P[i]) ? "[OK - Correct]" : "[ERROR - Corrupted]");
    }

    printf("\n================ THEORETICAL ANALYSIS ================\n");
    printf("a. Are any blocks beyond P2 affected when C1 is corrupted?\n");
    printf("   - NO! CBC Decryption formula: P_i = D_K(C_i) ^ C_{i-1}\n");
    printf("   - For i >= 3, P_i depends ONLY on C_i and C_{i-1}.\n");
    printf("   - Therefore, C1 has NO effect on P3, P4, etc. (Self-synchronizing).\n\n");

    printf("b. If there is a bit error in the SOURCE P1:\n");
    printf("   - C1 is corrupted at encryption time.\n");
    printf("   - Since C1 is chained into C2, C2 into C3, and so on,\n");
    printf("     ALL subsequent ciphertext blocks (C1, C2, ..., Cn) are changed.\n");
    printf("   - At the receiver, ALL plaintext blocks will be corrupted.\n");
    printf("===============================================================\n");

    return 0;
}
