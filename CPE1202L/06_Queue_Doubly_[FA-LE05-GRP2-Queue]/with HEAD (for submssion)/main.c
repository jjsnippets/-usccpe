#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "queueDLL.h"

int main(){

    QUEUESTRUCT* List = calloc(1, sizeof(QUEUESTRUCT));
    char userInput;

    while (1){
        // main menu
        system("cls");
        printf("QUEUE ADT: DLL MENU\n");
        printf("\t[1] Enqueue\n");
        printf("\t[2] Dequeue\n");
        printf("\t[3] Show\n");
        printf("\t[4] Exit\n");
        fflush(stdin);
        userInput = getche();
        printf("\n\n");

        if (userInput == '4') break;

        switch (userInput){
            case '1':;
                enqueueMenu(&List);
                break;

            case '2':;
                dequeueMenu(&List);
                break;

            case '3':;
                showAll(&List);
                break;
        }
    }

}



