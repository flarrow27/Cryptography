#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(const char* text, char* result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isupper(c)) {
            result[i] = 'Z' - (c - 'A');
        }
        else if (islower(c)) {
            result[i] = 'z' - (c - 'a');
        }
        else {
            result[i] = c;
        }
    }
    result[i] = '\0';
}

// Atbash decryption is the same as encryption
void decrypt(const char* text, char* result) {
    encrypt(text, result);
}

int main() {
    char text[1000];
    char encrypted[1000];
    char decrypted[1000];

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline if present
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    encrypt(text, encrypted);
    decrypt(encrypted, decrypted);

    printf("\nOriginal text: %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
