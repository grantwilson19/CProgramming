// CS 420 - Grant Wilson - 824810214


#ifdef __STDC_ALLOC_LIB__
#define __STDC_ALLOC_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Function to read vocabulary strings into a dynamic array
char** readVocabularyFile(const char* filename, int* vocabCount) {
    FILE *file = fopen(filename, "r");

    // Initialize variables for dynamic array
    char** vocabArray = NULL;
    int capacity = 100000;
    int count = 0;

    // Allocate memory for the dynamic array
    vocabArray = (char**)malloc(capacity * sizeof(char*));

    char line[100000];
    while (fgets(line, sizeof(line), file)) {
        // Remove NewLine Marker and Make Null
        size_t len = strlen(line);
        for (size_t i = 0; i < len; i++){
            if (line[i] == '\n'){
                line[i] = '\0';
            }
        }


        // Add the word to the dynamic array
        if (count >= capacity) {
            // If the array is full, increase its capacity
            capacity *= 2;
            vocabArray = (char**)realloc(vocabArray, capacity * sizeof(char*));
        }
        vocabArray[count] = strdup(line); // Duplicate the string to store
        count++;
    }

    fclose(file);
    // Update the vocabCount and return the dynamic array
    *vocabCount = count;
    return vocabArray;
}




//Main Function
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <vocabulary_file> <test_file>\n", argv[0]);
        return 1;
    }

    // Open Vocabulary File and store in Array
    int vocabCount;
    char** vocabArray = readVocabularyFile(argv[1], &vocabCount);

    // Read lines from the test file, create a tree for each line, and search for vocab terms
    FILE* testFile = fopen(argv[2], "r");

    char line[10000];
    while (fgets(line, sizeof(line), testFile)) {
        // Create a new root node for each line
        // Root Node with 31 Empty Children waiting for Index Letter
        struct CharNode* rootNode = createNode();

        // Remove trailing newline character if present and make null ptr
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Create Tree using insert Function
        insert(rootNode, line);


        // Search for vocabulary terms and count
        int count = 0;
        for (int i = 0; i < vocabCount; i++) {
            if (search(rootNode, vocabArray[i])) {
                count++;
                //printf("%s \n", vocabArray[i]);
            }

        }

        // Print the count for this tree
        printf("%d\n", count);

    }
    fclose(testFile);

    // Free allocated memory
    for (int i = 0; i < vocabCount; i++) {
        free(vocabArray[i]);
    }
    free(vocabArray);

    return 0;
}
