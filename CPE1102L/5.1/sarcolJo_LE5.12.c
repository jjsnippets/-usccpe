/*
============================================================================
 FILE        : sarcolJo_LE5.12.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.12 Passcode Lock
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/25/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : asks the user for the input password before adding 2 numbers
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main() {
    int setPasscode = 0, attempts = 0, userPasscode, number1, number2, sum;

    //password creation step
    printf("Set your password: ");
    scanf("%d", &setPasscode);
    system("cls");


    do {
        //asks the user the password before adding
        printf("\nEnter password before continuing: ");
        scanf("%d", &userPasscode);
        attempts++;
        if (setPasscode == userPasscode) //for correct password
        {
            printf("\nACCESS GRANTED!");
            break;
        }
        else if (attempts == 3) //user reached maximum attempts
            printf("\nACCESS DENIED");
        else //retry entry of password
            printf("\nWrong password! %d attempt(s) remaining", 3 - attempts);
    } while (attempts < 3);

    return 0;
}