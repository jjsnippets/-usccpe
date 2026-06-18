/*
======================================================
FILE        : recursive.c
AUTHOR      : Sarcol, Joshua
DESCRIPTION : implementation file for all recursive functions
COPYRIGHT   : 2024-03-18

REVISION HISTORY
Date                By              Description
2024-03-18          sarcol          made file

======================================================
*/

#include "recursive.h"

/*
======================================================
FUNCTION    : recurFactorial
DESCRIPTION : recursive implementation of n! 1, 2, 6, 24, 120, ...
ARGUMENTS
    int n - n in n!
RETURNS
    int - effectively n!

======================================================
*/
int recurFactorial(int n){
    int result = n;

    if (n == 1)
        result = 1;
    else
        result *= recurFactorial(n - 1);

    return result;
}

/*
======================================================
FUNCTION    : recurFibonacci
DESCRIPTION : recusive implementation of generating fibonacci numbers 1, 1, 2, 3, 5, ...
ARGUMENTS
    int n - nth fibonacci number to determine
RETURNS
    int - nth fibonacci number a_n where a_1 = 1 and a_2 = 1

======================================================
*/
int recurFibonacci(int n){
    int result;

    if (n < 3)
        result = 1;
    else
        result = recurFibonacci(n - 1) + recurFibonacci(n - 2);

    return result;
}

/*
======================================================
FUNCTION    : recurSum
DESCRIPTION : recursive implementation of generating triangular numbers 1, 3, 6, 10, 15, ...
ARGUMENTS
    int n - nth trangular number to determine
RETURNS
    int - nth trangular number a_n

======================================================
*/
int recurSum(int n){
    int result = n;

    if (n == 1)
        result = 1;
    else
        result += recurSum(n - 1);

    return result;
}
