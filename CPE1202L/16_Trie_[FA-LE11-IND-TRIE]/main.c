#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

int main(){

    NODE* root = calloc(1, sizeof(NODE));
    int longestWord = 0;
    char userInput;

    do{

        system("cls");
        BOLD_TEXT;
        printf("=== TRIE MAIN MENU ===\n");
        TEXT_RESET;
        printf("[1] Add new word\n");
        printf("[2] Delete word\n");
        printf("[3] Show Trie Tree\n");
        printf("[4] Exit\n");

        userInput = getche();
        printf("\n\n");

        switch (userInput) {
            case '1':
                addMenu(&root, &longestWord);
                break;

            case '2':
                deleteMenu(&root, &longestWord);
                break;

            case '3':
                printf("Tree display:\n");
                displayTree(root, longestWord, "!!!");
                printf("Press any key to continue\n");
                getche();

                break;
        }

    } while (userInput != '4');


    return 0;
}
