#include <stdio.h>

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long extendedGCD(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    long long x1, y1;
    long long g = extendedGCD(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return g;
}

int main() {
    printf("===============================================================\n");
    printf("      EXP 28: DIFFIE-HELLMAN PROTOCOL VARIATION ANALYSIS       \n");
    printf("===============================================================\n\n");

    printf("1. Standard Diffie-Hellman (g^x mod q):\n");
    printf("   - Alice chooses secret x_A, sends Y_A = g^(x_A) mod q\n");
    printf("   - Bob chooses secret x_B, sends Y_B = g^(x_B) mod q\n");
    printf("   - Shared Key K = (Y_B)^(x_A) = (Y_A)^(x_B) = g^(x_A * x_B) mod q\n");
    printf("   - Security relies on Discrete Logarithm Problem (DLP).\n\n");

    printf("---------------------------------------------------------------\n");
    printf("2. Flawed Variant (x^a mod q for public constant a):\n");
    printf("   - Alice chooses secret x_A, sends Y_A = (x_A)^a mod q\n");
    printf("   - Bob chooses secret x_B, sends Y_B = (x_B)^a mod q\n\n");

    long long q = 353;  // Prime
    long long a = 11;   // Public exponent (coprime to q-1 = 352)
    long long x_A = 45; // Alice's secret
    long long x_B = 89; // Bob's secret

    long long y_A = modExp(x_A, a, q);
    long long y_B = modExp(x_B, a, q);

    printf("   Alice sends Y_A = %lld^%lld mod %lld = %lld\n", x_A, a, q, y_A);
    printf("   Bob sends   Y_B = %lld^%lld mod %lld = %lld\n\n", x_B, a, q, y_B);

    // Key agreement method: K = (Y_A * Y_B) mod q = (x_A * x_B)^a mod q
    long long K_Alice = modExp((x_A * x_B) % q, a, q);
    long long K_Bob = (y_A * y_B) % q;
    printf("   Key Agreement: Shared Key K = (Y_A * Y_B) mod q = %lld\n\n", K_Bob);

    printf("================ EVE'S ATTACK ================\n");
    printf("Can Eve find the secret numbers? YES, EASILY!\n");
    printf("Since 'a' is known and gcd(a, q - 1) = 1, Eve computes modular inverse\n");
    printf("  d = a^(-1) mod (q - 1)\n");

    long long x_inv, y_inv;
    extendedGCD(a, q - 1, &x_inv, &y_inv);
    long long d = (x_inv % (q - 1) + (q - 1)) % (q - 1);

    printf("  Inverse exponent d = %lld^(-1) mod %lld = %lld\n", a, q - 1, d);

    // Eve recovers Alice's and Bob's secrets via a-th root extraction:
    long long recovered_xA = modExp(y_A, d, q);
    long long recovered_xB = modExp(y_B, d, q);

    printf("  Eve extracts Alice's secret x_A = (Y_A)^d mod q = %lld\n", recovered_xA);
    printf("  Eve extracts Bob's secret   x_B = (Y_B)^d mod q = %lld\n", recovered_xB);
    printf("  Eve computes Shared Key K   = %lld\n\n", modExp((recovered_xA * recovered_xB) % q, a, q));

    printf("Conclusion: The variant is completely broken because calculating\n");
    printf("discrete roots is computationally trivial when modulus order is known.\n");
    printf("===============================================================\n");

    return 0;
}
