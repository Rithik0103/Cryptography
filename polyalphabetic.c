#include <stdio.h>
#include <string.h>

int main() {
    char key[100], plaintext[100], ciphertext[100];

    // Input the key
    printf("Enter the key: ");
    scanf("%s", key);

    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    // Encrypt the plaintext
    int i, j;
    int keyLength = strlen(key);

    for (i = 0, j = 0; i < strlen(plaintext); i++, j = (j + 1) % keyLength) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[j] - 'A';
            plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[j] - 'a';
            plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
        }
    }

    // Output the ciphertext
    printf("Ciphertext: %s\n", plaintext);

    // Decrypt the ciphertext
    for (i = 0, j = 0; i < strlen(plaintext); i++, j = (j + 1) % keyLength) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int shift = key[j] - 'A';
            plaintext[i] = (plaintext[i] - 'A' - shift + 26) % 26 + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[j] - 'a';
            plaintext[i] = (plaintext[i] - 'a' - shift + 26) % 26 + 'a';
        }
    }

    // Output the decrypted text
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

