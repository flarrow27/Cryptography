#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createGrid(char* text, int rows, int cols, char grid[rows][cols]) {
    int k = 0;
    
    // Fill the grid row by row
    for (int i = 0; i < rows && k < strlen(text); i++) {
        for (int j = 0; j < cols && k < strlen(text); j++) {
            grid[i][j] = text[k++];
        }
    }
}

char* encrypt(char* text, int rows, int cols, int route) {
    // Pad text with spaces if needed
    int textLength = strlen(text);
    while (textLength < rows * cols) {
        text[textLength++] = ' ';
        text[textLength] = '\0';
    }

    char grid[rows][cols];
    createGrid(text, rows, cols, grid);

    char* result = (char*)malloc((rows * cols + 1) * sizeof(char));
    int index = 0;
    
    switch (route) {
        case 1: // Spiral clockwise from outside
            {
                int top = 0, bottom = rows - 1;
                int left = 0, right = cols - 1;

                while (top <= bottom && left <= right) {
                    // Right direction
                    for (int i = left; i <= right; i++)
                        result[index++] = grid[top][i];
                    top++;
                    
                    // Down direction
                    for (int i = top; i <= bottom; i++)
                        result[index++] = grid[i][right];
                    right--;
                    
                    if (top <= bottom) {
                        // Left direction
                        for (int i = right; i >= left; i--)
                            result[index++] = grid[bottom][i];
                        bottom--;
                    }
                    
                    if (left <= right) {
                        // Up direction
                        for (int i = bottom; i >= top; i--)
                            result[index++] = grid[i][left];
                        left++;
                    }
                }
            }
            break;
            
        case 2: // Snake pattern (alternating right and left)
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols; j++)
                        result[index++] = grid[i][j];
                } else {
                    for (int j = cols - 1; j >= 0; j--)
                        result[index++] = grid[i][j];
                }
            }
            break;
            
        case 3: // Diagonal (top-left to bottom-right)
            for (int sum = 0; sum < rows + cols - 1; sum++) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (i + j == sum)
                            result[index++] = grid[i][j];
                    }
                }
            }
            break;
    }

    result[index] = '\0';
    return result;
}

char* decrypt(char* text, int rows, int cols, int route) {
    char grid[rows][cols];
    int k = 0;
    
    // Fill the grid according to the route pattern
    switch (route) {
        case 1: // Spiral clockwise from outside
            {
                int top = 0, bottom = rows - 1;
                int left = 0, right = cols - 1;

                while (top <= bottom && left <= right && k < strlen(text)) {
                    for (int i = left; i <= right && k < strlen(text); i++)
                        grid[top][i] = text[k++];
                    top++;
                    
                    for (int i = top; i <= bottom && k < strlen(text); i++)
                        grid[i][right] = text[k++];
                    right--;
                    
                    if (top <= bottom) {
                        for (int i = right; i >= left && k < strlen(text); i--)
                            grid[bottom][i] = text[k++];
                        bottom--;
                    }
                    
                    if (left <= right) {
                        for (int i = bottom; i >= top && k < strlen(text); i--)
                            grid[i][left] = text[k++];
                        left++;
                    }
                }
            }
            break;
            
        case 2: // Snake pattern
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols && k < strlen(text); j++)
                        grid[i][j] = text[k++];
                } else {
                    for (int j = cols - 1; j >= 0 && k < strlen(text); j--)
                        grid[i][j] = text[k++];
                }
            }
            break;
            
        case 3: // Diagonal
            for (int sum = 0; sum < rows + cols - 1 && k < strlen(text); sum++) {
                for (int i = 0; i < rows && k < strlen(text); i++) {
                    for (int j = 0; j < cols && k < strlen(text); j++) {
                        if (i + j == sum)
                            grid[i][j] = text[k++];
                    }
                }
            }
            break;
    }

    // Read the grid row by row
    char* result = (char*)malloc((rows * cols + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != ' ') {
                result[index++] = grid[i][j];
            }
        }
    }
    result[index] = '\0';
    return result;
}

int main() {
    char text[1000];
    int rows, cols, route;
    
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline character from fgets
    text[strcspn(text, "\n")] = 0;
    
    printf("Enter grid dimensions (rows cols): ");
    scanf("%d %d", &rows, &cols);
    
    printf("Enter route type (1: Spiral, 2: Snake, 3: Diagonal): ");
    scanf("%d", &route);
    
    char* encrypted = encrypt(text, rows, cols, route);
    char* decrypted = decrypt(encrypted, rows, cols, route);
    
    printf("\nOriginal text: %s\n", text);
    printf("Encrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);
    
    // Free allocated memory
    free(encrypted);
    free(decrypted);
    
    return 0;
}
