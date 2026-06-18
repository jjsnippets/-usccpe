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

void deleteMenu(NODE** root, int* count){

    int newValue, isDeleted;

    COLOR_BLUE;
    printf("=== DELETE A NODE ===\n");
    TEXT_RESET;
    printf("value to delete: ");
    scanf(" %d", &newValue);
    printf("\n");

    isDeleted = deleteNode(root, newValue, count);
    printf("!!!\n");
    displayAll(*root, *count);

    if (isDeleted){
        COLOR_GREEN;
        printf("Success!\n");
        TEXT_RESET;
        printf("Node removed\n");
    } else {
        COLOR_RED;
        printf("FAILED!\n");
        TEXT_RESET;
        printf("Data not found in tree\n");
    }

    printf("Press any key to continue\n");
    getche();

}

int deleteNode(NODE** root, int data, int* size){

    if (*size < 1) return 0;

    if (*size == 1){
        if ((*root)->x == data){
            (*size)--;
            *root = calloc(1, sizeof(NODE));
            return 1;

        } else return 0;
    }


    NODE* parentDelete = calloc(1, sizeof(NODE));

    NODE* toLastNode = *root;
    int movement = 1;
    for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
    movement >>= 1;

    if (*size > 1){
        for (; movement > 1; movement >>= 1){

            if (*size & movement){
                (toLastNode = toLastNode->right);
            } else {
                (toLastNode = toLastNode->left);
            }
        }
    }

    if ((*root)->x == data){
        (*size)--;
        NODE* leftReattach = (*size > 1) ? (*root)->left : NULL;
        NODE* rightReattach = (*size > 2) ? (*root)->right : NULL;

        (*root) = (toLastNode->right) ? toLastNode->right : toLastNode->left;
        (*root)->left = leftReattach;
        (*root)->right = rightReattach;

        if (toLastNode->right){
            toLastNode->right = NULL;
        } else
            toLastNode->left = NULL;

        // printf("Successfully removed!\n");
        return 1;

    } else {

        parentDelete = postOrderSearch(*root, data);
        if (parentDelete){
            (*size)--;
            int lastData = ((toLastNode->right) ? toLastNode->right : toLastNode->left)->x;
            // printf(" *%d ", lastData);

            displayNode(parentDelete);
            NODE* deleteNode = (parentDelete->left->x == data) ? parentDelete->left : parentDelete->right;
            displayNode(deleteNode);
            displayNode(toLastNode);

            NODE *leftReattach, *rightReattach;

            if (deleteNode->left)
                leftReattach = (deleteNode->left->x != lastData) ? deleteNode->left : NULL;
            else
                leftReattach = NULL;

            printf("Left reattach: %ld, %d\n", leftReattach, !leftReattach);

            if (deleteNode->right)
                rightReattach = (deleteNode->right->x != lastData) ? deleteNode->right : NULL;
            else
                rightReattach = NULL;

            printf("Right reattach: %ld, %d\n", rightReattach, !rightReattach);

            displayNode(leftReattach);
            displayNode(rightReattach);

            // printf("{%d %d %d}\n", deleteNode->left->x, deleteNode->right->x, lastData);

            if (parentDelete->left->x == data){
                parentDelete->left = (toLastNode->right) ? toLastNode->right : toLastNode->left;

                    // reattach to new node
                if (toLastNode->right){
                    parentDelete->left->left = leftReattach;
                    parentDelete->left->right = rightReattach;
                } else {
                    parentDelete->left->left = leftReattach;
                    parentDelete->left->right = rightReattach;
                }

            } else {
                parentDelete->right = (toLastNode->right) ? toLastNode->right : toLastNode->left;

                    // reattach to new node
                if (toLastNode->right){
                    parentDelete->right->left = leftReattach;
                    parentDelete->right->right = rightReattach;
                } else {
                    parentDelete->right->left = leftReattach;
                    parentDelete->right->right = rightReattach;
                }
            }

            // if (toLastNode->right){
            //    toLastNode->right = NULL;
            //  } else
            //    toLastNode->left = NULL;

            // printf("Successfully removed!\n");
            return 1;

        } else
            // printf("Data not found.\n");
            return 0;
    }
}

NODE* postOrderSearch(NODE* tree, int find){

    NODE* result = NULL;

    if (tree->left){

        if (tree->left->x == find){
            return tree;
        }

        else if (tree->left == NULL){
            return NULL;
        }

        else{
            result = postOrderSearch(tree->left, find);
            if (result)
                return result;

        }
    }

    if (tree->right){

        if (tree->right->x == find){
            return tree;
        }

        else if (tree->right == NULL){
            return NULL;
        }

        else{
            result = postOrderSearch(tree->right, find);
            if (result)
                return result;
        }
    }

    return result;
}
