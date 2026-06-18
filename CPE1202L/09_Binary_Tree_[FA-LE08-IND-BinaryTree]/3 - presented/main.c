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
    int count = 0;
    char userInput;

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
                addMenu(&root, &count);
                break;

            case '2':
                deleteMenu(&root, &count);
                break;

            case '3':
                traversalMenu(&root, &count);
                break;
        }
    } while (userInput != '4');
}
