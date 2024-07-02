// CS 420 - Grant Wilson - 824810214

#include <stdbool.h>

#ifndef TREE_H
#define TREE_H

#define NCHILD 31

//Trie Tree Node Structure
 struct CharNode {
    struct CharNode *next[NCHILD];
};

//Initialize New Trie Node
struct CharNode* createNode();

//Insert String Into the Trie
bool insert(struct CharNode* currentNode, const char* stringBeingInserted);

//Search for a String in the Trie
bool search(struct CharNode* currentNode, const char* strBeingSearched);


#endif //TREE_H
