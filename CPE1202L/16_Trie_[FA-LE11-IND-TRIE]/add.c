#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

void addMenu(NODE** root, int* longestWord){

    char addWord[20];
    char repeat = 'y';

    COLOR_BLUE;
    printf("=== ADD NEW WORD ===\n");
    TEXT_RESET;

    do {
        memset(addWord, '\0', sizeof(addWord));

        printf("Enter word to add: ");
        scanf(" %20[^\n\x20]", addWord);
        printf("\n");

        for (int i = 0; i < strlen(addWord); i++){
            addWord[i] = toupper(addWord[i]);
        }

        if (strlen(addWord) > *longestWord){
            *longestWord = strlen(addWord);
        }

        addNode(root, addWord, strlen(addWord));

        printf("Tree display:\n");
        displayTree(*root, *longestWord, "!!!!!");

        COLOR_GREEN;
        printf("Success!\n");
        TEXT_RESET;

        printf("Again [y/n]?");
        repeat = tolower(getche());
        printf("\n\n");

    } while (repeat != 'n');

}

void addNode(NODE** root, char* word, int wordLen){

    NODE* currentNode = *root;

    for (int i = 0; i < wordLen; i++){
        if (!currentNode->children[word[i] - 'A']){
            currentNode->children[word[i] - 'A'] = calloc(1, sizeof(NODE));
        }
        currentNode = currentNode->children[word[i] - 'A'];
    }

    currentNode->isWord = 1;
    strcpy(currentNode->finalWord, word);

}
