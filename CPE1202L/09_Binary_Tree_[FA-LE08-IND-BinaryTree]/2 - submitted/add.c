#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

#define BOLD_TEXT printf("\e[1m")
#define COLOR_RED printf("\e[91m")
#define COLOR_GREEN printf("\e[92m")
#define COLOR_BLUE printf("\e[94m")
#define TEXT_RESET printf("\e[m")

void addMenu(NODE** root, int* count){

    int newValue;

    COLOR_BLUE;
    printf("=== ADD NEW NODE ===\n");
    TEXT_RESET;
    printf("Insert value to add: ");
    scanf(" %d", &newValue);
    printf("\n");

    addNode(root, newValue, count);
    displayAll(*root, *count);

    COLOR_GREEN;
    printf("Success!\n");
    TEXT_RESET;
    printf("Node added\n");
    printf("Press any key to continue\n");
    getche();
}




void addNode(NODE** root, int data, int* size){

    NODE* newNode = calloc(1, sizeof(NODE));
    newNode->x = data;

    if (!(*size)++){
        *root = newNode;
        return;
    }

    int movement = 1;
    for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
    movement >>= 1;

    NODE* currentNode = *root;

    for (; movement > 1; movement >>= 1){

        if (*size & movement){
            (currentNode = currentNode->right);
        } else {
            (currentNode = currentNode->left);
        }
    }

    if (*size % 2){
            (currentNode->right = newNode);
    } else {
            (currentNode->left = newNode);
    }
}
