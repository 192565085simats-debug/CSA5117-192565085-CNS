#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    printf("===============================================================\n");
    printf("      EXP 36: AFFINE CIPHER INVERTIBILITY & COLLISION PROOF    \n");
    printf("===============================================================\n\n");

    printf("Affine encryption function: E([a, b], p) = (a*p + b) mod 26\n");
    printf("Condition for one-to-one mapping (bijective): gcd(a, 26) == 1\n\n");

    printf("--- PART 1: Concrete Collision Example for a = 2, b = 3 ---\n");
    int a = 2, b = 3;
    printf("Formula: C = (2*p + 3) mod 26\n\n");

    for (int p = 0; p < 26; p++) {
        int c = (a * p + b) % 26;
        printf("  p = %2d ('%c') --> C = %2d ('%c')", p, 'A' + p, c, 'A' + c);
        if (p >= 13) {
            int coll_p = p - 13;
            printf("  <-- COLLISION with p=%2d ('%c')!", coll_p, 'A' + coll_p);
        }
        printf("\n");
    }

    printf("\n--- PART 2: Comprehensive Invertibility Audit for all a in [0..25] ---\n");
    printf("Value of a | gcd(a, 26) | Invertible? | Reason\n");
    printf("-----------+------------+-------------+----------------------------------\n");

    for (int test_a = 0; test_a < 26; test_a++) {
        int g = gcd(test_a, 26);
        if (g == 1) {
            printf("    %2d     |     %2d     |   YES (OK)  | Coprime to 26\n", test_a, g);
        } else {
            printf("    %2d     |     %2d     |   NO (FAIL) | Non-invertible: Multiple of %d\n", 
                   test_a, g, (test_a % 2 == 0) ? 2 : 13);
        }
    }

    printf("\nSummary:\n");
    printf("  Valid 12 values of a  : 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25\n");
    printf("  Invalid 14 values of a: 0, 2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24\n");
    printf("===============================================================\n");

    return 0;
}
