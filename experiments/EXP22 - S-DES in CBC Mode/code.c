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

    // LS-1
    left = leftShift(left, 1, 5);
    right = leftShift(right, 1, 5);
    *k1 = permute((left << 5) | right, P8, 8, 10);

    // LS-2
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

    // Round 1
    uint8_t l1 = r;
    uint8_t r1 = l ^ f_k(r, k1);

    // Round 2
    uint8_t l2 = r1 ^ f_k(l1, k2);
    uint8_t r2 = l1;

    return permute((l2 << 4) | r2, IP_INV, 8, 8);
}

uint8_t sdes_decrypt(uint8_t block, uint8_t k1, uint8_t k2) {
    return sdes_encrypt(block, k2, k1);
}

void printBinary8(uint8_t b) {
    for (int i = 7; i >= 0; i--) printf("%d", (b >> i) & 1);
}

int main() {
    printf("===============================================================\n");
    printf("        EXP 22: S-DES IN CIPHER BLOCK CHAINING (CBC) MODE      \n");
    printf("===============================================================\n\n");

    uint16_t key = 0x1FD; // 01111 11101
    uint8_t iv = 0xAA;    // 1010 1010
    uint8_t plain[2] = {0x01, 0x23}; // 00000001 00100011
    uint8_t cipher[2], decrypted[2];

    uint8_t k1, k2;
    generateSubkeys(key, &k1, &k2);

    printf("Key: 01111 11101\n");
    printf("IV : 1010 1010\n");
    printf("Subkey K1 = 0x%02X, K2 = 0x%02X\n\n", k1, k2);

    printf("Test Plaintext:\n  Block 1: ");
    printBinary8(plain[0]);
    printf(" (0x%02X)\n  Block 2: ", plain[0]);
    printBinary8(plain[1]);
    printf(" (0x%02X)\n\n", plain[1]);

    // CBC Encryption
    uint8_t prev = iv;
    for (int i = 0; i < 2; i++) {
        cipher[i] = sdes_encrypt(plain[i] ^ prev, k1, k2);
        prev = cipher[i];
    }

    printf("Encrypted Ciphertext (CBC Mode):\n  Block 1: ");
    printBinary8(cipher[0]);
    printf(" (Expected: 1111 0100 -> 0x%02X)\n  Block 2: ", cipher[0]);
    printBinary8(cipher[1]);
    printf(" (Expected: 0000 1011 -> 0x%02X)\n\n", cipher[1]);

    // CBC Decryption
    prev = iv;
    for (int i = 0; i < 2; i++) {
        decrypted[i] = sdes_decrypt(cipher[i], k1, k2) ^ prev;
        prev = cipher[i];
    }

    printf("Decrypted Plaintext:\n  Block 1: ");
    printBinary8(decrypted[0]);
    printf(" (0x%02X)\n  Block 2: ", decrypted[0]);
    printBinary8(decrypted[1]);
    printf(" (0x%02X)\n\n", decrypted[1]);

    if (cipher[0] == 0xF4 && cipher[1] == 0x0B && decrypted[0] == plain[0] && decrypted[1] == plain[1]) {
        printf(">>> VERIFICATION SUCCESSFUL! Matches expected test vectors. <<<\n");
    }
    printf("===============================================================\n");

    return 0;
}
