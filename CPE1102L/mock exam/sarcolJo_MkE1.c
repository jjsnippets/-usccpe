/*
============================================================================
 FILE        : sarcolJo_MkE1.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of Mock Exam problem
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By:             Description:
 10/11/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : int main ()
 DESCRIPTION : reverses the integer input of the user with space as a separator
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
============================================================================
*/

int main () {

    //takes the integer that is inputted by the user
    int integer;
    scanf("%d", &integer);

    //loops until integer has a value of 0
    while(integer){

        //prints the one's digit of the current integer
        printf("%d ", integer % 10);

        //essentially shifts the number to the right, removing the digit shifted to the tenth's place
        integer /= 10;
    }

}
