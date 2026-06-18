#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "functions.h"

void factorialMenu(){

    char userInput;
    long int num;

    do{
        printf("Factorial Option\n");
        printf("Input number: ");
        scanf(" %ld", &num);
        printf("\n");

        printf("Iterative results: %ld\n", factorialLoop(num));
        printf("Recursive results: %ld\n", factorialCall(num));
        printf("\n");

        printf("Again [Y/N]?\n");
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput != 'n');
}

long int factorialLoop(long int n){

    long int result = 1;

    while (n > 1)
        result *= n--;

    return result;
}

long int factorialCall(long int n){

    if (n < 1)
        return 1;
    else
        return factorialCall(n - 1) * n;

}