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

    // [10, 6, 2, 21, 17, 13, 9, 5, 1, 20, 16]
    for (int i = 0; i < 11; i++){
        // printf("[%d %d] ", i, ((i+10)*295) % 23);
        addNode(&root, ((i+9)*295) % 23, &count);
    }

    // addNode(&root, 6, &count);
    // addNode(&root, 2, &count);
    // addNode(&root, 11, &count);

    displayAll(root, count);

    printf("===\n");

    deleteNode(&root, 17, &count);

    printf("=CODE RAN WITHOUT CRASHING=\n\n");

}

void displayNode(NODE* toShow){

    // debug
    printf("[%d %ld %ld %ld]\n", toShow->x, toShow, toShow->left, toShow->right);

    printf("Parent: %d\n", toShow->x);

    if (toShow->left)
        printf("\tLeft child: %d\n", toShow->left->x);
    if (toShow->right)
        printf("\tRight child: %d\n", toShow->right->x);

    printf("\n");

}

void displayAll(NODE* root, int count){

    if (!count) return;
    int inLine = 1;

    QUEUE* bft = calloc(1, sizeof(QUEUE));
    enqueue(&bft, root);

    while (inLine){

        NODE* display = dequeue(&bft);
        displayNode(display);
        inLine--;

        if (display->left){
            enqueue(&bft, display->left);
            inLine++;
        }
        if (display->right){
            enqueue(&bft, display->right);
            inLine++;
        }
    }
}
