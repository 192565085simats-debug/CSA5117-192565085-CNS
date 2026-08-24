#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherAlphabet(const char keyword[], char cipherAlphabet[]) {
    int used[26] = {0};
    int j = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipherAlphabet[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            cipherAlphabet[j++] = 'A' + i;
        }
    }
    cipherAlphabet[26] = '\0';
}

void encrypt(char text[], const char cipherAlphabet[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = cipherAlphabet[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(cipherAlphabet[text[i] - 'a']);
        }
    }
}

void decrypt(char text[], const char cipherAlphabet[]) {
    char plainAlphabet[26];
    for (int i = 0; i < 26; i++) {
        plainAlphabet[cipherAlphabet[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = plainAlphabet[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(plainAlphabet[text[i] - 'a']);
        }
    }
}

int main() {
    char keyword[100] = "CIPHER";
    char cipherAlphabet[27];
    char text[500];
    int choice;

    printf("============================================================\n");
    printf("   EXP 08: KEYWORD BASED MONOALPHABETIC CIPHER              \n");
    printf("============================================================\n");

    printf("Enter Keyword (default 'CIPHER'): ");
    if (fgets(keyword, sizeof(keyword), stdin) != NULL && keyword[0] != '\n') {
        keyword[strcspn(keyword, "\n")] = '\0';
    } else {
        strcpy(keyword, "CIPHER");
    }

    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("\nKeyword         : %s\n", keyword);
    printf("Plain Alphabet  : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher Alphabet : %s\n\n", cipherAlphabet);

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("\n1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(text, cipherAlphabet);
        printf("\nEncrypted Ciphertext: %s\n", text);
    } else if (choice == 2) {
        decrypt(text, cipherAlphabet);
        printf("\nDecrypted Plaintext : %s\n", text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
