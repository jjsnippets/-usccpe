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

void deleteNode(NODE** root, int data, int* count){

    printf("CALLED FUNCTION\n");

    NODE* toDelete = calloc(1, sizeof(NODE));
    NODE* parentDelete;

    // if ((*root)->x = data){

    // } else {

        toDelete = *root;

        while(1){
            printf("<%d %d>", data, toDelete->x);

            if (data == toDelete->x){
                break;
            }

            if (data < toDelete->x){
                if (toDelete->left) {
                    printf("went left\n");
                    parentDelete = toDelete;
                    toDelete = toDelete->left;
                    continue;
                } else {
                    printf("end of left\n");
                    parentDelete = NULL;
                    toDelete = NULL;
                    break;
                }
            } else if (data > toDelete->x){
                if (toDelete->right) {
                    printf("went right\n");
                    parentDelete = toDelete;
                    toDelete = toDelete->right;
                    continue;
                } else {
                    printf("end of right\n");
                    parentDelete = NULL;
                    toDelete = NULL;
                    break;
                }
            }
        }

        if (!toDelete) {
            return;

        } else {
            displayNode(parentDelete);
            displayNode(toDelete);

            NODE* reconnectNode = toDelete;

            if (toDelete->right){
                reconnectNode = toDelete->right;
                while (reconnectNode->left) reconnectNode = reconnectNode->left;
                // ENDED HERE

            }



        }






    // }




}
