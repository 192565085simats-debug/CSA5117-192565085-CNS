#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simple Feistel Block Cipher demonstration representing 3DES in CBC mode
uint64_t mockDES(uint64_t block, uint64_t key, int encrypt) {
    // Reversible mock Feistel round for demonstration
    uint32_t left = (uint32_t)(block >> 32);
    uint32_t right = (uint32_t)(block & 0xFFFFFFFF);
    uint32_t k = (uint32_t)(key & 0xFFFFFFFF);

    if (encrypt) {
        left ^= (right + k);
        return (((uint64_t)right) << 32) | left;
    } else {
        right ^= (left + k);
        return (((uint64_t)left) << 32) | right;
    }
}

// 3DES (EDE Mode): C = E(K3, D(K2, E(K1, P)))
uint64_t tripleDES_encrypt(uint64_t block, uint64_t k1, uint64_t k2, uint64_t k3) {
    uint64_t step1 = mockDES(block, k1, 1);
    uint64_t step2 = mockDES(step1, k2, 0);
    uint64_t step3 = mockDES(step2, k3, 1);
    return step3;
}

// 3DES (EDE Decrypt): P = D(K1, E(K2, D(K3, C)))
uint64_t tripleDES_decrypt(uint64_t block, uint64_t k1, uint64_t k2, uint64_t k3) {
    uint64_t step1 = mockDES(block, k3, 0);
    uint64_t step2 = mockDES(step1, k2, 1);
    uint64_t step3 = mockDES(step2, k1, 0);
    return step3;
}

int main() {
    printf("===============================================================\n");
    printf("        EXP 19: 3DES IN CIPHER BLOCK CHAINING (CBC) MODE       \n");
    printf("===============================================================\n\n");

    uint64_t k1 = 0x133457799BBCDFF1ULL;
    uint64_t k2 = 0x0E329232EA6D0D73ULL;
    uint64_t k3 = 0x87A24510D789BCEFULL;
    uint64_t iv = 0xFEEDFACECAFEBEEFULL;

    uint64_t plaintext[3] = {
        0x0123456789ABCDEFULL,
        0x1122334455667788ULL,
        0xAABBCCDDEEFF0011ULL
    };
    uint64_t ciphertext[3];
    uint64_t decrypted[3];

    // CBC Encryption: C_i = 3DES_Enc(P_i ^ C_{i-1})
    uint64_t prev = iv;
    for (int i = 0; i < 3; i++) {
        ciphertext[i] = tripleDES_encrypt(plaintext[i] ^ prev, k1, k2, k3);
        prev = ciphertext[i];
    }

    // CBC Decryption: P_i = 3DES_Dec(C_i) ^ C_{i-1}
    prev = iv;
    for (int i = 0; i < 3; i++) {
        decrypted[i] = tripleDES_decrypt(ciphertext[i], k1, k2, k3) ^ prev;
        prev = ciphertext[i];
    }

    printf("CBC Mode 3DES Simulation:\n");
    for (int i = 0; i < 3; i++) {
        printf("  Block %d:\n", i + 1);
        printf("    Plaintext  : 0x%016llX\n", plaintext[i]);
        printf("    Ciphertext : 0x%016llX\n", ciphertext[i]);
        printf("    Decrypted  : 0x%016llX\n", decrypted[i]);
    }

    printf("\n--- QUESTIONS AND ANSWERS ---\n");
    printf("Between 3DES and modern alternatives like AES in CBC:\n");
    printf("a. For Security:\n");
    printf("   - AES-256 is preferred. 3DES has a 64-bit block size which makes it\n");
    printf("     vulnerable to birthday attacks (Sweet32 attack) in CBC mode.\n");
    printf("b. For Performance:\n");
    printf("   - AES is significantly faster due to dedicated hardware acceleration\n");
    printf("     (AES-NI instructions) and a 128-bit native architecture.\n");
    printf("===============================================================\n");

    return 0;
}
