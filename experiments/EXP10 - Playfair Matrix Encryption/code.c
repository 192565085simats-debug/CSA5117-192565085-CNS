#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Specified 5x5 Playfair matrix
char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPosition(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void prepareText(const char in[], char out[]) {
    int len = 0;
    char temp[500];

    for (int i = 0; in[i] != '\0'; i++) {
        if (isalpha(in[i])) {
            char ch = toupper(in[i]);
            if (ch == 'J') ch = 'I';
            temp[len++] = ch;
        }
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        out[j++] = temp[i];
        if (i + 1 < len && temp[i] == temp[i + 1]) {
            out[j++] = 'X';
        }
    }
    if (j % 2 != 0) {
        out[j++] = 'X';
    }
    out[j] = '\0';
}

void encryptPair(char p1, char p2, char *c1, char *c2) {
    int r1, col1, r2, col2;
    findPosition(p1, &r1, &col1);
    findPosition(p2, &r2, &col2);

    if (r1 == r2) {
        *c1 = matrix[r1][(col1 + 1) % 5];
        *c2 = matrix[r2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        *c1 = matrix[(r1 + 1) % 5][col1];
        *c2 = matrix[(r2 + 1) % 5][col2];
    } else {
        *c1 = matrix[r1][col2];
        *c2 = matrix[r2][col1];
    }
}

int main() {
    const char *plaintext = "Must see you over Cadogan West. Coming at once.";
    char prepared[500], encrypted[500];

    printf("====================================================\n");
    printf("      EXP 10: PLAYFAIR MATRIX ENCRYPTION            \n");
    printf("====================================================\n\n");

    printf("Specified Playfair Matrix:\n");
    printf("  M   F   H  I/J  K\n");
    printf("  U   N   O   P   Q\n");
    printf("  Z   V   W   X   Y\n");
    printf("  E   L   A   R   G\n");
    printf("  D   S   T   B   C\n\n");

    printf("Original Message:\n  \"%s\"\n\n", plaintext);

    prepareText(plaintext, prepared);
    printf("Prepared Text (with 'X' fillers & paired digraphs):\n  ");
    for (int i = 0; prepared[i] != '\0'; i += 2) {
        printf("%c%c ", prepared[i], prepared[i + 1]);
    }
    printf("\n\n");

    int encLen = 0;
    printf("Digraph Encryption Steps:\n");
    for (int i = 0; prepared[i] != '\0'; i += 2) {
        encryptPair(prepared[i], prepared[i + 1], &encrypted[encLen], &encrypted[encLen + 1]);
        printf("  %c%c -> %c%c\n", prepared[i], prepared[i + 1], encrypted[encLen], encrypted[encLen + 1]);
        encLen += 2;
    }
    encrypted[encLen] = '\0';

    printf("\nFinal Ciphertext:\n  ");
    for (int i = 0; encrypted[i] != '\0'; i += 2) {
        printf("%c%c ", encrypted[i], encrypted[i + 1]);
    }
    printf("\n\nComplete Ciphertext String:\n  %s\n", encrypted);

    return 0;
}
