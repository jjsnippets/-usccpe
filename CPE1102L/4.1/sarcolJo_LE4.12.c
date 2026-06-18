/*
============================================================================
 FILE        : sarcolJo_LE4.12.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE4_12: Quadratic Equation
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/20/2023         Sarcol          made code in int main()

============================================================================
*/

#include<stdio.h>
#include<math.h>

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : displays the real-numbered root of the quadratic equation ax^2 + bx + c = 0
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main()
{
    float a, b, c, discriminant, x1, x2;

    //gets from user the coefficients a, b, and c from ax^2 + bx + c = 0
    printf("Enter coefficient of x^2 term: ");
    scanf("%f", &a);
    printf("Enter coefficient of x term: ");
    scanf("%f", &b);
    printf("Enter constant term: ");
    scanf("%f", &c);

    //calculates discriminant
    discriminant = b * b - 4 * a * c;

    if (a == b && b == 0) //degenerate case: c = 0
        printf("No solutions found.\n");
    else if (a == 0) //degenerate case: bx + c = 0
    {
        x1 = -1 * c / b;
        printf("One solution found: %.2f\n", x1);
    }
    else if (discriminant < 0) //no solutions in the reals: sqrt(negative)
        printf("No real-numbered solutions found.\n");
    else
    {
        x1 = (-1 * b + sqrt(discriminant)) / (2 * a);
        x2 = (-1 * b - sqrt(discriminant)) / (2 * a);
        if (x1 == x2) //special case: solution x1 is of multiplicity 2
            printf("One solution found: %.2f\n", x1);
        else
            printf("Two solutions found: %.2f, %.2f\n", x1, x2);
    }
    return 0;
}

