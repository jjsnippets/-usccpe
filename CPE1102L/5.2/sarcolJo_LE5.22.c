/*
============================================================================
 FILE        : sarcolJo_LE5.22.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.22 Pyramid
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By:             Description:
 10/02/2023         Sarcol          made code in int main()
 10/07/2023         Sarcol          optimized the for loop

============================================================================
*/

#include <stdio.h>
#include <math.h>

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : generates a pyramid of numbers of N layers
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
============================================================================
*/

int main(){
    int pyramidHeight;

    //gets from user height of pyramid
    printf("Enter a value for N: ");
    scanf("%d", &pyramidHeight);

    for (int i = 1; i <= pyramidHeight; i++) //i indicates the row index
    {
        for (int j = -1 * (pyramidHeight - 1); j <= pyramidHeight; j++) //j indicates the column index where center value is 0
            if (i - abs(j)> 0) //prints a number based on the row and column index
                printf("%d", i - abs(j));
            else
                printf(" ");
        printf("\n");
    }

    return 0;
}
