/*
============================================================================
 FILE        : sarcolJo_LE5.21.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.21 Multiplication Table
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
 DESCRIPTION : generates a n-by-m multiplication table, where the top left corner is 1 x 1 = 1
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
============================================================================
*/

int main(){
    int column, row;

    //gets from user number of columns and rows for the multiplication table
    printf("Number of columns: ");
    scanf("%d", &column);
    printf("Number of rows: ");
    scanf("%d", &row);

    //formatting for the very first row
    printf("\t");
    for (int i = 1; i <= column; i++)
        printf("%d\t", i);
    printf("\n");

    //generates the rest of the multiplication table values
    for (int i = 1; i <= row; i++)
    {
        for (int j = 0; j <= column; j++)
            if (j == 0) //formats the first entry of the row
                printf("%d\t", i);
            else //generates the cell value i*j
                printf("%d\t", i*j);
        printf("\n");
    }

    return 0;
}
