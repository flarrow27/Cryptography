#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate determinant of 2x2 matrix
int determinant(int key[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    return det < 0 ? det + 26 : det;
}

// Function to calculate GCD
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular multiplicative inverse
int modInverse(int a, int m) {
    a = ((a % m) + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;  // Return -1 if inverse doesn't exist
}

// Function to validate key matrix
int isValidKey(int key[2][2]) {
    // Check if all elements are within valid range
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (key[i][j] < 0 || key[i][j] >= 26) return 0;
        }
    }
    
    // Check if determinant is valid (coprime with 26)
    int det = determinant(key);
    return gcd(det, 26) == 1;
}

// Function to get adjugate matrix
void adjugate(int key[2][2], int adj[2][2]) {
    adj[0][0] = key[1][1];
    adj[1][1] = key[0][0];
    adj[0][1] = (-key[0][1] % 26 + 26) % 26;
    adj[1][0] = (-key[1][0] % 26 + 26) % 26;
}

// Function to encrypt text
void encrypt(char *text, int key[2][2], char *result) {
    // Remove non-alphabetic characters and convert to uppercase
    int cleanedLength = 0;
    char cleaned[1000];
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            cleaned[cleanedLength++] = toupper(text[i]);
        }
    }
    
    // Pad with 'X' if necessary
    if (cleanedLength % 2 != 0) {
        cleaned[cleanedLength++] = 'X';
    }
    cleaned[cleanedLength] = '\0';

    // Encryption process
    int e1, e2;
    for (int i = 0; i < cleanedLength; i += 2) {
        int p1 = cleaned[i] - 'A';
        int p2 = cleaned[i + 1] - 'A';
        
        e1 = ((key[0][0] * p1 + key[0][1] * p2) % 26 + 26) % 26;
        e2 = ((key[1][0] * p1 + key[1][1] * p2) % 26 + 26) % 26;
        
        result[i] = e1 + 'A';
        result[i + 1] = e2 + 'A';
    }
    result[cleanedLength] = '\0';
}

// Function to decrypt text
void decrypt(char *text, int key[2][2], char *result) {
    int det = determinant(key);
    int detInv = modInverse(det, 26);
    
    if (detInv == -1) {
        printf("Invalid key matrix! No modular multiplicative inverse exists.\n");
        return;
    }
    
    int adj[2][2];
    adjugate(key, adj);
    
    int invKey[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invKey[i][j] = (adj[i][j] * detInv % 26 + 26) % 26;
        }
    }
    
    encrypt(text, invKey, result);
}

int main() {
    char text[1000], keyStr[100];
    int key[2][2];

    printf("Enter text to encrypt (letters only): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;  // Remove trailing newline from fgets

    printf("Enter 2x2 key matrix (4 numbers between 0-25):\n");
    printf("Note: Determinant must be coprime with 26\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            while (1) {
                scanf("%d", &key[i][j]);
                if (key[i][j] >= 0 && key[i][j] < 26) break;
                printf("Please enter a number between 0 and 25: ");
            }
        }
    }
    
    if (!isValidKey(key)) {
        printf("\nError: Invalid key matrix! Determinant must be coprime with 26.\n");
        return 1;
    }

    char encrypted[1000], decrypted[1000];
    encrypt(text, key, encrypted);
    decrypt(encrypted, key, decrypted);
    
    printf("\nOriginal text:  %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);
    
    return 0;
}
