#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stackSLL.h"

void pushMenu(NODE** head){

    char userInput;

    do{
        NODE* newNode = calloc(1, sizeof(NODE));

        // input menu
        printf("Input First Name: ");
        fflush(stdin);
        scanf("%99[^\n]s", newNode->fn);

        printf("Input Middle Name: ");
        fflush(stdin);
        scanf("%99[^\n]s", newNode->mn);

        printf("Input Last Name: ");
        fflush(stdin);
        scanf("%99[^\n]s", newNode->ln);

        printf("Input Mobile Number: ");
        fflush(stdin);
        scanf("%99[^\n]s", newNode->pn);

        printf("Input Email Address: ");
        fflush(stdin);
        scanf("%99[^\n]s", newNode->ea);
        printf("\n");

        push(head, newNode);
            // adds the newly created node at the top of the stack

        printf("Again [Y/N]?\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput != 'n');
}



void popMenu(NODE** head){

    if(!*head){
            // when size of stack is 0
        printf("No elements to remove\n");
        printf("Press any key to continue\n");
        getche();
        return;
    }

    char userInput;
    char* separator = calloc(106, sizeof(char));
    memset(separator, '=', 105);

    do{

        NODE* toShow = pop(head);
            // pops first node of stack

        // pop output
        printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n", "Last name", "First name", "Middle name", "Phone number", "Email Address");
        printf("%s\n", separator);
        printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n\n", toShow->ln, toShow->fn, toShow->mn, toShow->pn, toShow->ea);

        printf("Successfully removed entry!\n\n");

        if(!*head){
                // when stack size is 0
            printf("No more elements to remove\n");
            printf("Press any key to continue\n");
            getche();
            break;
        }

        printf("Again [Y/N]?\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput == 'y');

    free(separator);
}


