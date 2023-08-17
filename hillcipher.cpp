#include <iostream>
#include <string>
#include <vector>

// Function to calculate the determinant of a 2x2 matrix
int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to encrypt a message using Hill Cipher
std::string encrypt(const std::string &message, const std::vector<std::vector<int>> &key) {
    int mod = 26; // We're working with the English alphabet

    std::string encrypted = "";
    for (size_t i = 0; i < message.size(); i += 2) {
        int letter1 = message[i] - 'A';
        int letter2 = (i + 1 < message.size()) ? message[i + 1] - 'A' : 0;

        int encryptedLetter1 = (key[0][0] * letter1 + key[0][1] * letter2) % mod;
        int encryptedLetter2 = (key[1][0] * letter1 + key[1][1] * letter2) % mod;

        encrypted += static_cast<char>(encryptedLetter1 + 'A');
        encrypted += static_cast<char>(encryptedLetter2 + 'A');
    }

    return encrypted;
}

// Function to decrypt a message using Hill Cipher
std::string decrypt(const std::string &encrypted, const std::vector<std::vector<int>> &key) {
    int mod = 26; // We're working with the English alphabet
    int invDet = modInverse(determinant(key[0][0], key[0][1], key[1][0], key[1][1]), mod);

    std::string decrypted = "";
    for (size_t i = 0; i < encrypted.size(); i += 2) {
        int letter1 = encrypted[i] - 'A';
        int letter2 = encrypted[i + 1] - 'A';

        int decryptedLetter1 = (invDet * (key[1][1] * letter1 - key[0][1] * letter2 + mod * mod)) % mod;
        int decryptedLetter2 = (invDet * (-key[1][0] * letter1 + key[0][0] * letter2 + mod * mod)) % mod;

        decrypted += static_cast<char>((decryptedLetter1 + mod) % mod + 'A');
        decrypted += static_cast<char>((decryptedLetter2 + mod) % mod + 'A');
    }

    return decrypted;
}

int main() {
    // Define the key matrix
    std::vector<std::vector<int>> key = {{5, 4}, {2, 3}};

    // Message to be encrypted
    std::string message = "HI";

    // Encrypt the message
    std::string encrypted = encrypt(message, key);
    std::cout << "Encrypted: " << encrypted << std::endl;

    // Decrypt the message
    std::string decrypted = decrypt(encrypted, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
