#include <stdio.h>
#include <math.h>

// Extended Euclidean Algorithm to find modular inverse
int extendedGCD(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedGCD(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int modInverse(int e, int phi) {
    int x, y;
    int g = extendedGCD(e, phi, &x, &y);
    if (g != 1) return -1;
    return (x % phi + phi) % phi;
}

int main() {
    int e = 31;
    int n = 3599;

    printf("===============================================================\n");
    printf("         EXP 24: RSA PRIVATE KEY GENERATION                    \n");
    printf("===============================================================\n\n");

    printf("Given Public Key: e = %d, n = %d\n\n", e, n);

    // Step 1: Trial-and-error factoring of n
    printf("Step 1: Finding Prime Factors p and q of n = %d:\n", n);
    int p = 0, q = 0;
    int limit = (int)sqrt(n);

    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    printf("  Found Factors: p = %d, q = %d\n", p, q);
    printf("  Verification : %d * %d = %d\n\n", p, q, p * q);

    // Step 2: Calculate Euler's Totient phi(n)
    int phi = (p - 1) * (q - 1);
    printf("Step 2: Calculate Euler's Totient phi(n):\n");
    printf("  phi(n) = (p - 1) * (q - 1) = (%d - 1) * (%d - 1)\n", p, q);
    printf("  phi(n) = %d * %d = %d\n\n", p - 1, q - 1, phi);

    // Step 3: Compute private key d using Extended Euclidean Algorithm
    printf("Step 3: Finding Private Key d = e^(-1) mod phi(n):\n");
    printf("  Solve: (31 * d) = 1 (mod %d)\n", phi);

    int d = modInverse(e, phi);

    printf("  Extended Euclidean Algorithm Result: d = %d\n\n", d);
    printf("  Verification: (%d * %d) mod %d = %lld mod %d = %lld\n\n", 
           e, d, phi, (long long)e * d, phi, ((long long)e * d) % phi);

    printf("================ RESULT ================\n");
    printf("  Public Key  (e, n) = (%d, %d)\n", e, n);
    printf("  Private Key (d, n) = (%d, %d)\n", d, n);
    printf("========================================\n");

    return 0;
}
