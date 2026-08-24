#include <stdio.h>
#include <stdint.h>

// S-DES Tables
const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[8]   = {6, 3, 7, 4, 8, 5, 10, 9};
const int IP[8]   = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
const int EP[8]   = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[4]   = {2, 4, 3, 1};

const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

uint16_t permute(uint16_t in, const int *table, int n, int inBits) {
    uint16_t out = 0;
    for (int i = 0; i < n; i++) {
        int bit = (in >> (inBits - table[i])) & 1;
        out = (out << 1) | bit;
    }
    return out;
}

uint8_t leftShift(uint8_t val, int shift, int bits) {
    uint8_t mask = (1 << bits) - 1;
    return ((val << shift) | (val >> (bits - shift))) & mask;
}

void generateSubkeys(uint16_t key10, uint8_t *k1, uint8_t *k2) {
    uint16_t p10 = permute(key10, P10, 10, 10);
    uint8_t left = (p10 >> 5) & 0x1F;
    uint8_t right = p10 & 0x1F;

    left = leftShift(left, 1, 5);
    right = leftShift(right, 1, 5);
    *k1 = permute((left << 5) | right, P8, 8, 10);

    left = leftShift(left, 2, 5);
    right = leftShift(right, 2, 5);
    *k2 = permute((left << 5) | right, P8, 8, 10);
}

uint8_t f_k(uint8_t r, uint8_t sk) {
    uint8_t ep = permute(r, EP, 8, 4);
    uint8_t x = ep ^ sk;

    uint8_t left = (x >> 4) & 0xF;
    uint8_t right = x & 0xF;

    int r0 = ((left & 0x8) >> 2) | (left & 0x1);
    int c0 = (left >> 1) & 0x3;
    uint8_t s0_val = S0[r0][c0];

    int r1 = ((right & 0x8) >> 2) | (right & 0x1);
    int c1 = (right >> 1) & 0x3;
    uint8_t s1_val = S1[r1][c1];

    return permute((s0_val << 2) | s1_val, P4, 4, 4);
}

uint8_t sdes_encrypt(uint8_t block, uint8_t k1, uint8_t k2) {
    uint8_t ip = permute(block, IP, 8, 8);
    uint8_t l = (ip >> 4) & 0xF;
    uint8_t r = ip & 0xF;

    uint8_t l1 = r;
    uint8_t r1 = l ^ f_k(r, k1);

    uint8_t l2 = r1 ^ f_k(l1, k2);
    uint8_t r2 = l1;

    return permute((l2 << 4) | r2, IP_INV, 8, 8);
}

void printBinary8(uint8_t b) {
    for (int i = 7; i >= 0; i--) printf("%d", (b >> i) & 1);
}

int main() {
    printf("===============================================================\n");
    printf("         EXP 23: S-DES IN COUNTER (CTR) MODE                   \n");
    printf("===============================================================\n\n");

    uint16_t key = 0x1FD; // 01111 11101
    uint8_t initialCounter = 0x00; // 0000 0000
    uint8_t plain[3] = {0x01, 0x02, 0x04}; // 00000001 00000010 00000100
    uint8_t cipher[3], decrypted[3];

    uint8_t k1, k2;
    generateSubkeys(key, &k1, &k2);

    printf("Key: 01111 11101\n");
    printf("Initial Counter: 0000 0000\n\n");

    printf("Plaintext Blocks:\n");
    for (int i = 0; i < 3; i++) {
        printf("  Block %d: ", i + 1);
        printBinary8(plain[i]);
        printf(" (0x%02X)\n", plain[i]);
    }
    printf("\n");

    // CTR Encryption: C_i = P_i ^ E_K(CTR_i)
    for (int i = 0; i < 3; i++) {
        uint8_t ctr = initialCounter + i;
        uint8_t keystream = sdes_encrypt(ctr, k1, k2);
        cipher[i] = plain[i] ^ keystream;
    }

    printf("Encrypted Ciphertext (CTR Mode):\n");
    for (int i = 0; i < 3; i++) {
        printf("  Block %d: ", i + 1);
        printBinary8(cipher[i]);
        printf(" (0x%02X)\n", cipher[i]);
    }
    printf("\nExpected: 0011 1000 (0x38), 0100 1111 (0x4F), 0011 0010 (0x32)\n\n");

    // CTR Decryption: P_i = C_i ^ E_K(CTR_i)
    for (int i = 0; i < 3; i++) {
        uint8_t ctr = initialCounter + i;
        uint8_t keystream = sdes_encrypt(ctr, k1, k2); // Note: encryption used for decrypt!
        decrypted[i] = cipher[i] ^ keystream;
    }

    printf("Decrypted Plaintext:\n");
    for (int i = 0; i < 3; i++) {
        printf("  Block %d: ", i + 1);
        printBinary8(decrypted[i]);
        printf(" (0x%02X)\n", decrypted[i]);
    }
    printf("\n");

    if (cipher[0] == 0x38 && cipher[1] == 0x4F && cipher[2] == 0x32) {
        printf(">>> VERIFICATION SUCCESSFUL! Output matches expected test vectors. <<<\n");
    }
    printf("===============================================================\n");

    return 0;
}
