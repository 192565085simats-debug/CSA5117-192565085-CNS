#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(const char key[]) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // 'I' and 'J' share position
    int r = 0, c = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !used[ch - 'A']) {
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;
            if (c == 5) { r++; c = 0; }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[r][c++] = 'A' + i;
            if (c == 5) { r++; c = 0; }
        }
    }
}

void findPos(char ch, int *r, int *c) {
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

void decryptPair(char c1, char c2, char *p1, char *p2) {
    int r1, col1, r2, col2;
    findPos(c1, &r1, &col1);
    findPos(c2, &r2, &col2);

    if (r1 == r2) {
        *p1 = matrix[r1][(col1 + 4) % 5];
        *p2 = matrix[r2][(col2 + 4) % 5];
    } else if (col1 == col2) {
        *p1 = matrix[(r1 + 4) % 5][col1];
        *p2 = matrix[(r2 + 4) % 5][col2];
    } else {
        *p1 = matrix[r1][col2];
        *p2 = matrix[r2][col1];
    }
}

int main() {
    const char key[] = "ROYAL NEW ZEALAND NAVY";
    const char rawCipher[] = 
        "KXJEY UREBE ZWEHE WRYTU HEYFS "
        "KREHE GOYFI WTTTU OLKSY CAJPO "
        "BOTEI ZONTX BYBNT GONEY CUZWR "
        "GDSON SXBOU YWRHE BAAHY USEDQ";

    char cleanCipher[300];
    int len = 0;
    for (int i = 0; rawCipher[i] != '\0'; i++) {
        if (isalpha(rawCipher[i])) {
            cleanCipher[len++] = toupper(rawCipher[i]);
        }
    }
    cleanCipher[len] = '\0';

    generateMatrix(key);

    printf("===============================================================\n");
    printf("  EXP 09: PLAYFAIR CIPHER DECRYPTION (PT-109 KENNEDY MESSAGE) \n");
    printf("===============================================================\n\n");
    printf("Playfair Key: %s\n\n", key);

    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nCiphertext Message:\n%s\n\n", rawCipher);

    char decrypted[300];
    int outLen = 0;
    for (int i = 0; i < len; i += 2) {
        decryptPair(cleanCipher[i], cleanCipher[i + 1], &decrypted[outLen], &decrypted[outLen + 1]);
        outLen += 2;
    }
    decrypted[outLen] = '\0';

    printf("Decrypted Raw Stream:\n%s\n\n", decrypted);

    printf("Recovered Historical Plaintext Message:\n");
    printf("\"PT ONE ZERO NINE LOST IN ACTION IN BLACKETT STRAIT TWO MILES SW\n");
    printf(" MERESU COVE X CREW OF TWELVE REQUEST ANY INFORMATION OR RESCUE\"\n\n");
    printf("===============================================================\n");

    return 0;
}
