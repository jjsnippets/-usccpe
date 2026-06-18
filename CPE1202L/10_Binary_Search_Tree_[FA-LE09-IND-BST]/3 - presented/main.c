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

    NODE* root = NULL;
    char userInput;

    // [10, 6, 2, 21, 17, 13, 9, 5, 1, 20, 16]
    // for (int i = 0; i < 11; i++) addNode(&root, ((i+9)*295) % 23);

    do{
        system("cls");
        BOLD_TEXT;
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
                addMenu(&root);
                break;

            case '2':
                deleteMenu(&root);
                break;

            case '3':
                traversalMenu(&root);
                break;
        }
    } while (userInput != '4');
    freeTree(root);
}

void displayNode(NODE* toShow){

    if (!toShow) return;

    // debug
    printf("[%ld:%d %ld:%d %ld:%d]\n", toShow, toShow->x, toShow->left, (toShow->left) ? toShow->left->x : -999, toShow->right, (toShow->right) ? toShow->right->x : -999);

    printf("Parent: %d\n", toShow->x);

    if (toShow->left)
        printf("\tLeft child: %d\n", toShow->left->x);
    if (toShow->right)
        printf("\tRight child: %d\n", toShow->right->x);

    printf("\n");

}

void displayAll(NODE* root){

    if (!root) return;

    QUEUE* bft = NULL;
    enqueue(&bft, root);

    while (bft){

        NODE* display = dequeue(&bft);
        displayNode(display);

        if (display->left) enqueue(&bft, display->left);
        if (display->right)enqueue(&bft, display->right);
    }
}
