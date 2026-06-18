#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook-sll.h"

void changePrcs (NODE** start, int* size){

    char userInput;
    char* compare = calloc(100, sizeof(char));
    int inList = 0;

    NODE* currentNode;

    do {
        inList = 0;
        memset(compare, '\0', 100);
            //initializes variables

        printf("[L] Search by Last Name\n[N] Search by Mobile Number\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

        switch (userInput) {
            case 'l':
            case 'n':

                printf("Input %s: ", (userInput == 'l' ? "Last Name" : "Mobile Number"));
                fflush(stdin);
                scanf("%[^\n,]s", compare);
                printf("\n");

                // reimplementation from browse-sll.c
                for(int i = 0; i < *size; i++){
                    currentNode = (i == 0 ? *start : currentNode->next);
                    if (strcmp(compare, (userInput == 'l' ? currentNode->lname : currentNode->num) ) == 0){
                        inList = 1;
                        break;
                    }
                }

                // when not found, return to main
                if (!inList){
                    printf("%s not found!\n", (userInput == 'l' ? "Last Name" : "Mobile Number"));
                    printf("Press any key to continue\n");
                    fflush(stdin);
                    getche();
                    free(compare);
                    return;
                }

                break;

            default:
                    // when neither l or n, return to main
                free(compare);
                return;
        }

        displayTable(currentNode, 0);

        changeChoiceMenu();
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

        printf("Replace with: ");
        fflush(stdin);
        memset(compare, '\0', 100);
        scanf("%[^\n,]s", compare);

        // change individual field
        switch (userInput) {
        case 'l':
            strcpy(currentNode->lname, compare);
            break;

        case 'm':
            strcpy(currentNode->mname, compare);
            break;

        case 'f':
            strcpy(currentNode->fname, compare);
            break;

        case 'n':
            strcpy(currentNode->num, compare);
            break;

        case 'e':
            strcpy(currentNode->email, compare);
            break;
        }

        displayTable(currentNode, 0);

        saveToFile(start, size);
        printf("Again [Y/N]\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput != 'n');

    free(compare);
}

void changeChoiceMenu (){

    printf("Change What?\n");
    printf("[L] Last Name\n");
    printf("[M] Middle Name\n");
    printf("[F] First Name\n");
    printf("[N] Mobile Number\n");
    printf("[E] Email Address\n");

}
