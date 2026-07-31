#include <stdio.h>
#include <string.h>

int main() {
    char plaintext[100], ciphertext[100];
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char substitute[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, j;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            for (j = 0; j < 26; j++) {
                if (plaintext[i] == alphabet[j]) {
                    ciphertext[i] = substitute[j];
                    break;
                }
            }
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            for (j = 0; j < 26; j++) {
                if (plaintext[i] == alphabet[j] + 32) {
                    ciphertext[i] = substitute[j] + 32;
                    break;
                }
            }
        }
        else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Encrypted message: %s", ciphertext);

    return 0;
}


