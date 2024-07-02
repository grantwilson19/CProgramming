
// CS 420 - Grant Wilson - 824810214
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"


typedef struct CharNode CharNode;

//Check if Character is Valid
bool isValid(char c){
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||  // Case-insensitive
           (c == ' ') ||
           (c == '\'') ||
           (c == '-') ||
           (c == '_');
}

//Make Case Insensitive by making lowercase
char toLower(char c) {
    if ((c>= 'A' && c<= 'Z') || (c >= 'a' && c <= 'z')){
        return c | 32;
    }
    return c;
}

//Initialize a new Trie Node
CharNode* createNode() {
    CharNode* newNode = (CharNode*)calloc(1, sizeof(CharNode));
    if (newNode != NULL) {
        for (int i = 0; i < NCHILD; i++) {
            newNode->next[i] = NULL;
        }
    }
    //printf("NewNode \n");
    return newNode;
}


// Insert String Function
bool insert(CharNode* rootNode, const char* stringBeingInserted) {
// Take in letters from the String, Go one by one until hits null
for (int outerIndex = 0; stringBeingInserted[outerIndex] != '\0'; outerIndex++) {
    // Current Node has same frame as root (Empty with 31 Empty Children)
    // Outside of Loop so that suffixes can also be made to Tree
    CharNode* currentNode = rootNode;
    for (int index = outerIndex; stringBeingInserted[index] != '\0'; index++) {
        //Pass to toLower to make sure it is lowercase
        char insertChar = toLower(stringBeingInserted[index]);
        //Check if Valid, if not Skip
        if (!isValid(insertChar)) {
            continue;
        }
        //When lowercase get index. If "g", then 'g' - 'a' = 6
        int charIndex = 0;
        if (insertChar == ' ') {
            charIndex = 26;
        } else if (insertChar == '\'') {
            charIndex = 27;
        } else if (insertChar == '-') {
            charIndex = 28;
        } else if (insertChar == '_') {
            charIndex = 29;
        } else if (insertChar == '\0') {
            charIndex = 30;
        } else if (insertChar >= 'a' && insertChar <= 'z') {
            charIndex = insertChar - 'a';
        }
        //If the Root to 'char' is null
        if (currentNode->next[charIndex] == NULL) {
            //Create a New Node
            CharNode* newNode = createNode();
            //Allocate that spot with the char for the New Node
            currentNode->next[charIndex] = newNode;
        }
        //Now Set the current Node being changed to the one the char was just allocated to
        currentNode = currentNode->next[charIndex];
        // Continue inserting suffixes until the end of the word
    }

}
    return true;
}


bool search(struct CharNode* currentNode, const char* strBeingSearched) {
    // If Vocab word is Null just skip it
    if (strBeingSearched == NULL) {
        return false; // No match found
    }



    // Search the string up until it has a null Char
    while (strBeingSearched[0] != '\0' ) {
        // Make it LowerCase so the search Accurate
        char insertChar = toLower(*strBeingSearched);

        if (!isValid(insertChar)) {
            return false;
        }


        // Same process to search for indexes
        int charIndex = 0;
        if (insertChar == ' ') {
            charIndex = 26;
        } else if (insertChar == '\'') {
            charIndex = 27;
        } else if (insertChar == '-') {
            charIndex = 28;
        } else if (insertChar == '_') {
            charIndex = 29;
        } else if (insertChar == '\0') {
            charIndex = 30;
        } else if (insertChar >= 'a' && insertChar <= 'z') {
            charIndex = insertChar - 'a';
        }


        // If the Index is within the boundaries
        if (charIndex >= 0 && charIndex < NCHILD) {
            if (currentNode->next[charIndex] != NULL) {
                // Continue searching in the current tree node
                currentNode = currentNode->next[charIndex];
            } else {
                return false; // No match found
            }
        } else {
            return false; // Invalid character
        }
        strBeingSearched++;
    }

    return true; // Found a match
}
