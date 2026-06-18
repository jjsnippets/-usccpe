#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "functions.h"

#define BOLD_TEXT printf("\e[1m")
#define COLOR_RED printf("\e[91m")
#define TEXT_RESET printf("\e[m")

void main (){

    char userInput;

    do {

        system("cls");
        COLOR_RED;
        printf("Main menu:\n");
        TEXT_RESET;
        printf("[1] Power\n");
        printf("[2] Factorial\n");
        printf("[3] Fibonacci\n");
        printf("[4] Exit\n");

        fflush(stdin);
        userInput = getche();
        printf("\n\n");

        switch (userInput)
        {
            case '1':
                powerMenu();
                break;
            
            case '2':
                factorialMenu();
                break;
            
            case '3':
                fibonnaciMenu();
                break;
        }

    } while (userInput != '4');
}