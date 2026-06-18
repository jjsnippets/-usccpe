#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "stackSLL.h"

void main(){
    NODE* head = NULL;
    char userInput;

    // initialization for debug purposes; provides stack size of 3
    // NODE h3 = {"fn3", "md3", "ln3", "pn3", "ea3", NULL};
    // NODE h2 = {"fn2", "md2", "ln2", "pn2", "ea2", &h3};
    // NODE h1 = {"fn1", "md1", "ln1", "pn1", "ea1", &h2};
    // head = &h1;

    while (1){
        // main menu
        system("cls");
        printf("[1] Push\n");
        printf("[2] Pop\n");
        printf("[3] Show\n");
        printf("[4] Exit\n");
        fflush(stdin);
        userInput = getche();
        printf("\n\n");

        if (userInput == '4') break;

        switch (userInput){
            case '1':;
                pushMenu(&head);
                break;

            case '2':;
                popMenu(&head);
                break;

            case '3':;
                showAll(&head);
                break;
        }
    }
}

