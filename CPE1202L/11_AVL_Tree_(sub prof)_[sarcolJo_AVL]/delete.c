/*
======================================================
FILE        : delete.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : implementation file for removing a node from a tree
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
#include "delete.h"
#include "search.h"
#include "traverse.h"

#include "balance.h"
#include "formatting.h"

/*
======================================================
FUNCTION    : deleteMenu
DESCRIPTION : submenu for removing a node from an AVL tree, prompts from user value to be deleted
ARGUMENTS
    NODE** root - root of AVL tree
======================================================
*/
void deleteMenu(NODE** root){

    int delValue;

    // submenu
    COLOR_BLUE;
    printf("=== DELETE A NODE ===\n");
    TEXT_RESET;
    printf("value to delete: ");
    scanf(" %d", &delValue);
    printf("\n");

    // determines first if value is in tree
    NODE* isPresent = searchNode(*root, delValue);
    printf("Tree display: ");
    treeDisplay(*root, delValue);
    printf("\n");

    // if value is not in tree
    if (!isPresent){
        COLOR_RED;
        printf("FAILED!\n");
        TEXT_RESET;
        printf("Data not found in tree\n");
        printf("\n");

    // otherwise
    } else {
        COLOR_GREEN;
        printf("Success!\n");
        TEXT_RESET;
        printf("Node removed\n");
        printf("\n");

        // initial removal of node from tree
        LIST* checkBalance = deleteNode(root, delValue);
        printf("Before balancing: ");
        treeDisplay(*root, -999);
        printf("\n");

        // balancing of tree
        balanceTree(root, checkBalance);
        printf("After balancing: ");
        treeDisplay(*root, -999);
        printf("\n");
    }

    printf("Press any key to continue\n");
    getche();
}

/*
======================================================
FUNCTION    : deleteNode
DESCRIPTION : removes a value 'data' into the AVL tree specified ('root')
              replacement node is the node that comes after it (inOrder arrangement)
                  undefined behavior when 'data' is not in 'root'
ARGUMENTS
    NODE** root - root of AVL tree
    int data - value to be removed into tree

RETURNS
    LIST* - a linked list (stack) of nodes visited by the function; to be used by balanceTree()
======================================================
*/
LIST* deleteNode(NODE** root, int data){

    LIST* traversed = NULL;
    NODE* toDelete = *root;

    // traversal to the node to be deleted ('toDelete')
    while(toDelete->data != data){
        push(&traversed, toDelete);
        toDelete = (toDelete->data > data) ? toDelete->left : toDelete->right;
    }

    // pointer that points to 'toDelete'
    NODE** parentNode = parentOf(root, toDelete);
    
    // value that replaces 'toDelete' ('toReplace')
    NODE* toReplace = toDelete->right;

    // when nodes right of 'toDelete' exist
    if(toReplace){
        // determines leftmost node
        while(toReplace->left)
            toReplace = toReplace->left;

        // parent of replacement node
        NODE** upperCon = parentOf(root, toReplace);

        // right subtree of replacement node
        NODE* lowerCon = toReplace->right;

        // deletion of 'data'
        (*parentNode)->data = toReplace->data;

        // reconnecting right subtree to parent
        *upperCon = lowerCon;

    // when there are no nodes to the right of 'toDelete'
    } else 
        // replace 'toDelete'
        *parentNode = toDelete->left;

    // when replaced node exists; ie not NULL
    if(*parentNode){
        push(&traversed, *parentNode);

        // when replaced node has right children
        if((*parentNode)->right)
            push(&traversed, (*parentNode)->right);
    }

    return traversed;
}