#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NGRAMS 1000
#define MAX_TEXT_LENGTH 1000

typedef struct {
    char ngram[100];
    int count;
} NgramFreq;

NgramFreq ngramFreq[MAX_NGRAMS];
int totalNgrams = 0;

void preprocessText(char *text) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            text[j++] = toupper(text[i]);
        }
    }
    text[j] = '\0';
}

void generateNgrams(char *text, int n, char ngrams[MAX_NGRAMS][100], int *ngramCount) {
    int len = strlen(text);
    *ngramCount = 0;
    
    for (int i = 0; i <= len - n; i++) {
        strncpy(ngrams[*ngramCount], text + i, n);
        ngrams[*ngramCount][n] = '\0';
        (*ngramCount)++;
    }
}

void analyzeFrequency(char *text, int n) {
    int len = strlen(text);
    totalNgrams = 0;
    int i, j;
    for (i = 0; i < MAX_NGRAMS; i++) {
        ngramFreq[i].count = 0;
    }

    for (i = 0; i <= len - n; i++) {
        char ngram[100];
        strncpy(ngram, text + i, n);
        ngram[n] = '\0';

        int found = 0;
        for (j = 0; j < totalNgrams; j++) {
            if (strcmp(ngramFreq[j].ngram, ngram) == 0) {
                ngramFreq[j].count++;
                found = 1;
                break;
            }
        }

        if (!found && totalNgrams < MAX_NGRAMS) {
            strcpy(ngramFreq[totalNgrams].ngram, ngram);
            ngramFreq[totalNgrams].count = 1;
            totalNgrams++;
        }
    }
}

void printFrequencyAnalysis() {
    int i, j;
    for (i = 0; i < totalNgrams - 1; i++) {
        for (j = i + 1; j < totalNgrams; j++) {
            if (ngramFreq[i].count < ngramFreq[j].count) {
                NgramFreq temp = ngramFreq[i];
                ngramFreq[i] = ngramFreq[j];
                ngramFreq[j] = temp;
            }
        }
    }

    printf("\nN-gram Frequency Analysis:\n");
    printf("%-10s%-10s%-15s\n", "N-gram", "Count", "Percentage");
    printf("-----------------------------\n");

    for (i = 0; i < totalNgrams; i++) {
        double percentage = (100.0 * ngramFreq[i].count) / totalNgrams;
        printf("%-10s%-10d%-15.2f\n", ngramFreq[i].ngram, ngramFreq[i].count, percentage);
    }
}

void findRepeatingSequences(char *text, int n) {
    int len = strlen(text);
    int positions[MAX_NGRAMS][MAX_TEXT_LENGTH];
    int positionCount[MAX_NGRAMS] = {0};
    int ngramCount = 0;

    for (int i = 0; i <= len - n; i++) {
        char ngram[100];
        strncpy(ngram, text + i, n);
        ngram[n] = '\0';

        int found = 0;
        for (int j = 0; j < ngramCount; j++) {
            if (strcmp(ngram, ngramFreq[j].ngram) == 0) {
                positions[j][positionCount[j]++] = i;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(ngramFreq[ngramCount].ngram, ngram);
            positions[ngramCount][positionCount[ngramCount]++] = i;
            ngramCount++;
        }
    }

    printf("\nRepeating %d-gram sequences:\n", n);
    for (int i = 0; i < ngramCount; i++) {
        if (positionCount[i] > 1) {
            printf("%s appears at positions: ", ngramFreq[i].ngram);
            for (int j = 0; j < positionCount[i]; j++) {
                printf("%d ", positions[i][j]);
            }
            printf("\n");
        }
    }
}

double calculateIoC(char *text) {
    int len = strlen(text);
    int freqs[26] = {0};
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            freqs[text[i] - 'A']++;
        }
    }

    double ioc = 0;
    for (int i = 0; i < 26; i++) {
        ioc += (freqs[i] * (freqs[i] - 1.0)) / (len * (len - 1.0));
    }

    return ioc;
}

void encryptDecrypt(char *text, char *key, int isEncrypt) {
    int len = strlen(text);
    char result[MAX_TEXT_LENGTH];
    
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int index = toupper(text[i]) - 'A';
            if (isEncrypt) {
                result[i] = key[index];
            } else {
                result[i] = 'A' + strchr(key, toupper(text[i])) - key;
            }
            if (islower(text[i])) {
                result[i] = tolower(result[i]);
            }
        } else {
            result[i] = text[i];
        }
    }
    result[len] = '\0';
    printf("%s\n", result);
}

int main() {
    char text[MAX_TEXT_LENGTH];
    char operation[10];
    int n;

    printf("Enter text for analysis: ");
    fgets(text, MAX_TEXT_LENGTH, stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("\nAvailable operations:\n");
    printf("1. Generate n-grams\n");
    printf("2. Frequency analysis\n");
    printf("3. Find repeating sequences\n");
    printf("4. Calculate Index of Coincidence\n");
    printf("5. Simple substitution cipher\n");
    printf("\nEnter operation number: ");
    fgets(operation, 10, stdin);
    operation[strcspn(operation, "\n")] = '\0';

    if (strcmp(operation, "1") == 0 || strcmp(operation, "2") == 0 || strcmp(operation, "3") == 0) {
        printf("Enter n (length of n-grams): ");
        scanf("%d", &n);
        getchar();  // Consume newline
        
        if (strcmp(operation, "1") == 0) {
            char ngrams[MAX_NGRAMS][100];
            int ngramCount;
            generateNgrams(text, n, ngrams, &ngramCount);
            printf("\nGenerated %d-grams:\n", n);
            for (int i = 0; i < ngramCount; i++) {
                printf("%s ", ngrams[i]);
            }
            printf("\n");
        }
        else if (strcmp(operation, "2") == 0) {
            analyzeFrequency(text, n);
            printFrequencyAnalysis();
        }
        else if (strcmp(operation, "3") == 0) {
            findRepeatingSequences(text, n);
        }
    }
    else if (strcmp(operation, "4") == 0) {
        double ioc = calculateIoC(text);
        printf("\nIndex of Coincidence: %.4f\n", ioc);
        printf("(English text typically has IoC around 0.067)\n");
    }
    else if (strcmp(operation, "5") == 0) {
        char key[27];
        printf("Enter 26-letter key (A-Z): ");
        fgets(key, 27, stdin);
        key[strcspn(key, "\n")] = '\0';

        if (strlen(key) != 26) {
            printf("Error: Key must be exactly 26 letters\n");
            return 1;
        }

        encryptDecrypt(text, key, 1);
        encryptDecrypt(text, key, 0);
    }

    return 0;
}
