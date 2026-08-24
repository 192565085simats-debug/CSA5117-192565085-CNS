#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using Caesar Cipher
void encrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        } else if (islower(text[i])) {
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
        }
    }
}

// Function to decrypt ciphertext using Caesar Cipher
void decrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' - key + 26) % 26 + 'A';
        } else if (islower(text[i])) {
            text[i] = (text[i] - 'a' - key + 26) % 26 + 'a';
        }
    }
}

int main() {
    char message[500];
    int key, choice;

    printf("========================================\n");
    printf("        EXP 01: CAESAR CIPHER           \n");
    printf("========================================\n");

    printf("Enter a message: ");
    if (fgets(message, sizeof(message), stdin) == NULL) return 1;
    message[strcspn(message, "\n")] = '\0';

    printf("Enter shift key k (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25) {
        printf("Invalid key! Key must be in range 1 to 25.\n");
        return 1;
    }

    printf("\nSelect Operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice (1/2): ");
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
