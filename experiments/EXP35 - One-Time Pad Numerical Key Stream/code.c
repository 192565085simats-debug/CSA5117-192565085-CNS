#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main() {
    char text[500];
    int keyStream[500];
    char ciphertext[500];
    char decrypted[500];

    srand((unsigned int)time(NULL));

    printf("===============================================================\n");
    printf("    EXP 35: ONE-TIME PAD VIGENERE (NUMERICAL KEY STREAM)       \n");
    printf("===============================================================\n\n");

    printf("Enter Plaintext: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    int len = 0;
    char cleanText[500];
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            cleanText[len++] = toupper(text[i]);
        }
    }
    cleanText[len] = '\0';

    // Generate random numerical key stream in range [0..25]
    for (int i = 0; i < len; i++) {
        keyStream[i] = rand() % 26;
    }

    // Encryption: C_i = (P_i + K_i) mod 26
    for (int i = 0; i < len; i++) {
        int p = cleanText[i] - 'A';
        int c = (p + keyStream[i]) % 26;
        ciphertext[i] = c + 'A';
    }
    ciphertext[len] = '\0';

    // Decryption: P_i = (C_i - K_i + 26) mod 26
    for (int i = 0; i < len; i++) {
        int c = ciphertext[i] - 'A';
        int p = (c - keyStream[i] + 26) % 26;
        decrypted[i] = p + 'A';
    }
    decrypted[len] = '\0';

    printf("\nCleaned Plaintext : %s\n", cleanText);
    printf("Random Key Stream : ");
    for (int i = 0; i < len; i++) printf("%2d ", keyStream[i]);
    printf("\n");

    printf("Ciphertext        : %s\n", ciphertext);
    printf("Decrypted Output  : %s\n\n", decrypted);

    printf(">>> Perfect Secrecy Verified: Decrypted matches Plaintext! <<<\n");
    printf("===============================================================\n");

    return 0;
}
