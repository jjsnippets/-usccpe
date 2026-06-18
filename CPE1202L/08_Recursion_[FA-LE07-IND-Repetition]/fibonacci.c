#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "functions.h"

void fibonnaciMenu(){

    char userInput;
    int index;

    do{
        printf("Fibonacci Option\n");
        printf("Input number (starts at a_0 = 0, a_1 = 1): ");
        scanf(" %d", &index);
        printf("\n");

        printf("Iterative results: %d\n", fibonnaciLoop(index));
        printf("Recursive results: %d\n", fibonnaciCall(index));
        printf("\n");

        printf("Again [Y/N]?\n");
        userInput = tolower(getche());
        printf("\n\n");

    } while (userInput != 'n');
}

int fibonnaciLoop(int a){

    if (a == 0) return 0;
    if (a == 1) return 1;

    int* set = calloc(a + 1, sizeof(int));
    set[0] = 0;
    set[1] = 1;

    for (int i = 2; i <= a; i++)
        set[i] = set[i - 1] + set[i - 2];

    return set[a];
}

int fibonnaciCall(int a){

    if (a == 0)
        return 0;
    else if (a == 1)
        return 1;
    else
        return fibonnaciCall(a - 1) + fibonnaciCall(a - 2);
}