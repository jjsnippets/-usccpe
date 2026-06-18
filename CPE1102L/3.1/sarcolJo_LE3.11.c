/*
============================================================================
 FILE        : sarcolJo_LE3.11.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : programming task for LE3.11: Weekly Pay
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
 DESCRIPTION : calculates and prints weekly pay from user's yearly pay
 ARGUMENTS   : --no passed variables
 RETURNS     : 0 - integer constant
===========================================================================
*/

int main ()
{
    //gets yearly pay of user
    float yearlyPay;
    printf("Enter your yearly pay: ");
    scanf("%f", &yearlyPay);

    //calculates weekly pay from yearly pay: 1 year = 52 weeks
    float weeklyPay = yearlyPay/52;
    printf("Your weekly pay is %.2f", weeklyPay);

    return 0;
}
