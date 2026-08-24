#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long modInverse(long long a, long long m) {
    a = (a % m + m) % m;
    for (long long i = 1; i < m; i++) {
        if ((a * i) % m == 1) return i;
    }
    return -1;
}

int main() {
    printf("===============================================================\n");
    printf("     EXP 32: DSA VS RSA SIGNATURE NON-DETERMINISM ANALYSIS     \n");
    printf("===============================================================\n\n");

    // Simplified DSA Parameters
    long long p = 7879; // Prime
    long long q = 101;  // Prime factor of p-1
    long long g = 170;  // Generator mod p
    long long x_secret = 23; // Private key (0 < x < q)
    long long y_pub = 4914;  // Public key g^x mod p

    long long hashMsg = 55; // H(M)

    printf("DSA Parameters (p=%lld, q=%lld, g=%lld, pub_y=%lld)\n", p, q, g, y_pub);
    printf("Message Hash H(M) = %lld\n\n", hashMsg);

    // Signature 1 with random k1
    long long k1 = 19;
    long long r1 = 82; // (g^k1 mod p) mod q
    long long k1_inv = modInverse(k1, q);
    long long s1 = (k1_inv * (hashMsg + x_secret * r1)) % q;

    // Signature 2 with different random k2 for the SAME message
    long long k2 = 43;
    long long r2 = 34; // (g^k2 mod p) mod q
    long long k2_inv = modInverse(k2, q);
    long long s2 = (k2_inv * (hashMsg + x_secret * r2)) % q;

    printf("1. Signing the EXACT SAME message twice with DSA:\n");
    printf("   - Signature 1 (using k=%lld) : (r1 = %lld, s1 = %lld)\n", k1, r1, s1);
    printf("   - Signature 2 (using k=%lld) : (r2 = %lld, s2 = %lld)\n", k2, r2, s2);
    printf("   -> Signatures are completely different (Non-deterministic).\n\n");

    printf("---------------------------------------------------------------\n");
    printf("2. CRITICAL SECURITY IMPLICATION: Hazard of Reusing 'k':\n");
    printf("   Suppose a signer accidentally reuses the SAME k for two different messages:\n");

    long long hashM2 = 72; // Different message M2
    long long s1_reuse = (k1_inv * (hashMsg + x_secret * r1)) % q;
    long long s2_reuse = (k1_inv * (hashM2 + x_secret * r1)) % q;

    printf("   Signatures share same r=%lld: (s1 = %lld, s2 = %lld)\n", r1, s1_reuse, s2_reuse);

    // Adversary recovers k: k = (H(m1) - H(m2)) / (s1 - s2) mod q
    long long s_diff = (s1_reuse - s2_reuse + q) % q;
    long long s_diff_inv = modInverse(s_diff, q);
    long long h_diff = (hashMsg - hashM2 + q) % q;
    long long recovered_k = (h_diff * s_diff_inv) % q;

    // Adversary recovers secret key x: x = (s1*k - H(m1)) * r^(-1) mod q
    long long r_inv = modInverse(r1, q);
    long long recovered_x = (((s1_reuse * recovered_k - hashMsg) % q + q) % q * r_inv) % q;

    printf("   Adversary calculation:\n");
    printf("   - Extracted ephemeral key k = %lld\n", recovered_k);
    printf("   - >>> EXTRACTED PRIVATE KEY x = %lld <<< (Actual: %lld)\n\n", recovered_x, x_secret);

    printf("Conclusion:\n");
    printf("  Unlike RSA which is deterministic (S = H(M)^d mod n), DSA requires\n");
    printf("  a fresh, cryptographically strong random k for EVERY signature.\n");
    printf("  Reusing k even once leads to total compromise of the private key!\n");
    printf("===============================================================\n");

    return 0;
}
