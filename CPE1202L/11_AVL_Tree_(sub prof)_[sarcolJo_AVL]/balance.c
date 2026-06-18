/*
======================================================
FILE        : balance.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : implementation file for balancing trees
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
FUNCTION    : balanceTree
DESCRIPTION : balances a provided tree specified by 'root'
ARGUMENTS
    NODE** root - root of AVL tree
    LIST* checkNodes - nodes of the tree that needs their balance factors checked; provided by addNode() and deleteNode()
        check https://en.wikipedia.org/wiki/AVL_tree#Insert for why 'checkNodes' is implemented
======================================================
*/
void balanceTree(NODE** root, LIST* checkNodes){
    // when and while there are nodes that needs their balance factors checked
    if (checkNodes){
        while(checkNodes){
            NODE* checkBalance = pop(&checkNodes);
            NODE** currentNode = parentOf(root, checkBalance);
            // balance factor is defined as R-L; ie right-heavy trees have positive BF and left-heavy trees have negative BF
            int currentBF = treeDepth(checkBalance->right, 1) - treeDepth(checkBalance->left, 1);

            NODE* childOf;
            int nextBF;

            // when tree is right-heavy
            if (currentBF == 2){

                childOf = checkBalance->right;
                nextBF = treeDepth(childOf->right, 1) - treeDepth(childOf->left, 1);
                
                // when subtree is left-heavy, perform a R rotation on subtree
                if (nextBF == -1) checkBalance->right = rotateRight(childOf, childOf->left);
                // perform a L rotation on tree
                *currentNode = rotateLeft(checkBalance, checkBalance->right);

                // check https://en.wikipedia.org/wiki/AVL_tree#Delete for why 2 sets of rotations is needed at most to balance an AVL tree
                break;
            
            // similar to above; when tree is left-heavy
            } else if (currentBF == -2){
                childOf = checkBalance->left;
                nextBF = treeDepth(childOf->right, 1) - treeDepth(childOf->left, 1);
                
                // when subtree is right-heavy, perform a L rotation on subtree
                if (nextBF == 1) checkBalance->left = rotateLeft(childOf, childOf->right);
                // perform a R rotation on tree
                *currentNode = rotateRight(checkBalance, checkBalance->left);

                break;
            }
        }
    }
}

/*
======================================================
FUNCTION    : rotateLeft
DESCRIPTION : rotates a given tree 'A' to the left with the pivot its right child 'B'
ARGUMENTS
    NODE* A - some parent node
    NODE* B - right child of A

RETURNS
    NODE* - node of rotated tree
======================================================
*/
NODE* rotateLeft(NODE* A, NODE* B){
    A->right = B->left;
    B->left = A;
    return B;
}

/*
======================================================
FUNCTION    : rotateRight
DESCRIPTION : rotates a given tree 'A' to the right with the pivot its left child 'B'
ARGUMENTS
    NODE* A - some parent node
    NODE* B - left child of A

RETURNS
    NODE* - node of rotated tree
======================================================
*/
NODE* rotateRight(NODE* A, NODE* B){
    A->left = B->right;
    B->right = A;
    return B;
}

/*
======================================================
FUNCTION    : parentOf
DESCRIPTION : determines address of pointer to 'child' node
                  undefined behavior when 'child' is not in 'root'
              recursive implementation
ARGUMENTS
    NODE** root - root of AVL tree
    NODE* child - node to which its parent is to be determined

RETURNS
    NODE** - address of the pointer that points to 'child'; dereference it to obtain 'child'
======================================================
*/
NODE** parentOf(NODE** root, NODE* child){

    NODE** result;

    if(child->data == (*root)->data)
        result = root;
    else if(child->data < (*root)->data)
        result = parentOf(&((*root)->left), child);
    else
        result = parentOf(&((*root)->right), child);

    return result;
}

/*
======================================================
FUNCTION    : push
DESCRIPTION : push implemntation for a stack linked list
                  inserts at the head end
ARGUMENTS
    LIST** head - pointer to stack
    NODE* toAdd - node to add to stack
======================================================
*/
void push(LIST** head, NODE* toAdd){
    LIST* newHead = calloc(1, sizeof(LIST));
    newHead->node = toAdd;

    if (*head) newHead->next = *head;

    *head = newHead;
}

/*
======================================================
FUNCTION    : pop
DESCRIPTION : pop implemntation for a stack linked list
                  removes at the head end
ARGUMENTS
    LIST** head - pointer to stack

RETURNS
    NODE* - newest node that was added to stack
======================================================
*/
NODE* pop(LIST** head){
    NODE* result = (*head)->node;
    *head = (*head)->next;
    return result;
}
