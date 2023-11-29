#include <stdio.h>
#include<string.h>

#define SIZE 3  // Size of the key matrix (adjust as needed)

int modInverse(int a, int m) {
	int x;
    a = a % m;
    for (x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

int main() {
	int i,j;
    int keyMatrix[SIZE][SIZE];
    char plaintext[100], ciphertext[100];
    int size;

    // Input the key matrix
    printf("Enter the key matrix (3x3):\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    // Input the plaintext
    printf("Enter the plaintext (in uppercase): ");
    scanf(" %[^\n]s", plaintext);
    size = strlen(plaintext);

    // Encrypt the plaintext
    int k;
    int encrypted[size];

    for (i = 0; i < size; i += SIZE) {
        for (j = 0; j < SIZE; j++) {
            encrypted[i + j] = 0;
            for (k = 0; k < SIZE; k++) {
                encrypted[i + j] += keyMatrix[j][k] * (plaintext[i + k] - 'A');
            }
            encrypted[i + j] %= 26;
        }
    }

    // Output the encrypted text
    printf("Ciphertext: ");
    for (i = 0; i < size; i++) {
        printf("%c", encrypted[i] + 'A');
    }
    printf("\n");

    // Decrypt the ciphertext
    int det = (keyMatrix[0][0] * keyMatrix[1][1] * keyMatrix[2][2] +
               keyMatrix[0][1] * keyMatrix[1][2] * keyMatrix[2][0] +
               keyMatrix[1][0] * keyMatrix[2][1] * keyMatrix[0][2] -
               keyMatrix[0][2] * keyMatrix[1][1] * keyMatrix[2][0] -
               keyMatrix[0][1] * keyMatrix[1][0] * keyMatrix[2][2] -
               keyMatrix[1][2] * keyMatrix[2][1] * keyMatrix[0][0]) % 26;

    int detInverse = modInverse(det, 26);
    if (detInverse == -1) {
        printf("Error: The key matrix is not invertible (det=0).\n");
        return 1;
    }

    int keyInverse[SIZE][SIZE];

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            keyInverse[i][j] = (((keyMatrix[(j + 1) % SIZE][(i + 1) % SIZE] * keyMatrix[(j + 2) % SIZE][(i + 2) % SIZE]) -
                                 (keyMatrix[(j + 1) % SIZE][(i + 2) % SIZE] * keyMatrix[(j + 2) % SIZE][(i + 1) % SIZE])) % 26 + 26) % 26;
        }
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            keyInverse[i][j] = (keyInverse[i][j] * detInverse) % 26;
        }
    }

    // Decrypt the ciphertext
    int decrypted[size];

    for (i = 0; i < size; i += SIZE) {
        for (j = 0; j < SIZE; j++) {
            decrypted[i + j] = 0;
            for (k = 0; k < SIZE; k++) {
                decrypted[i + j] += keyInverse[j][k] * (encrypted[i + k] % 26);
            }
            decrypted[i + j] = (decrypted[i + j] % 26 + 26) % 26;
        }
    }

    // Output the decrypted text
    printf("Decrypted text: ");
    for (i = 0; i < size; i++) {
        printf("%c", decrypted[i] + 'A');
    }
    printf("\n");

    return 0;
}

