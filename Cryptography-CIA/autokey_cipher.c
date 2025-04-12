#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Generate the autokey by appending the plaintext to the initial key
void generateAutokey(const char* text, const char* key, char* autokey) {
    int keyLen = strlen(key);
    int textLen = strlen(text);
    
    strcpy(autokey, key);
    
    for (int i = keyLen; i < textLen; i++) {
        autokey[i] = text[i - keyLen];
    }
    autokey[textLen] = '\0';
}

// Encrypt using Autokey cipher
void encrypt(const char* text, const char* key, char* result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = ((text[i] + toupper(key[i]) - 2 * 'A') % 26) + 'A';
        } else if (islower(text[i])) {
            result[i] = ((text[i] + tolower(key[i]) - 2 * 'a') % 26) + 'a';
        } else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

// Decrypt using Autokey cipher
void decrypt(const char* text, const char* initialKey, char* result) {
    char key[MAX];
    strcpy(key, initialKey);
    
    int keyLen = strlen(initialKey);
    int i;
    
    for (i = 0; text[i] != '\0'; i++) {
        char decrypted;
        if (isupper(text[i])) {
            decrypted = ((text[i] - toupper(key[i]) + 26) % 26) + 'A';
            if (i >= keyLen) {
                key[i] = decrypted;
                key[i + 1] = '\0';
            }
        } else if (islower(text[i])) {
            decrypted = ((text[i] - tolower(key[i]) + 26) % 26) + 'a';
            if (i >= keyLen) {
                key[i] = decrypted;
                key[i + 1] = '\0';
            }
        } else {
            decrypted = text[i];
        }
        result[i] = decrypted;
    }
    result[i] = '\0';
}

int main() {
    char text[MAX], initialKey[MAX];
    char autokey[MAX], encrypted[MAX], decrypted[MAX];

    printf("Enter text to encrypt: ");
    fgets(text, MAX, stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter initial key: ");
    fgets(initialKey, MAX, stdin);
    initialKey[strcspn(initialKey, "\n")] = 0;

    generateAutokey(text, initialKey, autokey);
    encrypt(text, autokey, encrypted);
    decrypt(encrypted, initialKey, decrypted);

    printf("\nOriginal text: %s\n", text);
    printf("Initial key: %s\n", initialKey);
    printf("Full autokey: %s\n", autokey);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
