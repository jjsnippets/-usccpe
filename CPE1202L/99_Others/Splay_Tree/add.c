#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void addMenu(NODE** root){

    int newValue;

    // submenu
    COLOR_BLUE;
    printf("=== ADD NEW NODE ===\n");
    TEXT_RESET;
    printf("Insert value to add: ");
    scanf(" %d", &newValue);

    // adding of value to tree
    LIST* checkBalance = addNode(root, newValue);
    splayTree(root, checkBalance);

    COLOR_GREEN;
    printf("Success!\n");
    TEXT_RESET;
    printf("Node added\n");
    printf("Press any key to continue\n");
    getche();
}

LIST* addNode(NODE** root, int data){
    LIST* traversed = NULL;

    // when tree is empty
    if (!*root){
        *root = calloc(1, sizeof(NODE));
        (*root)->data = data;
        push(&traversed, *root);

    // otherwise
    } else {
        NODE* newNode = calloc(1, sizeof(NODE));
        newNode->data = data;

        // find position in tree to insert node in
            // initial move; from root to branch
            NODE* currentNode = *root;
            NODE** nextNode = (data < currentNode->data) ? &(currentNode->left) : &(currentNode->right);
            push(&traversed, currentNode); // history of nodes visited

            // next succeeding moves; from branch to branch
            while(*nextNode){
                currentNode = *nextNode;
                nextNode = (data < currentNode->data) ? &(currentNode->left) : &(currentNode->right);
                push(&traversed, currentNode);
            }

        // insert node in position
        *nextNode = newNode;

        // push added node to stack
        push(&traversed, newNode);
    }

    return traversed;
}