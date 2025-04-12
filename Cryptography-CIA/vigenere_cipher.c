#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char *text, char *key, char *repeatedKey) {
    int x = strlen(text);
    int j = 0;
    
    for (int i = 0; i < x; i++) {
        repeatedKey[i] = key[j];
        j++;
        if (j == strlen(key)) {
            j = 0;
        }
    }
    repeatedKey[x] = '\0';
}

void encrypt(char *text, char *key, char *result) {
    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            result[i] = (text[i] + key[i] - 2 * 'A') % 26 + 'A';
        }
        else if (islower(text[i])) {
            result[i] = (text[i] + tolower(key[i]) - 2 * 'a') % 26 + 'a';
        }
        else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0'; // Null terminate the result string
}

void decrypt(char *text, char *key, char *result) {
    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            result[i] = (text[i] - key[i] + 26) % 26 + 'A';
        }
        else if (islower(text[i])) {
            result[i] = (text[i] - tolower(key[i]) + 26) % 26 + 'a';
        }
        else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0'; // Null terminate the result string
}

int main() {
    char text[1000], key[100], repeatedKey[1000], encrypted[1000], decrypted[1000];
    
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove trailing newline
    
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove trailing newline
    
    generateKey(text, key, repeatedKey);
    encrypt(text, repeatedKey, encrypted);
    decrypt(encrypted, repeatedKey, decrypted);
    
    printf("\nOriginal text: %s\n", text);
    printf("Key: %s\n", key);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);
    
    return 0;
}
