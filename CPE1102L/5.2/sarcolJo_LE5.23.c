/*
============================================================================
 FILE        : sarcolJo_LE5.23.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.23 Fibonacci Series
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By:             Description:
 10/02/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : lists the first N fibonacci numbers
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
============================================================================
*/

int main(){
    int terms;

    //gets from user number of terms to print
    printf("Enter limit: ");
    scanf("%d", &terms);

    //formatting
    printf("\nFibonacci sequence: ");

    //for loop implementation of fibbonaci sequence
    for(int i = 1, n = 1, m = 0, o = 0; i <= terms; i++)
    {
        printf("%d ", n);
        o = m;
        m = n;
        n = m + o;
    }

    return 0;
}