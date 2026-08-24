#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Polyalphabetic (Vigenere) Cipher Encryption
void encrypt(char text[], const char key[]) {
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
            j++;
        } else if (islower(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
            j++;
        }
    }
}

// Polyalphabetic (Vigenere) Cipher Decryption
void decrypt(char text[], const char key[]) {
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
            j++;
        } else if (islower(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
            j++;
        }
    }
}

int main() {
    char text[500], key[100];
    int choice;

    printf("====================================================\n");
    printf("     EXP 04: POLYALPHABETIC (VIGENERE) CIPHER       \n");
    printf("====================================================\n");

    printf("Enter Key (word): ");
    if (fgets(key, sizeof(key), stdin) == NULL) return 1;
    key[strcspn(key, "\n")] = '\0';

    printf("Enter Message: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("\n1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encrypt(text, key);
        printf("\nEncrypted Ciphertext: %s\n", text);
    } else if (choice == 2) {
        decrypt(text, key);
        printf("\nDecrypted Plaintext : %s\n", text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
