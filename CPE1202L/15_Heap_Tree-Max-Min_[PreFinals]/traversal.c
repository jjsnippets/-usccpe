#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

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

void showLeaves(NODE* root, int depth, int match){
    if (root){
        showLeaves(root->left, depth + 1, match);
        MOVE_DOWN(depth);
        if (root->data == match) COLOR_PINK;
        printf("[%3s %02d]", root->text, root->data);
        if (root->data == match) TEXT_RESET;
        MOVE_UP(depth);
        MOVE_LEFT(1);
        showLeaves(root->right, depth + 1, match);
    }
}
