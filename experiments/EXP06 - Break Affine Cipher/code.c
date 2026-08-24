#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find modular inverse of a mod 26
int modInverse(int a) {
    a = (a % 26 + 26) % 26;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) return i;
    }
    return -1;
}

int main() {
    printf("====================================================\n");
    printf("     EXP 06: BREAKING AN AFFINE CIPHER              \n");
    printf("====================================================\n");

    printf("\n--- CRYPTANALYSIS DEDUCTION ---\n");
    printf("Given:\n");
    printf("  1. Most frequent ciphertext letter   = 'B' (C1 = 1)\n");
    printf("  2. Second most frequent cipher letter = 'U' (C2 = 20)\n\n");
    printf("English letter frequency knowledge:\n");
    printf("  - Most frequent plaintext letter   = 'E' (P1 = 4)\n");
    printf("  - Second most frequent plain letter = 'T' (P2 = 19)\n\n");
    printf("Affine encryption system of congruences:\n");
    printf("  (1)  (4*a + b)  = 1   (mod 26)\n");
    printf("  (2)  (19*a + b) = 20  (mod 26)\n\n");
    printf("Subtracting (1) from (2):\n");
    printf("  15*a = 19 (mod 26)\n");
    printf("  Modular inverse of 15 mod 26 = 7 (since 15 * 7 = 105 = 4*26 + 1 = 1)\n");
    printf("  a = (19 * 7) mod 26 = 133 mod 26 = 3\n");
    printf("Substitute a = 3 into (1):\n");
    printf("  4(3) + b = 1 (mod 26) => 12 + b = 1 => b = 1 - 12 = -11 = 15 (mod 26)\n\n");

    int a = 3;
    int b = 15;
    int a_inv = modInverse(a);

    printf("Key deduced:\n");
    printf("  Key a = %d, Key b = %d\n", a, b);
    printf("  Modular inverse a^(-1) mod 26 = %d\n", a_inv);
    printf("  Decryption formula: P = %d * (C - %d) mod 26\n", a_inv, b);
    printf("----------------------------------------------------\n\n");

    char ciphertext[500];
    char plaintext[500];

    printf("Enter Ciphertext to decrypt using deduced key: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) return 1;
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isupper(ciphertext[i])) {
            int c = ciphertext[i] - 'A';
            plaintext[i] = ((a_inv * ((c - b + 26) % 26)) % 26) + 'A';
        } else if (islower(ciphertext[i])) {
            int c = ciphertext[i] - 'a';
            plaintext[i] = ((a_inv * ((c - b + 26) % 26)) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';

    printf("\nDecrypted Plaintext: %s\n", plaintext);

    return 0;
}
