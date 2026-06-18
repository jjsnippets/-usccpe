#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void deleteMenu(NODE** maxHeap, NODE** minHeap, int* count){

    char repeat = 'y';

    do {
        COLOR_BLUE;
        printf("=== DELETE ROOT NODE ===\n");
        TEXT_RESET;

        int copyCount = *count;

        if(!*maxHeap){
            printf("\n");
            COLOR_RED;
            printf("FAILED!\n");
            TEXT_RESET;
            printf("No nodes to delete\n");
            printf("Press any key to return to main menu\n");
            getche();
            return;
        } else {
            MAX_COLOR;
            printf("Max Heap = %s %02d deleted:", (*maxHeap)->text, (*maxHeap)->data);
            TEXT_RESET;
            deleteMax(maxHeap, (*maxHeap)->data, count);
            treeDisplay(*maxHeap, -999);
            printf("\n");

            MIN_COLOR;
            printf("Min Heap = %s %02d deleted:", (*minHeap)->text, (*minHeap)->data);
            TEXT_RESET;
            deleteMin(minHeap, (*minHeap)->data, &copyCount);
            treeDisplay(*minHeap, -999);
            printf("\n");
        }

        printf("Again [y/n]?");
        repeat = tolower(getche());
        printf("\n\n");

    } while (repeat != 'n');
}

void deleteMax(NODE** root, int delValue, int* size){

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
        strncpy(toReplace->text, ((*size % 2) ? toDelete->right : toDelete->left)->text, 4);

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

            NODE* left = topNode->left;
            NODE* right = topNode->right;

            NODE* bottomNode = left;
            if (right) if (right->data > left->data) bottomNode = right;

            if (bottomNode->data < topNode->data) break;

            int temp = bottomNode->data;
            bottomNode->data = topNode->data;
            topNode->data = temp;

            char tempText[4];
            strncpy(tempText, topNode->text, 4);
            strncpy(topNode->text, bottomNode->text, 4);
            strncpy(bottomNode->text, tempText, 4);

            topNode = bottomNode;

        }
    }

    return;
}

void deleteMin(NODE** root, int delValue, int* size){

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
        strncpy(toReplace->text, ((*size % 2) ? toDelete->right : toDelete->left)->text, 4);

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

            NODE* left = topNode->left;
            NODE* right = topNode->right;

            NODE* bottomNode = left;
            if (right) if (right->data < left->data) bottomNode = right;

            if (bottomNode->data > topNode->data) break;

            int temp = bottomNode->data;
            bottomNode->data = topNode->data;
            topNode->data = temp;

            char tempText[4];
            strncpy(tempText, topNode->text, 4);
            strncpy(topNode->text, bottomNode->text, 4);
            strncpy(bottomNode->text, tempText, 4);

            topNode = bottomNode;

        }
    }

    return;
}
