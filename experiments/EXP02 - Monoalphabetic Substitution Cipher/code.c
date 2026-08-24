#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Standard alphabet and default substitution alphabet
const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DEFAULT_SUB[] = "QWERTYUIOPASDFGHJKLZXCVBNM";

void encrypt(char text[], const char key[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = key[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(key[toupper(text[i]) - 'A']);
        }
    }
}

void decrypt(char text[], const char key[]) {
    char reverse_key[26];
    for (int i = 0; i < 26; i++) {
        reverse_key[key[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = reverse_key[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(reverse_key[toupper(text[i]) - 'A']);
        }
    }
}

int main() {
    char message[500];
    char key[27];
    int choice;

    printf("====================================================\n");
    printf("   EXP 02: MONOALPHABETIC SUBSTITUTION CIPHER       \n");
    printf("====================================================\n");

    printf("1. Use default QWERTY substitution key\n");
    printf("2. Enter custom 26-letter substitution key\n");
    printf("Choice: ");
    int keyChoice;
    scanf("%d", &keyChoice);
    getchar(); // consume newline

    if (keyChoice == 2) {
        printf("Enter 26-letter unique substitution alphabet: ");
        scanf("%26s", key);
        getchar();
        for (int i = 0; i < 26; i++) key[i] = toupper(key[i]);
    } else {
        strcpy(key, DEFAULT_SUB);
    }

    printf("\nPlain Alphabet : %s\n", ALPHABET);
    printf("Cipher Alphabet: %s\n\n", key);

    printf("Enter message: ");
    if (fgets(message, sizeof(message), stdin) == NULL) return 1;
    message[strcspn(message, "\n")] = '\0';

    printf("\n1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(message, key);
        printf("\nEncrypted Ciphertext: %s\n", message);
    } else if (choice == 2) {
        decrypt(message, key);
        printf("\nDecrypted Plaintext : %s\n", message);
    } else {
        printf("Invalid Choice!\n");
    }

    return 0;
}
