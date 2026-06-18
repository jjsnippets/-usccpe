#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void splayTree(NODE** root, LIST* checkNodes){
    if(checkNodes){
        while(checkNodes){

            NODE* childNode = pop(&checkNodes);
            treeDisplay(*root, childNode->data);

            if(!checkNodes) break;

            NODE* parentNode = pop(&checkNodes);
            int cpRotate = childNode->data > parentNode->data;

            if (checkNodes){
                NODE* grandparentNode = pop(&checkNodes);
                NODE** connectionNode = parentOf(root, grandparentNode);
                int pgRotate = parentNode->data > grandparentNode->data;

                // zig-zag or two-rotation variants
                if (pgRotate){
                    if (cpRotate){
                        rotateLeft(grandparentNode, parentNode);
                        *connectionNode = rotateLeft(parentNode, childNode);
                    } else {
                        grandparentNode->right = rotateRight(parentNode, childNode);
                        *connectionNode = rotateLeft(grandparentNode, grandparentNode->right);
                    }
                } else {
                    if (cpRotate){
                        grandparentNode->left = rotateLeft(parentNode, childNode);
                        *connectionNode = rotateRight(grandparentNode, grandparentNode->left);
                    } else {
                        rotateRight(grandparentNode, parentNode);
                        *connectionNode = rotateRight(parentNode, childNode);
                    }
                }
                push(&checkNodes, *connectionNode);

            } else {
                // zig or zag
                parentNode = (cpRotate) ? rotateLeft(parentNode, childNode) : rotateRight(parentNode, childNode);
                *root = parentNode;
                push(&checkNodes, *root);
            }

            waitForUser();
        }
    } else 
        treeDisplay(*root, -999);
    
    printf("\n");
}

NODE* rotateLeft(NODE* A, NODE* B){
    A->right = B->left;
    B->left = A;
    return B;
}

NODE* rotateRight(NODE* A, NODE* B){
    A->left = B->right;
    B->right = A;
    return B;
}

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
