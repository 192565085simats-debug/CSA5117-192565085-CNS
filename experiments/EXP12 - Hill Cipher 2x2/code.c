#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Matrix dimensions
#define N 2

int mod26(int x) {
    return ((x % 26) + 26) % 26;
}

int modInverse(int a) {
    a = mod26(a);
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) return i;
    }
    return -1;
}

int main() {
    int key[2][2] = { {9, 4}, {5, 7} };
    int invKey[2][2];
    const char *plaintext = "meet me at the usual place at ten rather than eight oclock";

    printf("====================================================\n");
    printf("         EXP 12: 2x2 HILL CIPHER                    \n");
    printf("====================================================\n\n");

    printf("Key Matrix K:\n");
    printf("  [ %d   %d ]\n", key[0][0], key[0][1]);
    printf("  [ %d   %d ]\n\n", key[1][0], key[1][1]);

    // 1. Calculate determinant
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int detMod = mod26(det);
    int detInv = modInverse(detMod);

    printf("1. Calculations for Key Inversion:\n");
    printf("   - det(K) = (%d * %d) - (%d * %d) = %d = %d (mod 26)\n", 
           key[0][0], key[1][1], key[0][1], key[1][0], det, detMod);
    printf("   - Modular Inverse of det(K) mod 26 = %d (since %d * %d mod 26 = 1)\n", 
           detInv, detMod, detInv);

    // Adjugate Matrix
    int adj[2][2] = {
        { key[1][1], -key[0][1] },
        { -key[1][0], key[0][0] }
    };

    printf("   - Adjugate Matrix mod 26:\n");
    printf("     [ %2d  %2d ]\n", mod26(adj[0][0]), mod26(adj[0][1]));
    printf("     [ %2d  %2d ]\n", mod26(adj[1][0]), mod26(adj[1][1]));

    // Inverse Key Matrix
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invKey[i][j] = mod26(detInv * adj[i][j]);
        }
    }

    printf("   - Inverse Key Matrix K^(-1):\n");
    printf("     [ %2d  %2d ]\n", invKey[0][0], invKey[0][1]);
    printf("     [ %2d  %2d ]\n\n", invKey[1][0], invKey[1][1]);

    // Prepare text
    char cleanText[500];
    int len = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            cleanText[len++] = toupper(plaintext[i]);
        }
    }
    if (len % 2 != 0) {
        cleanText[len++] = 'X';
    }
    cleanText[len] = '\0';

    printf("Original Text : \"%s\"\n", plaintext);
    printf("Prepared Text : %s\n\n", cleanText);

    // Encryption
    char cipherText[500];
    for (int i = 0; i < len; i += 2) {
        int p1 = cleanText[i] - 'A';
        int p2 = cleanText[i + 1] - 'A';

        int c1 = mod26(key[0][0] * p1 + key[0][1] * p2);
        int c2 = mod26(key[1][0] * p1 + key[1][1] * p2);

        cipherText[i] = c1 + 'A';
        cipherText[i + 1] = c2 + 'A';
    }
    cipherText[len] = '\0';

    printf("2. Encrypted Ciphertext:\n   %s\n\n", cipherText);

    // Decryption
    char decryptedText[500];
    for (int i = 0; i < len; i += 2) {
        int c1 = cipherText[i] - 'A';
        int c2 = cipherText[i + 1] - 'A';

        int p1 = mod26(invKey[0][0] * c1 + invKey[0][1] * c2);
        int p2 = mod26(invKey[1][0] * c1 + invKey[1][1] * c2);

        decryptedText[i] = p1 + 'A';
        decryptedText[i + 1] = p2 + 'A';
    }
    decryptedText[len] = '\0';

    printf("3. Decrypted Plaintext:\n   %s\n", decryptedText);

    return 0;
}
