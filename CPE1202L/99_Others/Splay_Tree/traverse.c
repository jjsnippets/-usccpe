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
        printf("[%3d]", root->data);
        if (root->data == match) TEXT_RESET;
        MOVE_UP(depth);
        MOVE_LEFT(1);
        showLeaves(root->right, depth + 1, match);
    }
}

void waitForUser(){

    printf("Press any key to continue\n");
    while(!isspace(getche())) printf("\b\b");

}

// start of tree traversal functions
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

    void inFix(NODE* root){
        // when tree has contents
        if (root){
            inFix(root->left);
            printf("%d ", root->data);
            inFix(root->right);
        }
    }

    void preFix(NODE* root){
        // when tree has contents
        if (root){
            printf("%d ", root->data);
            preFix(root->left);
            preFix(root->right);
        }
    }

    void postFix(NODE* root){
        if (root){
            postFix(root->left);
            postFix(root->right);
            printf("%d ", root->data);
        }
    }

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

    NODE* dequeue(LIST** head){

        NODE* result = calloc(1, sizeof(NODE));
        result = (*head)->node;

        LIST* newHead = ((*head)->next) ? (*head)->next : NULL;

        *head = newHead;
        return result;
    }
