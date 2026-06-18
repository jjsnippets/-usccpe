#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

void searchMenu(NODE* root, int longestWord){

    char wordSearch[20];

    COLOR_BLUE;
    printf("=== SEARCH FOR WORD ===\n");
    TEXT_RESET;

    printf("Enter word to search: ");
    scanf(" %20[^\n]", wordSearch);
    printf("\n");

    for (int i = 0; i < strlen(wordSearch); i++){
        wordSearch[i] = toupper(wordSearch[i]);
    }

    NODE* isFound = search(root, wordSearch, strlen(wordSearch));

    if (isFound){
        COLOR_GREEN;
        printf("Word %s found\n", wordSearch);
        TEXT_RESET;
    } else {
        COLOR_RED;
        printf("Word %s not found\n", wordSearch);
        TEXT_RESET;
    }

    displayTree(root, longestWord, wordSearch);

    printf("\n");
    printf("Press any key to continue\n");
    getche();

}

NODE* search(NODE* root, char* word, int wordLen){
    NODE* currentNode = root;

    for (int i = 0; i < wordLen; i++){
        if (!currentNode->children[word[i] - 'A']) return NULL;
        currentNode = currentNode->children[word[i] - 'A'];
    }

    if(currentNode->isWord) return currentNode;
    else return NULL;
}

void displayTree(NODE* root, int longestWordLen, char* match){
    if (!root) return;

    for (int i = 0; i <= longestWordLen; i++) printf("\n");
    MOVE_UP(longestWordLen + 1);

    showNodes(root, 1, match);

    MOVE_DOWN(longestWordLen + 2);
    printf("\n");
}

void showNodes(NODE* root, int depth, char* match){
    if (!root) return;
    MOVE_DOWN(depth);
    printf("{");
    MOVE_UP(depth);

    for (int i = 0; i < 26; i++){
        if (root->children[i]){
            MOVE_DOWN(depth);
            printf("[%c]", i + 'A');
            TEXT_RESET;
            MOVE_UP(depth);
            MOVE_LEFT(3);
            showNodes(root->children[i], depth + 1, match);
        }
    }

    if (root->isWord){
        MOVE_DOWN(depth);
        if (strcmp(root->finalWord, match) == 0) COLOR_PINK;
        printf("<%s>} ", root->finalWord);
        TEXT_RESET;
        MOVE_UP(depth);

    } else {
        MOVE_DOWN(depth);
        printf("}");
        MOVE_UP(depth);
    }


    //
}
