#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt text using Caesar cipher
void encrypt(const char *text, char *result, int shift) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            result[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        }
        else if (islower(text[i])) {
            result[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        }
        else {
            result[i] = text[i];
        }
    }
    result[i] = '\0'; // Null-terminate the result string
}

// Function to decrypt text using Caesar cipher
void decrypt(const char *text, char *result, int shift) {
    shift = shift % 26;
    encrypt(text, result, 26 - shift);
}

int main() {
    char text[1000];
    char encrypted[1000], decrypted[1000];
    int shift;

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character if present
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);
    shift = shift % 26;

    encrypt(text, encrypted, shift);
    decrypt(encrypted, decrypted, shift);

    printf("\nOriginal text: %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
