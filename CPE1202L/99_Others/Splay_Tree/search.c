/*
======================================================
FILE        : search.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : implementation file for searching a node from a tree
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

/*
======================================================
FUNCTION    : searchMenu
DESCRIPTION : submenu for searching a node from an AVL tree, either smallest, largest, or user defined
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void searchMenu(NODE** root){

    char* input = calloc(25, sizeof(char));
    int searchFor;
    NODE* match = *root;
    LIST* searchPath = NULL;

    // submenu
    COLOR_BLUE;
    printf("=== SEARCH A NODE ===\n");
    TEXT_RESET;
    printf("[S] Smallest node\n");
    printf("[L] Largest node\n");
    printf("Or enter a specific number\n");
    scanf(" %25[^\n]s", input);
    printf("\n");

    // when user-defined number
    if (isdigit(*input)) {
        // converts number from string to integer
        searchFor = atoi(input);

        // traverses tree to find value
        searchNodePath(*root, &searchPath, searchFor);

        // if value is not tree
        if (searchPath->node->data != searchFor){
            printf("Value %d is not found in tree!\n", searchFor);
            printf("Last node visited: %d\n", searchPath->node->data);
            searchFor = searchPath->node->data;

        // otherwise
        } else
            printf("Value %d is in tree!\n", searchFor);
        
    // when smallest or largest value
    } else {
        char userChoice = tolower(*input);

        // determine smallest value
        if (userChoice == 's')
            while((match->left))
                match = match->left;

        // determines largest value
        else
            while((match->right))
                match = match->right;

        // prints determined values
        searchFor = match->data;
        searchNodePath(*root, &searchPath, searchFor);
        printf("%s value is %d\n", (userChoice == 's') ? "Smallest" : "Largest", searchFor);
    }

    // prints tree
    splayTree(root, searchPath);
    printf("Finished splaying!\n");
    printf("Press any key to continue\n");
    getche();

}

/*
======================================================
FUNCTION    : searchNode
DESCRIPTION : searches for node that contains the value specified at 'x'
              recursive implementation
ARGUMENTS
    NODE* root - root of AVL tree
    int x - value to search

RETURNS
    NODE* - node that contains the value being search for
======================================================
*/
NODE* searchNode(NODE* root, int x){
    NODE* result;

    // when node is NULL
    if (!root)
        result = NULL;
    
    // when node is found
    else if (root->data == x)
        result = root;

    // otherwise, recursive call
    else
        result = searchNode((root->data > x) ? root->left : root->right, x);
    
    return result;
}

LIST* searchNodePath(NODE* root, LIST** result, int x){
    // when node is NULL
    if (!root) 
        return *result;
    
    // when node is found
    else if (root->data == x){
        push(result, root);
        return *result;
    }

    // otherwise, recursive call
    else {
        push(result, root);
        return (root->data > x) ? searchNodePath(root->left, result, x) : searchNodePath(root->right, result, x);
    }
}