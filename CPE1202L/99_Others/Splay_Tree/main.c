// WARNING: since this is a copy from AVL, some comments may not relevant and some functions may not be called in this code

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "functions.h"

int main(){

    NODE* root = NULL;
    char userInput;


    // main menu loop
    do{
        system("cls");
        BOLD_TEXT;
        printf("=== MAIN MENU ===\n");
        TEXT_RESET;
        printf("[1] Add new node\n");
        printf("[2] Delete a node\n");
        printf("[3] Search for a node\n");
        printf("[4] Traverse binary tree\n");
        printf("[5] Exit\n");

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
                searchMenu(&root);
                break;

            case '4':
                traverseMenu(root);
                break;
        }
    } while (userInput != '5');
}