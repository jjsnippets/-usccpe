#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void addMenu(NODE** maxHeap, NODE** minHeap, int* count){

    int newValue;
    char newText[4];
    int copyCount = *count;
    char repeat = 'y';

    do {
        COLOR_BLUE;
        printf("=== ADD NEW NODE ===\n");
        TEXT_RESET;
        printf("Insert value to add: ");

        memset(newText, '\0', 4);
        scanf(" %3[^\n]s", newText);

        newValue = tolower(newText[0]) + tolower(newText[1]) + tolower(newText[2]) - (3 * 'a') + 3;

        BOLD_TEXT;
        printf("%s = %02d\n\n", newText, newValue);
        TEXT_RESET;

        addMax(maxHeap, newValue, newText, count);
        MAX_COLOR;
        printf("Max Heap:");
        TEXT_RESET;
        treeDisplay(*maxHeap, newValue);
        printf("\n");

        addMin(minHeap, newValue, newText, &copyCount);
        MIN_COLOR;
        printf("Min Heap:");
        TEXT_RESET;
        treeDisplay(*minHeap, newValue);
        printf("\n");

        printf("Again [y/n]?");
        repeat = tolower(getche());
        printf("\n\n");

    } while (repeat != 'n');

}

void addMax(NODE** root, int addValue, char* addText, int* size){

    LIST* visitedNodes = NULL;
    NODE* newNode = calloc(1, sizeof(NODE));
    newNode->data = addValue;
    strncpy(newNode->text, addText, 4);

    if (!(*size)++){
        *root = newNode;

    } else {
        int movement = 1;
        for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
        movement >>= 1;

        NODE* currentNode = *root;

        for (; movement > 1; movement >>= 1){
            push(&visitedNodes, currentNode);
            currentNode = (*size & movement) ? currentNode->right : currentNode->left;
        }

        if (*size % 2) currentNode->right = newNode;
        else currentNode->left = newNode;
        push(&visitedNodes, currentNode);
    }

    // swimming
    push(&visitedNodes, newNode);
    NODE* bottomNode = pop(&visitedNodes);

    while(visitedNodes){
        NODE* topNode = pop(&visitedNodes);

        if(topNode->data > bottomNode->data) break;

        int tempData = topNode->data;
        topNode->data = bottomNode->data;
        bottomNode->data = tempData;

        char tempText[4];
        strncpy(tempText, topNode->text, 4);
        strncpy(topNode->text, bottomNode->text, 4);
        strncpy(bottomNode->text, tempText, 4);

        bottomNode = topNode;
    }
}

void addMin(NODE** root, int addValue, char* addText, int* size){

    LIST* visitedNodes = NULL;
    NODE* newNode = calloc(1, sizeof(NODE));
    newNode->data = addValue;
    strncpy(newNode->text, addText, 4);

    if (!(*size)++){
        *root = newNode;

    } else {
        int movement = 1;
        for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
        movement >>= 1;

        NODE* currentNode = *root;

        for (; movement > 1; movement >>= 1){
            push(&visitedNodes, currentNode);
            currentNode = (*size & movement) ? currentNode->right : currentNode->left;
        }

        if (*size % 2) currentNode->right = newNode;
        else currentNode->left = newNode;
        push(&visitedNodes, currentNode);
    }

    // swimming
    push(&visitedNodes, newNode);
    NODE* bottomNode = pop(&visitedNodes);

    while(visitedNodes){
        NODE* topNode = pop(&visitedNodes);

        if(topNode->data < bottomNode->data) break;

        int temp = topNode->data;
        topNode->data = bottomNode->data;
        bottomNode->data = temp;

        char tempText[4];
        strncpy(tempText, topNode->text, 4);
        strncpy(topNode->text, bottomNode->text, 4);
        strncpy(bottomNode->text, tempText, 4);

        bottomNode = topNode;
    }
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
