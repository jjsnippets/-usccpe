#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void main(){

    NODE* root = NULL;
    int count = 0;
    char userInput;

    do{
        system("cls");
        BOLD_TEXT;
        printf("=== MIN HEAP MAIN MENU ===\n");
        TEXT_RESET;
        printf("[1] Add new node\n");
        printf("[2] Delete a node\n");
        printf("[3] Exit\n");

        userInput = getche();
        printf("\n\n");

        switch (userInput) {
            case '1':
                addMenu(&root, &count);
                break;

            case '2':
                deleteMenu(&root, &count);
                break;
        }
    } while (userInput != '3');
}
