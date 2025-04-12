#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Generate the August tableau
void generateTableau(char tableau[26][26]) {
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            tableau[i][j] = 'A' + ((j + i * i) % 26);
        }
    }
}

// Encrypt the text using the August cipher
void encrypt(const char* text, const char* key, char* result) {
    char tableau[26][26];
    generateTableau(tableau);

    int keyLen = strlen(key);
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            char k = toupper(key[i % keyLen]);
            int row = k - 'A';
            int col = c - 'A';
            char encrypted = tableau[row][col];
            result[i] = isupper(text[i]) ? encrypted : tolower(encrypted);
        } else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

// Decrypt the text using the August cipher
void decrypt(const char* text, const char* key, char* result) {
    char tableau[26][26];
    generateTableau(tableau);

    int keyLen = strlen(key);
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            char k = toupper(key[i % keyLen]);
            int row = k - 'A';
            int col = 0;
            for (int j = 0; j < 26; j++) {
                if (tableau[row][j] == c) {
                    col = j;
                    break;
                }
            }
            char decrypted = 'A' + col;
            result[i] = isupper(text[i]) ? decrypted : tolower(decrypted);
        } else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

int main() {
    char text[MAX], key[MAX];
    char encrypted[MAX], decrypted[MAX];

    printf("Enter text to encrypt: ");
    fgets(text, MAX, stdin);
    text[strcspn(text, "\n")] = 0; // remove newline

    printf("Enter key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    encrypt(text, key, encrypted);
    decrypt(encrypted, key, decrypted);

    printf("\nOriginal text: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
