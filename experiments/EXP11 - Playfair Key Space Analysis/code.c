#include <stdio.h>
#include <math.h>

// Calculation of factorial as double
double factorial(int n) {
    double f = 1.0;
    for (int i = 2; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main() {
    printf("===============================================================\n");
    printf("      EXP 11: PLAYFAIR CIPHER KEY SPACE ANALYSIS               \n");
    printf("===============================================================\n\n");

    printf("1. Theoretical Total Playfair Keys:\n");
    printf("   - The 5x5 matrix contains 25 distinct letters (I/J combined).\n");
    printf("   - Total permutations of 25 letters = 25!\n\n");

    double fact25 = factorial(25);
    double power2_total = log2(fact25);

    printf("   25! = %.6e\n", fact25);
    printf("   In powers of 2:\n");
    printf("   25! ≈ 2^(%.2f)\n\n", power2_total);

    printf("---------------------------------------------------------------\n");
    printf("2. Effectively Unique Playfair Keys (Accounting for Symmetries):\n");
    printf("   - Symmetries that produce identical ciphertext:\n");
    printf("     * Cyclic shift of rows (5 possibilities)\n");
    printf("     * Cyclic shift of columns (5 possibilities)\n");
    printf("     * Total equivalent configurations per key = 5 x 5 = 25.\n");
    printf("   - Effectively unique keys = 25! / 25 = 24!\n\n");

    double fact24 = factorial(24);
    double power2_unique = log2(fact24);

    printf("   24! = %.6e\n", fact24);
    printf("   In powers of 2:\n");
    printf("   24! ≈ 2^(%.2f)\n\n", power2_unique);

    printf("---------------------------------------------------------------\n");
    printf("Summary:\n");
    printf("  - Total possible Playfair matrices : 25! ≈ 1.55 x 10^25 ≈ 2^84\n");
    printf("  - Effectively unique keys          : 24! ≈ 6.20 x 10^23 ≈ 2^79\n");
    printf("===============================================================\n");

    return 0;
}
