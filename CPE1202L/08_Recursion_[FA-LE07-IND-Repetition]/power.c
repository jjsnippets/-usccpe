#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "functions.h"

void powerMenu(){

    char userInput;
    long int base;
    int power;

    do {

        printf("Power Option\n");
        printf("Enter base: ");
        scanf(" %ld", &base);
        printf("Enter power (positive integer): ");
        scanf(" %d", &power);
        printf("\n");

        printf("Iterative results: %ld\n", powerLoop(base, power));
        printf("Recursive results: %ld\n", powerCall(base, power));
        printf("\n");

        printf("Again [Y/N]?\n");
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput != 'n');
}

long int powerLoop(long int b, int e){

    long int result = 1;

    for (int i = 0; i < e; i++)
        result *= b;

    return result;
}

long int powerCall(long int b, int e){

    if (e < 1)
        return 1;
    else
        return powerCall(b, e - 1) * b;

}