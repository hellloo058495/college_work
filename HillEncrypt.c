#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 26

void matrixMultiply(int key[2][2], int block[2], int result[2]) {
    result[0] = (key[0][0] * block[0] + key[0][1] * block[1]) % MOD;
    result[1] = (key[1][0] * block[0] + key[1][1] * block[1]) % MOD;
}

void encrypt(const char *message, int key[2][2]) {
    int len = strlen(message);
    int blocks[len / 2][2];

    for (int i = 0; i < len; i += 2) {
        blocks[i / 2][0] = message[i] - 'a';
        blocks[i / 2][1] = (i + 1 < len) ? message[i + 1] - 'a' : 0;

        int result[2];
        matrixMultiply(key, blocks[i / 2], result);

        printf("%c%c", result[0] + 'a', result[1] + 'a');
    }
    printf("\n");
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

void decrypt(const char *ciphertext, int key[2][2]) {
    int keyInverse[2][2];
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;

    int detInverse = modInverse(determinant, MOD);
    if (detInverse == -1) {
        printf("Key matrix is not invertible. Cannot decrypt.\n");
        return;
    }

    keyInverse[0][0] = (key[1][1] * detInverse) % MOD;
    keyInverse[0][1] = ((-key[0][1] + MOD) * detInverse) % MOD;
    keyInverse[1][0] = ((-key[1][0] + MOD) * detInverse) % MOD;
    keyInverse[1][1] = (key[0][0] * detInverse) % MOD;

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        int block[2] = {ciphertext[i] - 'a', ciphertext[i + 1] - 'a'};
        int result[2];

        matrixMultiply(keyInverse, block, result);

        printf("%c%c", result[0] + 'a', result[1] + 'a');
    }
    printf("\n");
}

int main() {
    int key[2][2] = {{5, 4}, {2, 3}};
    char message[] = "hi";
    
    printf("Original Message: %s\n", message);
    
    printf("Encrypted Message: ");
    encrypt(message, key);
    
    char ciphertext[] = "lj";
    printf("Ciphertext: %s\n", ciphertext);
    
    printf("Decrypted Message: ");
    decrypt(ciphertext, key);

    return 0;
}

