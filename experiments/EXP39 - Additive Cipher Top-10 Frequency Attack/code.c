#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const double engFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749,  7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150,  1.974, 0.074
};

typedef struct {
    int key;
    double score;
    char text[500];
} Candidate;

void decryptCaesar(const char *in, int key, char *out) {
    int i;
    for (i = 0; in[i] != '\0'; i++) {
        if (isupper(in[i])) out[i] = (in[i] - 'A' - key + 26) % 26 + 'A';
        else if (islower(in[i])) out[i] = (in[i] - 'a' - key + 26) % 26 + 'a';
        else out[i] = in[i];
    }
    out[i] = '\0';
}

double scoreText(const char *text) {
    int counts[26] = {0};
    int total = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }
    if (total == 0) return 99999.0;
    double chi = 0.0;
    for (int i = 0; i < 26; i++) {
        double expected = total * (engFreq[i] / 100.0);
        double diff = counts[i] - expected;
        chi += (diff * diff) / expected;
    }
    return chi;
}

int main() {
    char ciphertext[500];
    Candidate candidates[26];

    printf("===============================================================\n");
    printf("   EXP 39: ADDITIVE CIPHER TOP-10 FREQUENCY ATTACK             \n");
    printf("===============================================================\n\n");

    printf("Enter Ciphertext: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) return 1;
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    for (int k = 0; k < 26; k++) {
        candidates[k].key = k;
        decryptCaesar(ciphertext, k, candidates[k].text);
        candidates[k].score = scoreText(candidates[k].text);
    }

    // Sort ascending by chi-square score
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25 - i; j++) {
            if (candidates[j].score > candidates[j + 1].score) {
                Candidate t = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = t;
            }
        }
    }

    printf("\n============= TOP 10 RANKED PLAINTEXTS =============\n");
    printf("Rank | Shift Key | Chi-Square | Candidate Plaintext\n");
    printf("-----+-----------+------------+--------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf(" #%2d |    %2d     | %10.2f | %s\n", 
               i + 1, candidates[i].key, candidates[i].score, candidates[i].text);
    }
    printf("====================================================\n");

    return 0;
}
