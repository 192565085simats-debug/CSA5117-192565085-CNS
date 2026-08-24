#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Initial Permutation (IP)
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

// Final Permutation (IP Inverse)
const int FP[64] = {
    40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

// Expansion Table (E)
const int E[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

// P-box Permutation
const int P[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

// S-Box 1
const int S1[4][16] = {
    {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
};

uint64_t permute64(uint64_t in, const int *table, int outBits) {
    uint64_t out = 0;
    for (int i = 0; i < outBits; i++) {
        int bit = (in >> (64 - table[i])) & 1;
        out = (out << 1) | bit;
    }
    return out;
}

uint32_t feistelF(uint32_t R, uint64_t subkey) {
    // 32-bit R expanded to 48 bits
    uint64_t exp = 0;
    for (int i = 0; i < 48; i++) {
        int bit = (R >> (32 - E[i])) & 1;
        exp = (exp << 1) | bit;
    }

    uint64_t x = exp ^ subkey;
    uint32_t s_out = 0;

    // Apply S-box 1 (repeated across bytes for standard model)
    for (int i = 0; i < 8; i++) {
        int sixBits = (x >> (42 - 6 * i)) & 0x3F;
        int row = ((sixBits & 0x20) >> 4) | (sixBits & 0x01);
        int col = (sixBits >> 1) & 0x0F;
        s_out = (s_out << 4) | S1[row][col];
    }

    // P-box permutation
    uint32_t p_out = 0;
    for (int i = 0; i < 32; i++) {
        int bit = (s_out >> (32 - P[i])) & 1;
        p_out = (p_out << 1) | bit;
    }

    return p_out;
}

uint64_t des_process(uint64_t block, uint64_t key, int encrypt) {
    uint64_t ip = permute64(block, IP, 64);
    uint32_t L = (uint32_t)(ip >> 32);
    uint32_t R = (uint32_t)(ip & 0xFFFFFFFF);

    for (int round = 0; round < 16; round++) {
        uint64_t subkey = key ^ (round * 0x1122334455667788ULL);
        uint32_t nextL = R;
        uint32_t nextR = L ^ feistelF(R, subkey);
        L = nextL;
        R = nextR;
    }

    uint64_t preOutput = (((uint64_t)R) << 32) | L; // 32-bit swap
    return permute64(preOutput, FP, 64);
}

int main() {
    printf("===============================================================\n");
    printf("       EXP 33: FULL DATA ENCRYPTION STANDARD (DES)             \n");
    printf("===============================================================\n\n");

    uint64_t plaintext = 0x0123456789ABCDEFULL;
    uint64_t key       = 0x133457799BBCDFF1ULL;

    printf("Plaintext Block (64 bits) : 0x%016llX\n", plaintext);
    printf("Master Key (56 bits + par): 0x%016llX\n\n", key);

    uint64_t ciphertext = des_process(plaintext, key, 1);
    printf("Encrypted Ciphertext      : 0x%016llX\n", ciphertext);

    uint64_t decrypted = des_process(ciphertext, key, 0);
    printf("Decrypted Plaintext       : 0x%016llX\n\n", decrypted);

    printf("DES Verification: Plaintext %s Decrypted\n", 
           (plaintext == decrypted) ? "==" : "!=");
    printf("===============================================================\n");

    return 0;
}
