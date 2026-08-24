#include <stdio.h>
#include <string.h>

#define BLOCK_SZ 8

// Demonstrates the critical necessity of padding even for full blocks
int main() {
    printf("===============================================================\n");
    printf("    EXP 34: PADDING NECESSITY IN BLOCK CIPHER MODES            \n");
    printf("===============================================================\n\n");

    printf("Scenario: An application receives two messages:\n");
    printf("  Message A: 7 bytes:  \"SECRET\" (0x53 0x45 0x43 0x52 0x45 0x54)\n");
    printf("  Message B: 8 bytes:  \"SECRET\\x01\" (ends in 0x01 naturally)\n\n");

    printf("Suppose System 1 does NOT add padding when a block is complete (8 bytes):\n");
    printf("  - Message A (7 bytes) is padded with 1 byte of 0x01 -> total 8 bytes.\n");
    printf("  - Message B (8 bytes) is left UNPADDED             -> total 8 bytes.\n\n");

    printf("Ciphertext resulting from Message A and Message B:\n");
    printf("  Both produce the EXACT SAME byte sequence: [ 'S', 'E', 'C', 'R', 'E', 'T', 0x01 ]!\n\n");

    printf("At the receiver side:\n");
    printf("  - When receiving Message B, receiver sees 0x01 at the end.\n");
    printf("  - Receiver mistakenly removes 0x01 thinking it was padding!\n");
    printf("  - Message B is corrupted (payload truncated from \"SECRET\\x01\" to \"SECRET\").\n\n");

    printf("================ SOLUTION: MANDATORY PADDING ================\n");
    printf("Under standard PKCS#7 / ANSI X9.23:\n");
    printf("  - Message A is padded with 1 byte  -> [ 'S', 'E', 'C', 'R', 'E', 'T', 0x01 ] (8 bytes)\n");
    printf("  - Message B is padded with 8 bytes -> [ 'S', 'E', 'C', 'R', 'E', 'T', 0x01, 0x08 ... 0x08 ] (16 bytes)\n\n");
    printf(">>> RESULT: Unambiguous decryption with zero risk of data corruption! <<<\n");
    printf("===============================================================\n");

    return 0;
}
