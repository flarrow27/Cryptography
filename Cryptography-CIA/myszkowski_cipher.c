#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to clean and validate input text
char* preprocessText(const char* text) {
    int length = strlen(text);
    char* cleaned = (char*)malloc(length + 1);
    int j = 0;
    
    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            cleaned[j++] = toupper(text[i]);
        }
    }
    cleaned[j] = '\0';
    
    if (j == 0) {
        printf("Error: Text must contain at least one letter!\n");
        exit(1);
    }
    return cleaned;
}

// Function to validate and process key
char* preprocessKey(const char* key) {
    int length = strlen(key);
    char* cleaned = (char*)malloc(length + 1);
    int j = 0;
    
    for (int i = 0; i < length; i++) {
        if (isalpha(key[i])) {
            cleaned[j++] = toupper(key[i]);
        }
    }
    cleaned[j] = '\0';
    
    if (j == 0) {
        printf("Error: Key must contain at least one letter!\n");
        exit(1);
    }
    return cleaned;
}

// Function to create a grid for encryption
char** createGrid(const char* text, const char* key, int* rows, int* cols) {
    *cols = strlen(key);
    *rows = (strlen(text) + *cols - 1) / *cols;
    
    char** grid = (char**)malloc(*rows * sizeof(char*));
    for (int i = 0; i < *rows; i++) {
        grid[i] = (char*)malloc(*cols * sizeof(char));
        for (int j = 0; j < *cols; j++) {
            grid[i][j] = ' ';
        }
    }
    
    int k = 0;
    for (int i = 0; i < *rows && k < strlen(text); i++) {
        for (int j = 0; j < *cols && k < strlen(text); j++) {
            grid[i][j] = text[k++];
        }
    }
    return grid;
}

// Function to print the grid (for visualization)
void printGrid(char** grid, const char* key, int rows, int cols) {
    printf("\nEncryption Grid:\n");
    printf("  ");
    for (int i = 0; i < cols; i++) {
        printf("%c ", key[i]);
    }
    printf("\n  ");
    for (int i = 0; i < cols; i++) {
        printf("- ");
    }
    printf("\n");
    
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j] == ' ' ? '_' : grid[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

char* encrypt(const char* text, const char* key) {
    char* processedText = preprocessText(text);
    char* processedKey = preprocessKey(key);
    
    int rows, cols;
    char** grid = createGrid(processedText, processedKey, &rows, &cols);
    printGrid(grid, processedKey, rows, cols); // Show the grid for visualization
    
    char* result = (char*)malloc(strlen(processedText) + 1);
    int resultIndex = 0;
    
    // Create ordered indices based on key
    int* keyOrder = (int*)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        keyOrder[i] = i;
    }
    for (int i = 0; i < cols - 1; i++) {
        for (int j = i + 1; j < cols; j++) {
            if (processedKey[keyOrder[i]] > processedKey[keyOrder[j]]) {
                int temp = keyOrder[i];
                keyOrder[i] = keyOrder[j];
                keyOrder[j] = temp;
            }
        }
    }
    
    printf("Reading order: ");
    // Read columns in sorted key order
    for (int i = 0; i < cols; i++) {
        printf("%c ", processedKey[keyOrder[i]]);
        for (int row = 0; row < rows; row++) {
            if (grid[row][keyOrder[i]] != ' ') {
                result[resultIndex++] = grid[row][keyOrder[i]];
            }
        }
    }
    printf("\n");
    
    result[resultIndex] = '\0';
    free(processedText);
    free(processedKey);
    free(keyOrder);
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return result;
}

char* decrypt(const char* text, const char* key) {
    char* processedText = preprocessText(text);
    char* processedKey = preprocessKey(key);
    
    int rows, cols;
    cols = strlen(processedKey);
    rows = (strlen(processedText) + cols - 1) / cols;
    
    // Create ordered indices based on key
    int* keyOrder = (int*)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        keyOrder[i] = i;
    }
    for (int i = 0; i < cols - 1; i++) {
        for (int j = i + 1; j < cols; j++) {
            if (processedKey[keyOrder[i]] > processedKey[keyOrder[j]]) {
                int temp = keyOrder[i];
                keyOrder[i] = keyOrder[j];
                keyOrder[j] = temp;
            }
        }
    }
    
    // Calculate the number of characters in each column
    int* colLengths = (int*)malloc(cols * sizeof(int));
    int fullRows = strlen(processedText) / cols;
    int remainingChars = strlen(processedText) % cols;
    
    for (int i = 0; i < cols; i++) {
        colLengths[i] = fullRows;
        if (i < remainingChars) colLengths[i]++;
    }
    
    // Create mapping from sorted position to original position
    int* positionMap = (int*)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        positionMap[keyOrder[i]] = i;
    }
    
    // Read the input text into columns
    char** columns = (char**)malloc(cols * sizeof(char*));
    for (int i = 0; i < cols; i++) {
        columns[i] = (char*)malloc(colLengths[i] * sizeof(char));
    }
    
    int pos = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < colLengths[i]; j++) {
            columns[keyOrder[i]][j] = processedText[pos++];
        }
    }
    
    // Reconstruct the original text
    char* result = (char*)malloc(strlen(processedText) + 1);
    int resultIndex = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row < colLengths[col]) {
                result[resultIndex++] = columns[col][row];
            }
        }
    }
    
    result[resultIndex] = '\0';
    
    free(processedText);
    free(processedKey);
    free(keyOrder);
    free(colLengths);
    free(positionMap);
    for (int i = 0; i < cols; i++) {
        free(columns[i]);
    }
    free(columns);
    
    return result;
}

int main() {
    char text[1000], key[100];
    
    printf("Enter text to encrypt (letters only): ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    
    printf("Enter key (letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    
    char* encrypted = encrypt(text, key);
    char* decrypted = decrypt(encrypted, key);
    
    printf("\nOriginal text:  %s\n", text);
    printf("Preprocessed:   %s\n", preprocessText(text));
    printf("Key:           %s\n", key);
    printf("Preprocessed:   %s\n", preprocessKey(key));
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);
    
    free(encrypted);
    free(decrypted);
    
    return 0;
}
