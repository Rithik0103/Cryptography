#include <stdio.h>
#include <string.h>

int main() {
    char key[100], plaintext[100], ciphertext[100];
    int keyLength, textLength,i,j;

    // Input the key
    printf("Enter the key: ");
    scanf("%s", key);
    keyLength = strlen(key);

    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
    textLength = strlen(plaintext);

    // Encrypt the plaintext
    printf("Ciphertext: ");
    for (i = 0, j = 0; i < textLength; i++) {
        char currentChar = plaintext[i];

        if (currentChar >= 'A' && currentChar <= 'Z') {
            ciphertext[i] = ((currentChar - 'A' + key[j % keyLength] - 'A') % 26) + 'A';
            j++;
        } else if (currentChar >= 'a' && currentChar <= 'z') {
            ciphertext[i] = ((currentChar - 'a' + key[j % keyLength] - 'A') % 26) + 'a';
            j++;
        } else {
            ciphertext[i] = currentChar; // Preserve non-alphabetic characters
        }

        printf("%c", ciphertext[i]);
    }

    printf("\n");

    // Decrypt the ciphertext
    printf("Decrypted text: ");
    for (i = 0, j = 0; i < textLength; i++) {
        char currentChar = ciphertext[i];

        if (currentChar >= 'A' && currentChar <= 'Z') {
            plaintext[i] = ((currentChar - 'A' - (key[j % keyLength] - 'A') + 26) % 26) + 'A';
            j++;
        } else if (currentChar >= 'a' && currentChar <= 'z') {
            plaintext[i] = ((currentChar - 'a' - (key[j % keyLength] - 'A') + 26) % 26) + 'a';
            j++;
        } else {
            plaintext[i] = currentChar; // Preserve non-alphabetic characters
        }

        printf("%c", plaintext[i]);
    }

    printf("\n");

    return 0;
}

