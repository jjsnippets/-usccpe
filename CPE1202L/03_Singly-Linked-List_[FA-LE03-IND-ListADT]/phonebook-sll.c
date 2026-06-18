#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook-sll.h"

void main(){

    NODE* startPBook;

    int currSizePBook = 0;
        // implementation with a separate variable that keeps track of the number of nodes in the linked list
    char userInput;

    loadFromFile(&startPBook, &currSizePBook);

    while (1){

        mainMenuDisp();

        fflush(stdin);
        userInput = tolower(getche());

        if (userInput == 'e')
            break;

        printf("\n\n");

        switch (userInput){

            case 'a':
                appendPrcs(&startPBook, &currSizePBook);
                break;

            case 'b':
                browsePrcs(&startPBook, &currSizePBook);
                break;

            case 'c':
                changePrcs(&startPBook, &currSizePBook);
                break;

            case 'd':
                deletePrcs(&startPBook, &currSizePBook);
                break;

        }

    }

    saveToFile(&startPBook, &currSizePBook);
    free(startPBook);

}


void mainMenuDisp() {
    system("cls");
    printf("[A]ppend\n");
    printf("[B]rowse\n");
    printf("[C]hange\n");
    printf("[D]elete\n");
    printf("[E]xit\n");
}
