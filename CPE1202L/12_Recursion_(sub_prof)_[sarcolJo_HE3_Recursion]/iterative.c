/*
======================================================
FILE        : iterative.c
AUTHOR      : Sarcol, Joshua
DESCRIPTION : implementation file for all iterative functions
COPYRIGHT   : 2024-03-18

REVISION HISTORY
Date                By              Description
2024-03-18          sarcol          made file

======================================================
*/

#include "iterative.h"

/*
======================================================
FUNCTION    : iterFactorial
DESCRIPTION : loop implementation of n! 1, 2, 6, 24, 120, ...
ARGUMENTS
    int n - n in n!
RETURNS
    int - effectively n!

======================================================
*/
int iterFactorial(int n){

    int result = 1;


    for (int i = 1; i <= n; i++)
        result *= i;

    return result;

}

/*
======================================================
FUNCTION    : iterFibonacci
DESCRIPTION : loop implementation of generating fibonacci numbers 1, 1, 2, 3, 5, ...
ARGUMENTS
    int n - nth fibonacci number to determine
RETURNS
    int - nth fibonacci number a_n where a_1 = 1 and a_2 = 1

======================================================
*/
int iterFibonacci(int n){

    int result = 0;
    int a0 = 1, a1 = 0;

    for (int i = 0; i < n; i++){
        result = a0 + a1;
        a0 = a1;
        a1 = result;
    }

    return result;
}

/*
======================================================
FUNCTION    : iterSum
DESCRIPTION : loop implementation of generating triangular numbers 1, 3, 6, 10, 15, ...
ARGUMENTS
    int n - nth trangular number to determine
RETURNS
    int - nth trangular number a_n

======================================================
*/
int iterSum(int n){
    int result = 0;

    for (int i = 1; i <= n; i++)
        result += i;

    return result;
}
