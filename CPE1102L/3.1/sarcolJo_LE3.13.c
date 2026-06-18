/*
============================================================================
 FILE        : sarcolJo_LE3.13.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : programming task for LE3.13: Tuition Fee
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/15/2023         Sarcol          made code in int main()

============================================================================
*/

//uses defined constants for easy changing of values
#define REGISTRATION 450
#define UNITPRICE 450
#define PENALTYUNITS 2260
#define PENALTYFRACTION 12

#include <stdio.h>

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : gives a printout of the user's school fees for a year
 ARGUMENTS   : --no passed variables
 RETURNS     : 0 - integer constant
===========================================================================
*/

int main ()
{
    //grabs relevant values from user. no input checking; assumes user always types integer
    float firstUnits, secondUnits;
    printf("1st Semester Number of Units\t: ");
    scanf("%f", &firstUnits);
    printf("2nd Semester Number of Units\t: ");
    scanf("%f", &secondUnits);

    //calculates the first semester fee
    float firstFee = REGISTRATION + UNITPRICE * firstUnits + PENALTYUNITS * (firstUnits / PENALTYFRACTION);
    printf("1st Semester Tuition Fee\t: %7.2f\n", firstFee);

    //calculates the second semester fee
    float secondFee = REGISTRATION + UNITPRICE * secondUnits + PENALTYUNITS * (secondUnits / PENALTYFRACTION);
    printf("2nd Semester Tuition Fee\t: %7.2f\n", secondFee);

    //sums the fees together
    float feeTotal = firstFee + secondFee;
    printf("Total Tuition Fee\t\t: %7.2f", feeTotal);

    return 0;
}
