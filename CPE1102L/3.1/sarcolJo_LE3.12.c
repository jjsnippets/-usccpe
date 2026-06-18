/*
============================================================================
 FILE        : sarcolJo_LE3.12.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : programming task for LE3.12: Add Digits
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/15/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : sums the ones and tens digit of a number
 ARGUMENTS   : --no passed variables
 RETURNS     : 0 - integer constant
===========================================================================
*/

int main ()
{
    //grabs number from user. no input checking; assumes user always types integer
    int originalNumber;
    printf("Enter a number\t: ");
    scanf("%d", &originalNumber);

    //grabs the ones digit of the number
    int onesPlace = originalNumber % 10;

    //grabs the tens digit of the number
    int tensPlace = (originalNumber - onesPlace) / 10 % 10;

    //prints the sum of the ones and tens digit
    int sum = onesPlace + tensPlace;
    printf("Sum\t\t: %d + %d = %d", tensPlace, onesPlace, sum);

    return 0;
}
