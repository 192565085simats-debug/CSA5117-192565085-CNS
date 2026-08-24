#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    printf("===============================================================\n");
    printf("    EXP 27: ATTACK ON CHARACTER-BY-CHARACTER RSA ENCRYPTION    \n");
    printf("===============================================================\n\n");

    // Public Key (Large e, Large n)
    long long n = 1000000007LL * 1000000009LL; // Large RSA modulus
    long long e = 65537;

    printf("Public Parameters:\n");
    printf("  Modulus n = %lld\n", n);
    printf("  Exponent e = %lld\n\n", e);

    const char *secretMessage = "ATTACKATDAWN";
    int msgLen = strlen(secretMessage);
    long long ciphertext[50];

    printf("Alice's Secret Message: \"%s\"\n", secretMessage);
    printf("Alice encrypts each letter (0..25) separately using RSA:\n");

    for (int i = 0; i < msgLen; i++) {
        long long m = secretMessage[i] - 'A';
        ciphertext[i] = modExp(m, e, n);
        printf("  '%c' (m=%2lld) -> C[%d] = %lld\n", secretMessage[i], m, i, ciphertext[i]);
    }
    printf("\n");

    printf("================ ADVERSARY (EVE) ATTACK ================\n");
    printf("Eve intercepts the ciphertext blocks.\n");
    printf("Eve builds a Codebook by computing C_m = m^e mod n for all 26 letters:\n\n");

    long long codebook[26];
    for (int m = 0; m < 26; m++) {
        codebook[m] = modExp(m, e, n);
    }

    printf("Eve recovers the plaintext by simple O(1) dictionary lookups:\n");
    char recovered[50];
    for (int i = 0; i < msgLen; i++) {
        for (int m = 0; m < 26; m++) {
            if (ciphertext[i] == codebook[m]) {
                recovered[i] = 'A' + m;
                break;
            }
        }
    }
    recovered[msgLen] = '\0';

    printf("  Decrypted Message: \"%s\"\n\n", recovered);

    printf("================ SECURITY CONCLUSION ================\n");
    printf("Is this method secure? ABSOLUTELY NOT.\n");
    printf("Because the message space is trivial (|M| = 26), an adversary can\n");
    printf("precompute all 26 ciphertexts in milliseconds. Deterministic RSA\n");
    printf("without randomized padding (like OAEP) is completely insecure for small inputs.\n");
    printf("===============================================================\n");

    return 0;
}
