/*
======================================================
FILE        : main.c
AUTHOR      : Sarcol, Joshua
DESCRIPTION : main file, contains all I/O for program
COPYRIGHT   : 2024-03-18

REVISION HISTORY
Date                By              Description
2024-03-18          sarcol          made file

======================================================
*/

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "iterative.h"
#include "recursive.h"

// special characters, ansi escape code to display text in color
#define GREEN "\e[32m"
#define BLUE "\e[94m"
#define RESET "\e[m"

/*
======================================================
FUNCTION    : main
DESCRIPTION : from user input (x), list factorial, fibonacci, and sum series a_1, a_2, ..., a_n
ARGUMENTS

RETURNS
    int - returns 0, indicates success

======================================================
*/
int main(){

    int userInput;
    char colorMode;

    // asks user if tui is in color or not
    system("cls"); // clears screen to properly show color, if at all
    printf("%sIs this text color green?%s\n", GREEN, RESET);
    printf("[Y] Yes (uses special characters)\n");
    printf("[N] No (maximum compatibility)\n");
    colorMode = tolower(getche());
    system("cls");

    // asks user for value of n
    printf("Enter value of n: ");
    scanf(" %d", &userInput);
    printf("\n");

    // Factorial series
    printf("Factorial series using %snon-recursive%s function.\n\t", colorMode == 'y' ? GREEN : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", iterFactorial(i));
    printf("\b\n");

    printf("Factorial series using %srecursive%s function.\n\t", colorMode == 'y' ? BLUE : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", recurFactorial(i));
    printf("\b\n\n");

    // Fibonacci series
    printf("Fibonacci series using %snon-recursive%s function.\n\t", colorMode == 'y' ? GREEN : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", iterFibonacci(i));
    printf("\b\n");

    printf("Fibonacci series using %srecursive%s function.\n\t", colorMode == 'y' ? BLUE : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", recurFibonacci(i));
    printf("\b\n\n");

    // Sum series (Triangular numbers)
    printf("Sum series using %snon-recursive%s function.\n\t", colorMode == 'y' ? GREEN : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", iterSum(i));
    printf("\b\n");

    printf("Sum series using %srecursive%s function.\n\t", colorMode == 'y' ? BLUE : "", colorMode == 'y' ? RESET : "");
        for(int i = 1; i <= userInput; i++)
            printf("%d ", recurSum(i));
    printf("\b\n");

    return 0;
}
