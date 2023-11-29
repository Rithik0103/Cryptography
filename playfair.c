#include <stdio.h>
#include <string.h>

#define SIZE 5

// Function to find the position of a character in the key matrix
void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';  // Replace 'J' with 'I' in the key matrix

    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (keyMatrix[*row][*col] == ch)
                return;
}

int main() {
    char key[26], keyMatrix[SIZE][SIZE];
    char plaintext[100], ciphertext[100], decryptedtext[100];

    // Input the key
    printf("Enter the key: ");
    scanf("%s", key);

    // Generate the key matrix
    int k = 0, i, j;
    char distinct[26] = {0};

    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'J' && !distinct[key[i] - 'A']) {
            distinct[key[i] - 'A'] = 1;
            keyMatrix[k / SIZE][k % SIZE] = key[i];
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !distinct[i]) {
            keyMatrix[k / SIZE][k % SIZE] = i + 'A';
            k++;
        }
    }

    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    if(strlen(plaintext)%2==1)
    {
    strcat(plaintext,"X");
	}

    // Encrypt the plaintext
    for (i = 0, j = 0; i < strlen(plaintext); i += 2, j += 2) {
        int row1, col1, row2, col2;
        findPosition(keyMatrix, plaintext[i], &row1, &col1);
        findPosition(keyMatrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[j] = keyMatrix[row1][(col1 + 1) % SIZE];
            ciphertext[j + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[j] = keyMatrix[(row1 + 1) % SIZE][col1];
            ciphertext[j + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[j] = keyMatrix[row1][col2];
            ciphertext[j + 1] = keyMatrix[row2][col1];
        }
    }
    ciphertext[j] = '\0';

    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    for (i = 0, j = 0; i < strlen(ciphertext); i += 2, j += 2) {
        int row1, col1, row2, col2;
        findPosition(keyMatrix, ciphertext[i], &row1, &col1);
        findPosition(keyMatrix, ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {
            decryptedtext[j] = keyMatrix[row1][(col1 - 1 + SIZE) % SIZE];
            decryptedtext[j + 1] = keyMatrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            decryptedtext[j] = keyMatrix[(row1 - 1 + SIZE) % SIZE][col1];
            decryptedtext[j + 1] = keyMatrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            decryptedtext[j] = keyMatrix[row1][col2];
            decryptedtext[j + 1] = keyMatrix[row2][col1];
        }
    }
    decryptedtext[j] = '\0';

    // Output the decrypted text
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

