#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // 8 bytes = 64 bits

// Pad data using PKCS#7 / 1-bit followed by zero bits
int padMessage(const unsigned char *input, int inLen, unsigned char *output) {
    memcpy(output, input, inLen);
    int padLen = BLOCK_SIZE - (inLen % BLOCK_SIZE);
    if (padLen == 0) padLen = BLOCK_SIZE; // Always add a block if exact multiple

    // Pad method: 0x80 (1000 0000) followed by zeros
    output[inLen] = 0x80;
    for (int i = 1; i < padLen; i++) {
        output[inLen + i] = 0x00;
    }
    return inLen + padLen;
}

int unpadMessage(const unsigned char *padded, int totalLen) {
    int i = totalLen - 1;
    while (i >= 0 && padded[i] == 0x00) {
        i--;
    }
    if (i >= 0 && padded[i] == 0x80) {
        return i; // Original length
    }
    return -1; // Padding error
}

int main() {
    printf("===============================================================\n");
    printf("     EXP 21: BLOCK CIPHER PADDING METHODS AND MOTIVATION       \n");
    printf("===============================================================\n\n");

    unsigned char msg1[] = "HELLO";       // 5 bytes (incomplete block)
    unsigned char msg2[] = "12345678";    // 8 bytes (exact full block)
    unsigned char padded[32];

    printf("Case 1: Message length (5 bytes) NOT a multiple of block size (8 bytes):\n");
    printf("  Original Message : \"%s\" (len = 5)\n", msg1);
    int len1 = padMessage(msg1, 5, padded);
    printf("  Padded Bytes     : ");
    for (int i = 0; i < len1; i++) printf("%02X ", padded[i]);
    printf(" (total %d bytes)\n", len1);
    int unpadded1 = unpadMessage(padded, len1);
    printf("  Unpadded Length  : %d bytes\n\n", unpadded1);

    printf("Case 2: Message length (8 bytes) IS an exact multiple of block size:\n");
    printf("  Original Message : \"%s\" (len = 8)\n", msg2);
    int len2 = padMessage(msg2, 8, padded);
    printf("  Padded Bytes     : ");
    for (int i = 0; i < len2; i++) printf("%02X ", padded[i]);
    printf(" (total %d bytes)\n", len2);
    int unpadded2 = unpadMessage(padded, len2);
    printf("  Unpadded Length  : %d bytes\n\n", unpadded2);

    printf("================ THEORETICAL MOTIVATION ================\n");
    printf("Why add a whole padding block when message is already complete?\n");
    printf("  1. Unambiguous Unpadding:\n");
    printf("     If no padding was added to an 8-byte message ending in 0x80 0x00,\n");
    printf("     the receiver would mistake genuine payload bytes for padding.\n");
    printf("  2. Deterministic Protocol:\n");
    printf("     By always appending padding, the receiver ALWAYS strips padding\n");
    printf("     without needing separate metadata indicating payload length.\n");
    printf("===============================================================\n");

    return 0;
}
