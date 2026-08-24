#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int invert2x2(int m[2][2], int inv[2][2]) {
    int det = mod26(m[0][0] * m[1][1] - m[0][1] * m[1][0]);
    int detInv = modInverse(det);
    if (detInv == -1) return 0; // Not invertible

    inv[0][0] = mod26(detInv * m[1][1]);
    inv[0][1] = mod26(detInv * -m[0][1]);
    inv[1][0] = mod26(detInv * -m[1][0]);
    inv[1][1] = mod26(detInv * m[0][0]);
    return 1;
}

int main() {
    printf("===============================================================\n");
    printf("     EXP 13: KNOWN PLAINTEXT ATTACK ON HILL CIPHER (2x2)       \n");
    printf("===============================================================\n\n");

    printf("Problem Description:\n");
    printf("Given known plaintext pairs and their corresponding ciphertext,\n");
    printf("we set up matrix equation: C = P * K (mod 26) => K = P^(-1) * C (mod 26)\n\n");

    // Example Known Plaintext: "FRIDAY" -> "PQCFKU"
    // P1 = "FR" = [5, 17], P2 = "ID" = [8, 3]
    // C1 = "PQ" = [15, 16], C2 = "CF" = [2, 5]
    char plainSample[] = "FRID";
    char cipherSample[] = "PQCF";

    printf("Known Plaintext Sample : \"%s\"\n", plainSample);
    printf("Corresponding Cipher   : \"%s\"\n\n", cipherSample);

    int P[2][2] = {
        { plainSample[0] - 'A', plainSample[1] - 'A' },
        { plainSample[2] - 'A', plainSample[3] - 'A' }
    };

    int C[2][2] = {
        { cipherSample[0] - 'A', cipherSample[1] - 'A' },
        { cipherSample[2] - 'A', cipherSample[3] - 'A' }
    };

    printf("Plaintext Matrix P:\n");
    printf("  [ %2d  %2d ]\n", P[0][0], P[0][1]);
    printf("  [ %2d  %2d ]\n\n", P[1][0], P[1][1]);

    printf("Ciphertext Matrix C:\n");
    printf("  [ %2d  %2d ]\n", C[0][0], C[0][1]);
    printf("  [ %2d  %2d ]\n\n", C[1][0], C[1][1]);

    int P_inv[2][2];
    if (!invert2x2(P, P_inv)) {
        printf("Error: Plaintext matrix is not invertible modulo 26. Pick another pair.\n");
        return 1;
    }

    printf("P^(-1) mod 26:\n");
    printf("  [ %2d  %2d ]\n", P_inv[0][0], P_inv[0][1]);
    printf("  [ %2d  %2d ]\n\n", P_inv[1][0], P_inv[1][1]);

    // Recover K = P_inv * C mod 26
    int K[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K[i][j] = mod26(P_inv[i][0] * C[0][j] + P_inv[i][1] * C[1][j]);
        }
    }

    printf(">>> RECOVERED SECRET KEY MATRIX K <<<\n");
    printf("  [ %2d  %2d ]\n", K[0][0], K[0][1]);
    printf("  [ %2d  %2d ]\n\n", K[1][0], K[1][1]);

    printf("Verification using full test text:\n");
    char fullPlain[] = "FRIDAY";
    char fullCipher[10];
    for (int i = 0; i < 6; i += 2) {
        int p1 = fullPlain[i] - 'A';
        int p2 = fullPlain[i + 1] - 'A';
        fullCipher[i] = mod26(p1 * K[0][0] + p2 * K[1][0]) + 'A';
        fullCipher[i + 1] = mod26(p1 * K[0][1] + p2 * K[1][1]) + 'A';
    }
    fullCipher[6] = '\0';
    printf("  Encryption of \"%s\" with recovered key: \"%s\"\n", fullPlain, fullCipher);

    return 0;
}
