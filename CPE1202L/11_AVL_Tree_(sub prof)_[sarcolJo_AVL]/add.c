/*
======================================================
FILE        : traverse.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : implementation file for adding a node into a tree
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "add.h"
#include "traverse.h"

#include "balance.h"
#include "formatting.h"

/*
======================================================
FUNCTION    : addMenu
DESCRIPTION : submenu for adding a node into an AVL tree, prompts from user value to be added to tree
ARGUMENTS
    NODE** root - root of AVL tree
======================================================
*/
void addMenu(NODE** root){

    int newValue;

    // submenu
    COLOR_BLUE;
    printf("=== ADD NEW NODE ===\n");
    TEXT_RESET;
    printf("Insert value to add: ");
    scanf(" %d", &newValue);
    printf("\n");

    // initial adding of value to tree
    LIST* checkBalance = addNode(root, newValue);
    printf("Before balancing: ");
    treeDisplay(*root, newValue);
    printf("\n");

    // balancing of tree
    balanceTree(root, checkBalance);
    printf("After balancing: ");
    treeDisplay(*root, newValue);
    printf("\n");

    // presents result
    COLOR_GREEN;
    printf("Success!\n");
    TEXT_RESET;
    printf("Node added\n");
    printf("Press any key to continue\n");
    getche();
}

/*
======================================================
FUNCTION    : addNode
DESCRIPTION : adds a value 'data' into the AVL tree specified ('root') 
ARGUMENTS
    NODE** root - root of AVL tree
    int data - value to be added into tree

RETURNS
    LIST* - a linked list (stack) of nodes visited by the function; to be used by balanceTree()
======================================================
*/
LIST* addNode(NODE** root, int data){
    LIST* traversed = NULL;

    // when tree is empty
    if (!*root){
        *root = calloc(1, sizeof(NODE));
        (*root)->data = data;

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
    }

    return traversed;
}