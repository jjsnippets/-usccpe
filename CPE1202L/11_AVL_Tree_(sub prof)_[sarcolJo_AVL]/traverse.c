/*
======================================================
FILE        : traverse.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : implementation file displaying tree traversals
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

#include "formatting.h"

/*
======================================================
FUNCTION    : traverseMenu
DESCRIPTION : displays tree traversal methods
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void traverseMenu(NODE* root){

    COLOR_BLUE;
    printf("=== TRAVERSE TREE ===\n");
    TEXT_RESET;

    printf("Breadth-first: ");
    breadthFirst(root);
    printf("\n");

    printf("Depth-first Inorder Traversal: ");
    inFix(root);
    printf("\n");

    printf("Depth-first Prefix Traversal: ");
    preFix(root);
    printf("\n");

    printf("Depth-first Postfix Traversal: ");
    postFix(root);
    printf("\n");

    printf("Tree display: ");
    treeDisplay(root, -999); // -999 as an arbitrary value
    printf("\n");

    printf("Press any key to continue\n");
    getche();
}

/*
======================================================
FUNCTION    : breadthFirst
DESCRIPTION : displays breath first tree traversal method
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void breadthFirst(NODE* root){
    // when tree has contents
    if (root){
        // initialization step
        LIST* bft = NULL;
        NODE* toPrint = NULL;
        enqueue(&bft, root);

        // loop through all nodes, breadth first arragement
        while (bft){
            toPrint = dequeue(&bft);
            if (toPrint->left) enqueue(&bft, toPrint->left);
            if (toPrint->right) enqueue(&bft, toPrint->right);
            printf("%d ", toPrint->data);
        }
    }
}

/*
======================================================
FUNCTION    : inFix
DESCRIPTION : displays infix tree traversal method
              recursive implementation
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void inFix(NODE* root){
    // when tree has contents
    if (root){
        inFix(root->left);
        printf("%d ", root->data);
        inFix(root->right);
    }
}

/*
======================================================
FUNCTION    : preFix
DESCRIPTION : displays prefix tree traversal method
              recursive implementation
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void preFix(NODE* root){
    // when tree has contents
    if (root){
        printf("%d ", root->data);
        preFix(root->left);
        preFix(root->right);
    }
}

/*
======================================================
FUNCTION    : postFix
DESCRIPTION : displays postfix tree traversal method
              recursive implementation
ARGUMENTS
    NODE* root - root of AVL tree
======================================================
*/
void postFix(NODE* root){
    if (root){
        postFix(root->left);
        postFix(root->right);
        printf("%d ", root->data);
    }
}

/*
======================================================
FUNCTION    : treeDisplay
DESCRIPTION : displays tree in a tree shape
              preparatory function to showLeaves()
ARGUMENTS
    NODE* root - root of AVL tree
    int match - value of node to be highlighted; set to an arbitrary value if unspecified
======================================================
*/
void treeDisplay(NODE* root, int match){
    // when tree has contents
    if (root){
        // determines vertical height of tree
        int maxDepth = treeDepth(root, 1);
        for (int i = 0; i < maxDepth; i++)
            printf("\n");
        MOVE_UP(maxDepth);

        // calls function to print individual leaves
        showLeaves(root, 1, match);

        // move to bottom of terminal
        MOVE_DOWN(maxDepth);
    }
    printf("\n");
}

/*
======================================================
FUNCTION    : treeDepth
DESCRIPTION : determines height of a tree
              recursive implementation
ARGUMENTS
    NODE* root - root of subtree; set to root when initially called
    int depth - current depth of node; set to 1 when initially called

RETURNS
    int - depth of tree at node 'root'
======================================================
*/
int treeDepth(NODE* root, int depth){
    int result;

    if (!root)
        result = depth - 1;

    else{
        int dLeft = treeDepth(root->left, depth + 1);
        int dRight = treeDepth(root->right, depth + 1);
        result = (dLeft > dRight) ? dLeft : dRight;
    }

    return result;
}

/*
======================================================
FUNCTION    : showLeaves
DESCRIPTION : displays individual branches and leaves of a tree
              before calling, enough vertical lines should be allocated for the tree to be displayed properly
                  this is already handled by treeDisplay(); so it should be called instead
              recursive implementation
ARGUMENTS
    NODE* root - root of AVL tree
    int depth - current depth of node; set to 1 when initially called
    int match - value of node to be highlighted; set to an arbitrary value if unspecified
======================================================
*/
void showLeaves(NODE* root, int depth, int match){
    if (root){
        showLeaves(root->left, depth + 1, match);
        MOVE_DOWN(depth);
        if (root->data == match) COLOR_PINK;
        printf("[%3d]", root->data);
        if (root->data == match) TEXT_RESET;
        MOVE_UP(depth);
        MOVE_LEFT(1);
        showLeaves(root->right, depth + 1, match);
    }
}

/*
======================================================
FUNCTION    : enqueue
DESCRIPTION : enqueue implemntation for a queue linked list
                  inserts at the tail end
ARGUMENTS
    LIST** head - pointer to queue
    NODE* toAdd - node to add to queue
======================================================
*/
void enqueue(LIST** head, NODE* toAdd){
    if (!*head){
        *head = calloc(1, sizeof(LIST));
        (*head)->node = toAdd;

    } else {
        LIST* lastQueue = *head;
        LIST* insert = calloc(1, sizeof(LIST));
        insert->node = toAdd;

        while (lastQueue->next) lastQueue = lastQueue->next;
        lastQueue->next = insert;
    }
}

/*
======================================================
FUNCTION    : dequeue
DESCRIPTION : dequeue implemntation for a queue linked list
                  removes at the head end
ARGUMENTS
    LIST** head - pointer to queue

RETURNS
    NODE* - oldest node that was added to queue
======================================================
*/
NODE* dequeue(LIST** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->node;

    LIST* newHead = ((*head)->next) ? (*head)->next : NULL;

    *head = newHead;
    return result;
}
