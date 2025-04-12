#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Repeat key to match length of the text
void generateKey(const char* text, const char* key, char* repeatedKey) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLen; i++, j++) {
        if (j == keyLen) j = 0;
        repeatedKey[i] = key[j];
    }
    repeatedKey[textLen] = '\0';
}

// Encrypt/Decrypt using Beaufort Cipher
void beaufortCipher(const char* text, const char* key, char* result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = 'A' + (key[i] - text[i] + 26) % 26;
        }
        else if (islower(text[i])) {
            result[i] = 'a' + (tolower(key[i]) - text[i] + 26) % 26;
        }
        else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

int main() {
    char text[MAX], key[MAX];
    char repeatedKey[MAX], encrypted[MAX], decrypted[MAX];

    printf("Enter text to encrypt: ");
    fgets(text, MAX, stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    generateKey(text, key, repeatedKey);
    beaufortCipher(text, repeatedKey, encrypted);
    beaufortCipher(encrypted, repeatedKey, decrypted); // same as encryption

    printf("\nOriginal text: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
