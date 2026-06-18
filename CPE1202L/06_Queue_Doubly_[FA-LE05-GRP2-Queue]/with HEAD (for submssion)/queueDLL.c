#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queueDLL.h"

#define HEAD (*List)->queueHead
#define TAIL (*List)->queueTail

void enqueueMenu(QUEUESTRUCT** List)
{
    char again = '\0';

    do {

        NODE* toAdd = (NODE*)calloc(1, sizeof(NODE));

        if (toAdd == NULL)
        {
            printf("Memory allocation failed!");
            exit(1);
        };

        printf("\n\nENQUEUE MENU:\n");

        printf("\tInput First Name: ");
        scanf("%99[^\n]", toAdd->fn);
        fflush(stdin);

        printf("\n\tInput Middle Name: ");
        scanf("%99[^\n]", toAdd->mn);
        fflush(stdin);

        printf("\n\tInput Last Name: ");
        scanf("%99[^\n]", toAdd->ln);
        fflush(stdin);

        printf("\n\tInput Mobile No.: ");
        scanf("%99[^\n]", toAdd->pn);
        fflush(stdin);

        printf("\n\tInput Email Address: ");
        scanf("%99[^\n]", toAdd->ea);
        fflush(stdin);

        toAdd->next = NULL;
        toAdd->prev = NULL;

        enqueue(List, toAdd);

        printf("\n\n\tAgain [Y/N]? ");
        scanf(" %c", &again);
        again = toupper(again);
        fflush(stdin);

    } while (again != 'N');

    return;
}

void dequeueMenu(QUEUESTRUCT** List){

    if(!HEAD){
        printf("No elements to remove\n");
        printf("Press any key to continue\n");
        getche();
        return;
    }

    char userInput;
    char* separator = calloc(106, sizeof(char));
    memset(separator, '=', 105);

    do {

        NODE* toShow = dequeue(List);

        printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n", "Last name", "First name", "Middle name", "Phone number", "Email Address");
        printf("%s\n", separator);
        printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n\n", toShow->ln, toShow->fn, toShow->mn, toShow->pn, toShow->ea);

        free(toShow);

        printf("Successfully removed entry!\n\n");

        if(!HEAD){
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
