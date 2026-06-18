#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook-sll.h"

void deletePrcs (NODE** start, int* size){

    char userInput;
    char* compare = calloc(100, sizeof(char));
    int inList = 0;

    printf("[L] Search by Last Name\n[N] Search by Mobile Number\n");
    fflush(stdin);
    userInput = tolower(getche());
    printf("\n\n");

    NODE* previousNode, * removeNode;
        // removeNode also acts as the currentNode

    switch (userInput) {
        case 'l':
        case 'n':

            printf("Input %s: ", (userInput == 'l' ? "Last Name" : "Mobile Number"));
            fflush(stdin);
            scanf("%[^\n,]s", compare);
            printf("\n");

            // special case where there is only one node
            removeNode = *start;
            if (strcmp(compare, (userInput == 'l' ? removeNode->lname : removeNode->num) ) == 0)
                inList = 1;

            // for loop that deals with the rest of the nodes in the linked list
            // skips when the first element is already a match
            for(int i = 0; i < (*size - 1) && !inList; i++){
                previousNode = (i == 0 ? *start : previousNode->next);
                    // initializes to start, then moves along the linked list afterwards
                removeNode = previousNode->next;
                if (strcmp(compare, (userInput == 'l' ? removeNode->lname : removeNode->num) ) == 0){
                    inList = 1;
                    break;
                }
            }

            // if not found, return to main
            if (!inList){
                printf("%s not found!\n", (userInput == 'l' ? "Last Name" : "Mobile Number"));
                printf("Press any key to continue\n");
                fflush(stdin);
                getche();
                free(compare);
                return;
            }

            if (removeNode == *start) {
                    // special case where the match is the first node
                *start = removeNode->next;
                free(removeNode);
            } else {
                    // otherwise
                previousNode->next = removeNode->next;
                free(removeNode);
            }

        break;

        default:
            free(compare);
            return;
    }

    (*size)--;

    saveToFile(start, size);
    printf("Entry Successfully deleted!\n");
    printf("Press any key to continue\n");
    fflush(stdin);
    getche();

    free(compare);
    return;
}
