#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to find modular multiplicative inverse of a mod 26
int modInverse(int a) {
    a = (a % 26 + 26) % 26;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) return i;
    }
    return -1;
}

void printTheoreticalAnalysis() {
    printf("\n--- THEORETICAL ANALYSIS ---\n");
    printf("General formula: C = E([a, b], p) = (a*p + b) mod 26\n");
    printf("Decryption formula: p = D([a, b], C) = a^(-1) * (C - b) mod 26\n\n");
    printf("a. Limitations on value of b:\n");
    printf("   - b can be any integer from 0 to 25 (shift offset).\n");
    printf("   - There are no coprimality restrictions on b.\n\n");
    printf("b. Disallowed values of a:\n");
    printf("   - 'a' MUST be coprime to 26 (i.e., gcd(a, 26) == 1).\n");
    printf("   - Disallowed values of a in [0..25]:\n");
    printf("     Even numbers: 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24\n");
    printf("     Multiple of 13: 13\n");
    printf("   - Total 12 valid values of a: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25.\n");
    printf("----------------------------\n\n");
}

int main() {
    char text[200], encrypted[200], decrypted[200];
    int a, b, choice;

    printf("====================================================\n");
    printf("         EXP 05: AFFINE CAESAR CIPHER               \n");
    printf("====================================================\n");

    printTheoreticalAnalysis();

    printf("Enter plaintext: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("Enter value of a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("Enter value of b (0-25): ");
    scanf("%d", &b);

    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("\nError: gcd(%d, 26) = %d != 1. Value 'a' has no modular inverse mod 26!\n", a, gcd(a, 26));
        printf("Decryption is impossible (one-to-one mapping fails).\n");
        return 1;
    }

    // Encryption: C = (a*p + b) mod 26
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            encrypted[i] = ((a * (text[i] - 'A') + b) % 26 + 26) % 26 + 'A';
        } else if (islower(text[i])) {
            encrypted[i] = ((a * (text[i] - 'a') + b) % 26 + 26) % 26 + 'a';
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[i] = '\0';

    // Decryption: P = a_inv * (C - b) mod 26
    for (i = 0; encrypted[i] != '\0'; i++) {
        if (isupper(encrypted[i])) {
            decrypted[i] = ((a_inv * ((encrypted[i] - 'A' - b) % 26 + 26)) % 26) + 'A';
        } else if (islower(encrypted[i])) {
            decrypted[i] = ((a_inv * ((encrypted[i] - 'a' - b) % 26 + 26)) % 26) + 'a';
        } else {
            decrypted[i] = encrypted[i];
        }
    }
    decrypted[i] = '\0';

    printf("\nModular Inverse of a (%d mod 26): %d\n", a, a_inv);
    printf("Encrypted Ciphertext : %s\n", encrypted);
    printf("Decrypted Plaintext  : %s\n", decrypted);

    return 0;
}
