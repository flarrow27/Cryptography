#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return 1;
}

void encrypt(char* text, char* result, int a, int b) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isupper(c)) {
            result[i] = ((a * (c - 'A') + b) % 26) + 'A';
        }
        else if (islower(c)) {
            result[i] = ((a * (c - 'a') + b) % 26) + 'a';
        }
        else {
            result[i] = c;
        }
    }
    result[i] = '\0';
}

void decrypt(char* text, char* result, int a, int b) {
    int a_inv = modInverse(a, 26);
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isupper(c)) {
            result[i] = (a_inv * ((c - 'A' - b + 26) % 26)) + 'A';
        }
        else if (islower(c)) {
            result[i] = (a_inv * ((c - 'a' - b + 26) % 26)) + 'a';
        }
        else {
            result[i] = c;
        }
    }
    result[i] = '\0';
}

int main() {
    char text[1000], encrypted[1000], decrypted[1000];
    int a, b;

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline if present
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter first key (a) [must be coprime with 26]: ");
    scanf("%d", &a);
    printf("Enter second key (b): ");
    scanf("%d", &b);

    encrypt(text, encrypted, a, b);
    decrypt(encrypted, decrypted, a, b);

    printf("\nOriginal text: %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
