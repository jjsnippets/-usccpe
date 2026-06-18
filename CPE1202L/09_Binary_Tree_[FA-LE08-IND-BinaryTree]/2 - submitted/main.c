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

void main(){

    NODE* root = calloc(1, sizeof(NODE));
    int count = 0;
    char userInput;

    for (int i = 1; i < 9; i++)
        addNode(&root, i, &count);

    do{

        system("cls");
        BOLD_TEXT;
        printf("[%d]\n", count);
        printf("=== MAIN MENU ===\n");
        TEXT_RESET;
        printf("[1] Add new node\n");
        printf("[2] Delete a node\n");
        printf("[3] Traverse binary tree\n");
        printf("[4] Exit\n");

        userInput = getche();
        printf("\n\n");

        switch (userInput) {
            case '1':
                addMenu(&root, &count);
                break;

            case '2':
                deleteMenu(&root, &count);
                break;

            case '3':
                // traversalMenu(&root, &count);
                break;
        }
    } while (userInput != '4');



    /*
        for (int i = 1; i < 9; i++)
            addNode(&root, i, &count);

        displayAll(root, count);

        deleteNode(&root, 9, &count);
        deleteNode(&root, 2, &count);
        deleteNode(&root, 4, &count);
        deleteNode(&root, 1, &count);
        deleteNode(&root, 4, &count);
        deleteNode(&root, 5, &count);

        displayAll(root, count);
    */
}

void displayNode(NODE* toShow){

    // debug
    if (toShow == NULL) return;

    printf("[%d %ld %ld:%d %ld:%d]\n", toShow->x, toShow, toShow->left,(toShow->left) ? toShow->left->x : -999 , toShow->right, (toShow->right) ? toShow->right->x : -999);

    printf("Parent: %d\n", toShow->x);

    if (toShow->left)
        printf("\tLeft child: %d\n", toShow->left->x);
    if (toShow->right)
        printf("\tRight child: %d\n", toShow->right->x);

    printf("\n");

}

void displayAll(NODE* root, int size){

    if (!size) return;

    QUEUE* bft = calloc(1, sizeof(QUEUE));
    NODE* display;
    enqueue(&bft, root);

    while(size--){

        display = dequeue(&bft);
        displayNode(display);

        if (display->left) enqueue(&bft, display->left);
        if (display->right) enqueue(&bft, display->right);

    }
    free(bft);
}
