#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define MAX_KEY 100

void processKey(const char *keyStr, int *key, int textLength) {
    int tempKey[MAX_KEY];
    int tempLen = 0;

    for (int i = 0; keyStr[i] != '\0'; i++) {
        if (isdigit(keyStr[i])) {
            tempKey[tempLen++] = keyStr[i] - '0';
        }
    }

    for (int i = 0; i < textLength; i++) {
        key[i] = tempKey[i % tempLen];
    }
}

void encrypt(const char *text, char *result, int *key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = ((text[i] - 'A' + key[i]) % 26) + 'A';
        }
        else if (islower(text[i])) {
            result[i] = ((text[i] - 'a' + key[i]) % 26) + 'a';
        }
        else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

void decrypt(const char *text, char *result, int *key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = ((text[i] - 'A' - key[i] + 26) % 26) + 'A';
        }
        else if (islower(text[i])) {
            result[i] = ((text[i] - 'a' - key[i] + 26) % 26) + 'a';
        }
        else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

int main() {
    char text[MAX_TEXT], keyStr[MAX_KEY];
    char encrypted[MAX_TEXT], decrypted[MAX_TEXT];
    int key[MAX_TEXT];

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter numerical key (e.g., 31415): ");
    fgets(keyStr, sizeof(keyStr), stdin);
    len = strlen(keyStr);
    if (len > 0 && keyStr[len - 1] == '\n') {
        keyStr[len - 1] = '\0';
    }

    processKey(keyStr, key, strlen(text));
    encrypt(text, encrypted, key);
    decrypt(encrypted, decrypted, key);

    printf("\nOriginal text: %s\n", text);
    printf("Key: %s\n", keyStr);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
