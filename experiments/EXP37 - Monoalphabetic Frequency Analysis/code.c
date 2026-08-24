#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char englishFreqOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char letter;
    int count;
} LetterCount;

int compare(const void *a, const void *b) {
    return ((LetterCount *)b)->count - ((LetterCount *)a)->count;
}

void solve(const char *cipher, char *plain, int offset) {
    LetterCount counts[26];
    for (int i = 0; i < 26; i++) {
        counts[i].letter = 'A' + i;
        counts[i].count = 0;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) counts[toupper(cipher[i]) - 'A'].count++;
    }

    qsort(counts, 26, sizeof(LetterCount), compare);

    char map[26];
    for (int i = 0; i < 26; i++) {
        int idx = (i + offset) % 26;
        map[counts[i].letter - 'A'] = englishFreqOrder[idx];
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isupper(cipher[i])) plain[i] = map[cipher[i] - 'A'];
        else if (islower(cipher[i])) plain[i] = tolower(map[cipher[i] - 'a']);
        else plain[i] = cipher[i];
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char cipher[500], plain[500];
    int topN = 10;

    printf("===============================================================\n");
    printf("   EXP 37: MONOALPHABETIC CIPHER FREQUENCY ATTACK              \n");
    printf("===============================================================\n\n");

    printf("Enter Ciphertext: ");
    if (fgets(cipher, sizeof(cipher), stdin) == NULL) return 1;
    cipher[strcspn(cipher, "\n")] = '\0';

    printf("\nGenerating top %d candidate plaintexts:\n\n", topN);
    for (int i = 0; i < topN; i++) {
        solve(cipher, plain, i);
        printf("Rank #%2d (Frequency Alignment Offset %d):\n  %s\n\n", i + 1, i, plain);
    }
    printf("===============================================================\n");

    return 0;
}
