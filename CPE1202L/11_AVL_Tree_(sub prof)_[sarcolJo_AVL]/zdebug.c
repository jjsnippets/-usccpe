#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "add.h"
#include "traverse.h"
#include "formatting.h"

#include "zdebug.h"

void balanceDisplay(NODE* root){
    if (root){
        printf("TREE BALANCE");
        int maxDepth = treeDepth(root, 1);

        for (int i = 0; i < maxDepth; i++) printf("\n");
        MOVE_UP(maxDepth);
        showBalance(root, 1);
        MOVE_DOWN(maxDepth);
        printf("\n");
    }
}

void showBalance(NODE* root, int depth){
    if (root){
        showBalance(root->left, depth + 1);
        MOVE_DOWN(depth);
        printf("[%3d <%3d>]", root->data, treeDepth(root->right, 1) - treeDepth(root->left, 1));
        MOVE_UP(depth);
        MOVE_LEFT(1);
        showBalance(root->right, depth + 1);
    }
}

void printNode(NODE* toShow){
    if(!toShow) return;

    printf("[%d <%d>]\n", toShow->data, treeDepth(toShow->right, 1) - treeDepth(toShow->left, 1));

}