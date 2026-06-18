/*
======================================================
FILE        : main.c
AUTHORS     : Sarcol, Joshua
DESCRIPTION : main file, calls other functions
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          sarcol          made file
2024-03-28          sarcol          modified function calls

======================================================
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "add.h"
#include "delete.h"
#include "search.h"
#include "traverse.h"

#include "balance.h"
#include "formatting.h"

/*
======================================================
FUNCTION    : main
DESCRIPTION : implementation of a AVL tree with add, remove, search, and traverse functions
ARGUMENTS

RETURNS
    int - returns 0, indicates success

======================================================
*/
int main(){

    NODE* root = NULL;
    char userInput;

    // debugging values
    // [10, 6, 2, 21, 17, 13, 9, 5, 1, 20, 16]
    // for (int i = 0; i < 11; i++) {
    //     LIST* check = addNode(&root, ((i+9)*295) % 23);
    //     balanceTree(&root, check);
    // }

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
                searchMenu(root);
                break;

            case '4':
                traverseMenu(root);
                break;
        }
    } while (userInput != '5');
}