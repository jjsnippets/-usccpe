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

    int delValue, isDeleted;

    COLOR_BLUE;
    printf("=== DELETE A NODE ===\n");
    TEXT_RESET;
    printf("value to delete: ");
    scanf(" %d", &delValue);
    printf("\n");

    isDeleted = deleteNode(root, delValue, count);
    printf("Tree display: ");
    treeMode(*root);
    printf("\n");

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

    if (!*root) return 0;

    if (*size == 1){
        if ((*root)->x == data) {
            (*size)--;
            free(*root);
            *root = NULL;
            return 1;

        } else return 0;
    }

    NODE* toReplace = searchNode(*root, data);
    if (!toReplace) return 0;

    NODE* toDelete = *root;
    int movement = 1;
    for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
    movement >>= 1;

    for (; movement > 1; movement >>= 1)
        toDelete = (*size & movement) ? (toDelete->right) : (toDelete->left);
    toReplace->x = ((*size % 2) ? toDelete->right : toDelete->left)->x;

    if (*size % 2){
        free(toDelete->right);
        toDelete->right = NULL;
    }
    else {
        free(toDelete->left);
        toDelete->left = NULL;
    }

    (*size)--;
    return 1;
}

NODE* searchNode(NODE* tree, int find){

    if (!tree) return NULL;
    if (tree->x == find) return tree;

    NODE* result = NULL;

    if (tree->left) result = searchNode(tree->left, find);
    if (result) return result;

    if (tree->right) result = searchNode(tree->right, find);
    return result;
}
