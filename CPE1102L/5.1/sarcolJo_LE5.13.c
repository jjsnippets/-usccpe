/*
============================================================================
 FILE        : sarcolJo_LE5.13.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE 5.13 Problem Solver Menu
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/25/2023         Sarcol          made code in int main() and int quadraticSolver()

============================================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

int quadraticSolver();

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : presents a menu of possible calculations and solves based on user input
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main() {
    char userInput;
    do
    {
        do
        {
            //user selects from options presented
            printf("\nproceed to?\n[p]ower\n[f]actorial\n[r]oots of quadratic equation\n[q]uit program\nselect one option: ");
            do
            {
                userInput = tolower(getchar());
            }
            while (isspace(userInput) != 0); //do-while loop allows for white-space input not to count
        }
        while (userInput != 'p' &&  userInput != 'f' && userInput != 'r' && userInput != 'q');  //do-while loop only allows only (p, f, r, q) to proceed

        //resets relevant values needed to be reset
        int base, power, factorial, solution = 1;

        switch (userInput)
        {
            //if user selects [p]ower
            case 'p':
                //gets from user the value of base and power
                printf("\nEnter base: ");
                scanf("%d", &base);
                printf("Enter power: ");
                scanf("%d", &power);

                //calculates base^power 
                solution = pow(base, power);
                printf("%d^%d = %d\n", base, power, solution);           
                break;

            //if user selects [f]actorial
            case 'f':
                //gets from user the value of n from n!
                printf("\nEnter value of n: ");
                scanf("%d", &factorial);

                //calculates the value of n! using for loops
                for (int i = 1; i <= factorial; i++)
                    solution *= i;
                printf("%d! = %d\n", factorial, solution);
                break;
            
            //if user selects [r]oots. its own function for code tidyness since solving quadratics takes many lines of code
            case 'r':
                quadraticSolver();
                break;
        }
    }
    while (userInput != 'q'); //code exits only when user selects [q]uit

    return 0;
}



/*
============================================================================
 FUNCTION    : quadraticSolver()
 DESCRIPTION : displays the real-numbered root of the quadratic equation ax^2 + bx + c = 0
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int quadraticSolver()
{
    float a, b, c, discriminant, x1, x2;

    //gets from user the coefficients a, b, and c from ax^2 + bx + c = 0
    printf("\nEnter coefficient of x^2 term: ");
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
