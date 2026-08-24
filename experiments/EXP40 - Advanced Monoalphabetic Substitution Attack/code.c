#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char engOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char ch;
    int count;
} Freq;

int cmp(const void *a, const void *b) {
    return ((Freq *)b)->count - ((Freq *)a)->count;
}

void decryptWithMapping(const char *cipher, int shift, char *out) {
    Freq freq[26];
    for (int i = 0; i < 26; i++) {
        freq[i].ch = 'A' + i;
        freq[i].count = 0;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) freq[toupper(cipher[i]) - 'A'].count++;
    }

    qsort(freq, 26, sizeof(Freq), cmp);

    char map[26];
    for (int i = 0; i < 26; i++) {
        int target = (i + shift) % 26;
        map[freq[i].ch - 'A'] = engOrder[target];
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isupper(cipher[i])) out[i] = map[cipher[i] - 'A'];
        else if (islower(cipher[i])) out[i] = tolower(map[cipher[i] - 'a']);
        else out[i] = cipher[i];
    }
    out[strlen(cipher)] = '\0';
}

int main() {
    char ciphertext[500], plain[500];

    printf("===============================================================\n");
    printf("   EXP 40: ADVANCED MONOALPHABETIC SUBSTITUTION ATTACK         \n");
    printf("===============================================================\n\n");

    printf("Enter Ciphertext: ");
    if (fgets(ciphertext, sizeof(ciphertext), stdin) == NULL) return 1;
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("\nTop 10 Automated Candidate Plaintexts (Descending Likelihood):\n\n");
    for (int rank = 0; rank < 10; rank++) {
        decryptWithMapping(ciphertext, rank, plain);
        printf("[%2d] Alignment Permutation %2d:\n     %s\n\n", rank + 1, rank, plain);
    }
    printf("===============================================================\n");

    return 0;
}
