#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

void main() {
    char userInput1, userInput2, wordIndex;
    float num1, num2, result;
    char* words[4] = {
        "sum",
        "subtraction",
        "product",
        "quotient"
    };

    while (1) {
        printf("CALCULATOR MENU\n");
        printf("[A]ddition\n");
        printf("[S]ubtraction\n");
        printf("[M]ultiplication\n");
        printf("[D]ivision\n");
        printf("[E]xit\n\n");

        userInput1 = tolower(getche());

        if (userInput1 == 'e')
            break;

        do {
            printf("\n\nEnter number 1: ");
            scanf("%f", &num1);

            printf("Enter number 2: ");
            scanf("%f", &num2);

            switch (userInput1){
                case 'a':
                    result = toAdd(num1, num2);
                    wordIndex = 0;
                    break;

                case 's':
                    result = toSub(num1, num2);
                    wordIndex = 1;
                    break;

                case 'm':
                    result = toMul(num1, num2);
                    wordIndex = 2;
                    break;

                case 'd':
                    result = toDiv(num1, num2);
                    wordIndex = 3;
                    break;

                default:
                    break;
            };

            printf("The %s of %.2f and %.2f is %.2f\n", words[wordIndex], num1, num2, result);
            printf("Try another calculation?\n[Y]es\n[N]o\n\n");

            userInput2 = tolower(getche());

        } while (userInput2 != 'n');

        system("cls");
    }
}