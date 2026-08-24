#include <stdio.h>
#include <string.h>

// Encryption shift schedule
const int encShifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Decryption shift schedule (Right shifts)
const int decShifts[16] = {0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int main() {
    printf("===============================================================\n");
    printf("     EXP 17: DES DECRYPTION KEY SCHEDULE ALGORITHM             \n");
    printf("===============================================================\n\n");

    printf("1. Standard DES Encryption Key Schedule (Left Shifts):\n");
    printf("Round | Left Shifts | Cumulative Shift\n");
    printf("------+-------------+-----------------\n");
    int cumEnc = 0;
    for (int i = 0; i < 16; i++) {
        cumEnc += encShifts[i];
        printf("  %2d  |     %2d      |       %2d\n", i + 1, encShifts[i], cumEnc);
    }
    printf("Total Left Shifts across 16 rounds = %d (28 mod 28 = 0)\n\n", cumEnc);

    printf("---------------------------------------------------------------\n");
    printf("2. DES Decryption Key Schedule (Right Shifts from (C16, D16)):\n");
    printf("Round | Subkey | Right Shifts | Description\n");
    printf("------+--------+--------------+----------------------------------\n");
    for (int i = 0; i < 16; i++) {
        printf("  %2d  |  K_%-2d  |      %2d      | ", i + 1, 16 - i, decShifts[i]);
        if (i == 0) {
            printf("Direct output of (C16, D16)\n");
        } else {
            printf("Shift (C, D) right by %d bit(s)\n", decShifts[i]);
        }
    }
    printf("\nConclusion:\n");
    printf("  By applying this right-shift schedule, subkeys K16, K15, ..., K1\n");
    printf("  are generated directly in reverse order on the fly during decryption.\n");
    printf("===============================================================\n");

    return 0;
}
