#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

// Generate Playfair 5x5 matrix from key
void generateMatrix(const char key[]) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // 'I' and 'J' share a position
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;
            if (col == 5) {
                row++;
                col = 0;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[row][col++] = 'A' + i;
            if (col == 5) {
                row++;
                col = 0;
            }
        }
    }
}

// Find position of a character in the matrix
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

// Format plaintext for Playfair encryption
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

void encrypt(char text[], char result[]) {
    int len = strlen(text);
    int k = 0;
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            result[k++] = matrix[r1][(c1 + 1) % 5];
            result[k++] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            result[k++] = matrix[(r1 + 1) % 5][c1];
            result[k++] = matrix[(r2 + 1) % 5][c2];
        } else {
            result[k++] = matrix[r1][c2];
            result[k++] = matrix[r2][c1];
        }
    }
    result[k] = '\0';
}

void decrypt(char text[], char result[]) {
    int len = strlen(text);
    int k = 0;
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            result[k++] = matrix[r1][(c1 + 4) % 5];
            result[k++] = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            result[k++] = matrix[(r1 + 4) % 5][c1];
            result[k++] = matrix[(r2 + 4) % 5][c2];
        } else {
            result[k++] = matrix[r1][c2];
            result[k++] = matrix[r2][c1];
        }
    }
    result[k] = '\0';
}

int main() {
    char key[100], text[500], prepared[500], output[500];
    int choice;

    printf("========================================\n");
    printf("        EXP 03: PLAYFAIR CIPHER         \n");
    printf("========================================\n");

    printf("Enter Keyword: ");
    if (fgets(key, sizeof(key), stdin) == NULL) return 1;
    key[strcspn(key, "\n")] = '\0';

    generateMatrix(key);

    printf("\nPlayfair 5x5 Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter Text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    if (choice == 1) {
        prepareText(text, prepared);
        printf("Prepared Text (digraphs): %s\n", prepared);
        encrypt(prepared, output);
        printf("Encrypted Ciphertext   : %s\n", output);
    } else if (choice == 2) {
        int k = 0;
        for (int i = 0; text[i] != '\0'; i++) {
            if (isalpha(text[i])) prepared[k++] = toupper(text[i]);
        }
        prepared[k] = '\0';
        decrypt(prepared, output);
        printf("Decrypted Plaintext    : %s\n", output);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
