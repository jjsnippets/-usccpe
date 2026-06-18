/*
============================================================================
 FILE        : sarcolJo_LE5.11.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.11 Average of Even Numbers and Product of Odd Numbers
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By:             Description:
 09/25/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : grabs 10 numbers from user and calculates the average from the evens and product from the odds
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main() {
    long long int countTotal = 1, currentNumber = 0, runningProductOdd = 1;
    float runningTotalEven = 0, countEven = 0, averageEven = 0;

    do {
        //grabs nth number from user
        printf("N%d: ", countTotal);
        scanf("%d", &currentNumber);
        if (currentNumber % 2 == 0) //for even numbers
        {
            runningTotalEven += currentNumber; //adds to running total
            countEven++; //counts how many even numbers
        }
        else //for odd numbers
            runningProductOdd *= currentNumber; //multiplies to running total
        countTotal++;
    } while (countTotal <= 10);

    //special case: when number of even numbers inputted is 0, then average is 0
    (countEven != 0) ? (averageEven = runningTotalEven / countEven) : (averageEven = 0);

    //special case: when number of odd numbers inputted is 0; then product is 0
    (countEven == 10) ? (runningProductOdd = 0) : 0 ;

    //prints results
    printf("\nAverage of all even numbers: %.2f", averageEven);
    printf("\nProduct of all odd numbers: %lld", runningProductOdd);

    return 0;
}
