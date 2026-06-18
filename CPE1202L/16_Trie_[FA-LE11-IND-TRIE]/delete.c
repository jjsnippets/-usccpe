#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

void deleteMenu(NODE** root, int* longestWord){

    char wordSearch[20];
    char repeat = 'y';

    // submenu
    COLOR_BLUE;
    printf("=== DELETE WORD ===\n");
    TEXT_RESET;

    do {

    memset(wordSearch, '\0', sizeof(wordSearch));
    printf("Enter word to delete: ");
    scanf(" %20[^\n\x20]", wordSearch);
    printf("\n");

    for (int i = 0; i < strlen(wordSearch); i++){
        wordSearch[i] = toupper(wordSearch[i]);
    }

        // determines first if value is in tree
        NODE* isFound = search(*root, wordSearch, strlen(wordSearch));
        printf("Tree display:\n");
        displayTree(*root, *longestWord, wordSearch);
        printf("\n");

        // if value is not in tree
        if (!isFound){
            COLOR_RED;
            printf("FAILED!\n");
            TEXT_RESET;
            printf("ERROR: word not found!\n");
            printf("\n");

        // otherwise
        } else {
            COLOR_GREEN;
            printf("Success!\n");
            TEXT_RESET;
            printf("Node removed\n");
            printf("\n");

            deleteNode(root, wordSearch, strlen(wordSearch));

            printf("Tree display:\n");
            displayTree(*root, (*longestWord) + 1, wordSearch);
            printf("\n");

        }
            printf("Again [y/n]?");
            repeat = tolower(getche());
            printf("\n\n");

    } while (repeat != 'n');

}

void deleteNode(NODE** root, char* word, int wordLen){
    NODE* currentNode = *root;
    LIST* path = NULL;

    for (int i = 0; i < wordLen; i++){
        push(&path, currentNode);
        currentNode = currentNode->children[word[i] - 'A'];
    }

    currentNode->isWord = 0;
    memset(currentNode->finalWord, '\0', sizeof(currentNode->finalWord));

    for(int i = 0; i < 26; i++)
        if (currentNode->children[i]) return;

    for(int i = wordLen - 1; i >= 0; i--){
        NODE* toRemove = pop(&path);
        int totalNodes = toRemove->isWord;

        for(int j = 0; j < 26; j++){
            if (toRemove->children[j]) totalNodes++;
        }

        if (totalNodes > 1){
            toRemove->children[word[i] - 'A'] = NULL;
            return;
        }
    }
    (*root)->children[word[0] - 'A'] = NULL;
}

void push(LIST** head, NODE* toAdd){
    LIST* newHead = calloc(1, sizeof(LIST));
    newHead->node = toAdd;

    if (*head) newHead->next = *head;

    *head = newHead;
}

NODE* pop(LIST** head){
    NODE* result = (*head)->node;
    *head = (*head)->next;
    return result;
}
