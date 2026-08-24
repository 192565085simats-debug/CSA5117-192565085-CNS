#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// English frequency order (from most to least frequent)
const char englishOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char letter;
    int count;
} FreqPair;

int compareFreq(const void *a, const void *b) {
    FreqPair *p1 = (FreqPair *)a;
    FreqPair *p2 = (FreqPair *)b;
    return p2->count - p1->count; // descending
}

void attack(const char *cipher, char *plain, int shiftOffset) {
    FreqPair pairs[26];
    for (int i = 0; i < 26; i++) {
        pairs[i].letter = 'A' + i;
        pairs[i].count = 0;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            pairs[toupper(cipher[i]) - 'A'].count++;
        }
    }

    qsort(pairs, 26, sizeof(FreqPair), compareFreq);

    // Map sorted ciphertext letters to English frequency with candidate shift
    char map[26];
    for (int i = 0; i < 26; i++) {
        int targetIdx = (i + shiftOffset) % 26;
        map[pairs[i].letter - 'A'] = englishOrder[targetIdx];
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isupper(cipher[i])) {
            plain[i] = map[cipher[i] - 'A'];
        } else if (islower(cipher[i])) {
            plain[i] = tolower(map[cipher[i] - 'a']);
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char ciphertext[500];
    char candidate[500];
    int topN = 10;

    printf("===============================================================\n");
    printf("   EXP 16: FREQUENCY ATTACK ON MONOALPHABETIC CIPHER           \n");
    printf("===============================================================\n\n");

    printf("Enter Ciphertext: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) return 1;
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter number of top candidate plaintexts to generate (default 10): ");
    char buf[10];
    if (fgets(buf, sizeof(buf), stdin) != NULL && buf[0] != '\n') {
        sscanf(buf, "%d", &topN);
        if (topN < 1) topN = 1;
        if (topN > 26) topN = 26;
    }

    printf("\n================ TOP %d CANDIDATE PLAINTEXTS ================\n", topN);
    for (int i = 0; i < topN; i++) {
        attack(ciphertext, candidate, i);
        printf("Candidate #%2d (Offset %d):\n  %s\n\n", i + 1, i, candidate);
    }
    printf("===============================================================\n");

    return 0;
}
