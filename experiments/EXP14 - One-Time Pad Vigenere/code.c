#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    const char *plaintext1 = "sendmoremoney";
    int keyStream1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int len = strlen(plaintext1);
    char ciphertext[50];

    printf("===============================================================\n");
    printf("      EXP 14: ONE-TIME PAD / VIGENERE NUMERICAL KEY STREAM     \n");
    printf("===============================================================\n\n");

    printf("Part (a): Encrypt plaintext \"send more money\" with key stream:\n");
    printf("Key Stream: ");
    for (int i = 0; i < len; i++) printf("%d ", keyStream1[i]);
    printf("\n\n");

    printf("Calculation Details:\n");
    for (int i = 0; i < len; i++) {
        int p = plaintext1[i] - 'a';
        int k = keyStream1[i];
        int c = (p + k) % 26;
        ciphertext[i] = c + 'A';
        printf("  p[%c]=%2d  +  k=%2d  =>  c=%2d (%c)\n", plaintext1[i], p, k, c, ciphertext[i]);
    }
    ciphertext[len] = '\0';

    printf("\nResulting Ciphertext: %s\n\n", ciphertext);
    printf("---------------------------------------------------------------\n");

    printf("Part (b): Find key stream to decrypt ciphertext to \"cash not needed\":\n");
    const char *plaintext2 = "cashnotneeded";
    int keyStream2[50];

    printf("Target Plaintext : %s\n\n", plaintext2);
    printf("Key Calculation formula: key = (ciphertext - target_plain + 26) mod 26\n\n");

    for (int i = 0; i < len; i++) {
        int c = ciphertext[i] - 'A';
        int p2 = plaintext2[i] - 'a';
        keyStream2[i] = (c - p2 + 26) % 26;
        printf("  c[%c]=%2d  -  p[%c]=%2d  =>  new_key = %2d\n", ciphertext[i], c, plaintext2[i], p2, keyStream2[i]);
    }

    printf("\nRequired Key Stream for \"cash not needed\":\n  ");
    for (int i = 0; i < len; i++) {
        printf("%d ", keyStream2[i]);
    }
    printf("\n\nConclusion:\n");
    printf("  Because of One-Time Pad's perfect secrecy, ANY plaintext of the same\n");
    printf("  length can be produced from the same ciphertext with a different valid key.\n");
    printf("===============================================================\n");

    return 0;
}
