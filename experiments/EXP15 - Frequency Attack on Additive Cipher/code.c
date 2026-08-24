#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Standard English letter frequencies (%)
const double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749,  7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150,  1.974, 0.074
};

typedef struct {
    int key;
    double score;
    char text[500];
} Candidate;

// Decrypt with Caesar shift
void decryptWithKey(const char *cipher, int key, char *plain) {
    int i;
    for (i = 0; cipher[i] != '\0'; i++) {
        if (isupper(cipher[i])) {
            plain[i] = (cipher[i] - 'A' - key + 26) % 26 + 'A';
        } else if (islower(cipher[i])) {
            plain[i] = (cipher[i] - 'a' - key + 26) % 26 + 'a';
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[i] = '\0';
}

// Calculate Chi-Squared statistic (lower is better match to English)
double calculateChiSquared(const char *text) {
    int count[26] = {0};
    int totalLetters = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[toupper(text[i]) - 'A']++;
            totalLetters++;
        }
    }

    if (totalLetters == 0) return 99999.0;

    double chiSquare = 0.0;
    for (int i = 0; i < 26; i++) {
        double expected = totalLetters * (englishFreq[i] / 100.0);
        double diff = count[i] - expected;
        chiSquare += (diff * diff) / expected;
    }

    return chiSquare;
}

int main() {
    char ciphertext[500];
    int topN = 10;
    Candidate candidates[26];

    printf("===============================================================\n");
    printf("   EXP 15: AUTOMATED FREQUENCY ATTACK ON ADDITIVE CIPHER       \n");
    printf("===============================================================\n\n");

    printf("Enter Ciphertext: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) return 1;
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("How many top plaintexts to display? (1-26, default 10): ");
    char numBuf[10];
    if (fgets(numBuf, sizeof(numBuf), stdin) != NULL && numBuf[0] != '\n') {
        sscanf(numBuf, "%d", &topN);
        if (topN < 1) topN = 1;
        if (topN > 26) topN = 26;
    }

    // Evaluate all 26 possible shift keys
    for (int k = 0; k < 26; k++) {
        candidates[k].key = k;
        decryptWithKey(ciphertext, k, candidates[k].text);
        candidates[k].score = calculateChiSquared(candidates[k].text);
    }

    // Sort candidates by Chi-Squared score in ascending order (best match first)
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25 - i; j++) {
            if (candidates[j].score > candidates[j + 1].score) {
                Candidate temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }

    printf("\n================ TOP %d CANDIDATE PLAINTEXTS ================\n", topN);
    printf("Rank | Key | Chi-Sq Score | Decrypted Candidate Text\n");
    printf("-----+-----+--------------+---------------------------------------\n");
    for (int i = 0; i < topN; i++) {
        printf(" #%2d | %3d | %12.2f | %s\n", 
               i + 1, candidates[i].key, candidates[i].score, candidates[i].text);
    }
    printf("===============================================================\n");

    return 0;
}
