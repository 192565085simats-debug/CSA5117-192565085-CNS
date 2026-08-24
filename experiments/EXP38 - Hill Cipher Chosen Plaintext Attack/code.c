#include <stdio.h>
#include <string.h>

int mod26(int x) {
    return ((x % 26) + 26) % 26;
}

int main() {
    printf("===============================================================\n");
    printf("   EXP 38: CHOSEN PLAINTEXT ATTACK ON 2x2 HILL CIPHER          \n");
    printf("===============================================================\n\n");

    // Secret Key Matrix unknown to attacker
    int K_secret[2][2] = {
        {7, 19},
        {8, 11}
    };

    printf("Hypothetical Secret Key Matrix K (hidden from adversary):\n");
    printf("  [ %2d  %2d ]\n", K_secret[0][0], K_secret[0][1]);
    printf("  [ %2d  %2d ]\n\n", K_secret[1][0], K_secret[1][1]);

    printf("Adversary Strategy (Chosen Plaintext Attack):\n");
    printf("  The adversary submits standard basis vectors as chosen plaintexts:\n");
    printf("    P1 = [1, 0]  (e.g., 'BA')\n");
    printf("    P2 = [0, 1]  (e.g., 'AB')\n\n");

    // Chosen plaintext 1: P1 = [1, 0]
    int C1[2] = {
        mod26(1 * K_secret[0][0] + 0 * K_secret[1][0]),
        mod26(1 * K_secret[0][1] + 0 * K_secret[1][1])
    };

    // Chosen plaintext 2: P2 = [0, 1]
    int C2[2] = {
        mod26(0 * K_secret[0][0] + 1 * K_secret[1][0]),
        mod26(0 * K_secret[0][1] + 1 * K_secret[1][1])
    };

    printf("Encryption Results returned by Oracle:\n");
    printf("  E([1, 0]) = [%2d, %2d]  (C1)\n", C1[0], C1[1]);
    printf("  E([0, 1]) = [%2d, %2d]  (C2)\n\n", C2[0], C2[1]);

    // Reconstruct K
    int K_recovered[2][2] = {
        { C1[0], C1[1] },
        { C2[0], C2[1] }
    };

    printf("Adversary Reconstruction:\n");
    printf("  Since [1, 0] * K = [K11, K12] and [0, 1] * K = [K21, K22],\n");
    printf("  the ciphertext outputs directly form the rows of the key matrix!\n\n");

    printf(">>> RECOVERED SECRET KEY MATRIX <<<\n");
    printf("  [ %2d  %2d ]\n", K_recovered[0][0], K_recovered[0][1]);
    printf("  [ %2d  %2d ]\n\n", K_recovered[1][0], K_recovered[1][1]);

    printf("Conclusion:\n");
    printf("  Under a Chosen Plaintext Attack, an n x n Hill Cipher key matrix\n");
    printf("  is completely recovered with zero matrix inversions using only n chosen vectors.\n");
    printf("===============================================================\n");

    return 0;
}
