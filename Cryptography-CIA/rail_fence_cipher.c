#include <stdio.h>
#include <string.h>

void encrypt(char* text, int rails, char* result) {
    int length = strlen(text);
    char fence[rails][length];
    
    int rail = 0;
    int down = 1;
    
    // Initialize the fence with spaces
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < length; j++) {
            fence[i][j] = ' ';
        }
    }
    
    // Build the rail fence pattern
    for (int i = 0; i < length; i++) {
        fence[rail][i] = text[i];
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = 0;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = 1;
            }
        }
    }
    
    // Combine all rails into result
    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < length; j++) {
            if (fence[i][j] != ' ') {
                result[index++] = fence[i][j];
            }
        }
    }
    result[index] = '\0';
}

void decrypt(char* text, int rails, char* result) {
    int length = strlen(text);
    char fence[rails][length];
    int counts[rails];
    int rail = 0;
    int down = 1;
    
    // Initialize counts to zero
    for (int i = 0; i < rails; i++) {
        counts[i] = 0;
    }
    
    // Mark positions in the fence
    for (int i = 0; i < length; i++) {
        counts[rail]++;
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = 0;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = 1;
            }
        }
    }
    
    // Fill the fence with text
    int pos = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < counts[i]; j++) {
            fence[i][j] = text[pos++];
        }
    }
    
    // Read off the fence pattern
    rail = 0;
    down = 1;
    int indices[rails];
    
    for (int i = 0; i < rails; i++) {
        indices[i] = 0;
    }
    
    int index = 0;
    for (int i = 0; i < length; i++) {
        result[index++] = fence[rail][indices[rail]++];
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = 0;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = 1;
            }
        }
    }
    result[index] = '\0';
}

int main() {
    char text[1000], encrypted[1000], decrypted[1000];
    int rails;
    
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline character from fgets
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter number of rails: ");
    scanf("%d", &rails);
    
    encrypt(text, rails, encrypted);
    decrypt(encrypted, rails, decrypted);
    
    printf("\nOriginal text: %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);
    
    return 0;
}
