#include <stdio.h>
#include <string.h>
#include <ctype.h>
//affine ceaser cipher
// Function to find modular inverse of a
int modInverse(int a)
{
    int i;
    for(i = 1; i < 26; i++)
    {
        if((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main()
{
    char text[100], encrypt[100], decrypt[100];
    int a, b, i;

    printf("Enter Plain Text: ");
    scanf("%s", text);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    if(modInverse(a) == -1)
    {
        printf("Invalid value of a! It has no modular inverse.\n");
        return 0;
    }

    // Encryption
    for(i = 0; text[i] != '\0'; i++)
    {
        if(isalpha(text[i]))
        {
            char ch = toupper(text[i]);
            int p = ch - 'A';
            encrypt[i] = ((a * p + b) % 26) + 'A';
        }
        else
            encrypt[i] = text[i];
    }
    encrypt[i] = '\0';

    printf("\nEncrypted Text : %s\n", encrypt);

    // Decryption
    int a_inv = modInverse(a);

    for(i = 0; encrypt[i] != '\0'; i++)
    {
        if(isalpha(encrypt[i]))
        {
            int c = encrypt[i] - 'A';
            decrypt[i] = ((a_inv * ((c - b + 26) % 26)) % 26) + 'A';
        }
        else
            decrypt[i] = encrypt[i];
    }
    decrypt[i] = '\0';

    printf("Decrypted Text : %s\n", decrypt);

    return 0;
}
