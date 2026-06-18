#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "queueDLL.h"

void main(){

    NODE* head = NULL;
    char userInput;

    while (1){
        // main menu
        system("cls");
        printf("[1] Enqueue\n");
        printf("[2] Dequeue\n");
        printf("[3] Show\n");
        printf("[4] Exit\n");
        fflush(stdin);
        userInput = getche();
        printf("\n\n");

        if (userInput == '4') break;

        switch (userInput){
            case '1':;
                enqueueMenu(&head);
                break;

            case '2':;
                dequeueMenu(&head);
                break;

            case '3':;
                showAll(&head);
                break;
        }
    }

}



