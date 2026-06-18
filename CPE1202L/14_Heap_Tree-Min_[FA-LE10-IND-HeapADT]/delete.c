#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void deleteMenu(NODE** root, int* count){

    COLOR_BLUE;
    printf("=== DELETE NODE ===");
    TEXT_RESET;

    if(!*root){
        printf("\n");
        COLOR_RED;
        printf("FAILED!\n");
        TEXT_RESET;
        printf("No nodes to delete\n");
    } else {
        deleteNode(root, (*root)->data, count);
        COLOR_GREEN;
        printf("Success!\n");
        TEXT_RESET;
        printf("Node removed\n");
    }

    printf("Press any key to return to main menu\n");
    getche();
}

void deleteNode(NODE** root, int delValue, int* size){

    treeDisplay(*root, delValue);
    printf("\n");
    waitForUser();

    if (*size == 1){
        (*size)--;
        free(*root);
        *root = NULL;
        printf("\n");

    } else {

        // root node is one to be deleted
        NODE* toReplace = *root;

        // determines the last node and sets it to NULL
        NODE* toDelete = *root;
        int movement = 1;
        for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
        movement >>= 1;

        for (; movement > 1; movement >>= 1)
            toDelete = (*size & movement) ? (toDelete->right) : (toDelete->left);
        toReplace->data = ((*size % 2) ? toDelete->right : toDelete->left)->data;

        if (*size % 2){
            free(toDelete->right);
            toDelete->right = NULL;
        }
        else {
            free(toDelete->left);
            toDelete->left = NULL;
        }

        (*size)--;

        // sinking
        NODE* topNode = *root;

        while (topNode->left){
            treeDisplay(*root, topNode->data);
            printf("\n");
            waitForUser();

            NODE* left = topNode->left;
            NODE* right = topNode->right;

            NODE* bottomNode = left;
            if (right) if (right->data < left->data) bottomNode = right;

            if (bottomNode->data > topNode->data) break;

            int temp = bottomNode->data;
            bottomNode->data = topNode->data;
            topNode->data = temp;

            topNode = bottomNode;

        }

        treeDisplay(*root, topNode->data);
        printf("\n");
    }

    return;
}
