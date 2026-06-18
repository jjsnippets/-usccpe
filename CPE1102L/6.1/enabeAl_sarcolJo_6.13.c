/*
============================================================================
 FILE        : enabeAl_sarcolJo_LE6.13.c
 AUTHOR      : Albert Justin Joe Enabe, Joshua Sarcol
 DESCRIPTION : C code implementation of LE 6.13 Problem Solver Menu
 COPYRIGHT   : Albert Justin Joe Enabe, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/11/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

void displayMenu ();
int powerSolver (int base, int p);
int factorialSolver (int num);
int quadraticSolver (int a, int b, int c);
float x1, x2;

/*
============================================================================
 FUNCTION    : main()
 DESCRIPTION : presents a menu of possible calculations and solves based on user input
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
===========================================================================
*/

void main() {
    char userInput;

    do
    {
        do
        {
            //user selects from options presented
            displayMenu();
            do
            {
                userInput = tolower(getchar());
            }
            while (isspace(userInput) != 0); //do-while loop allows for white-space input not to count
        }
        while (userInput != 'p' &&  userInput != 'f' && userInput != 'r' && userInput != 'q');  //do-while loop only allows only (p, f, r, q) to proceed
        
        //resets relevant values needed to be reset
        int base, power, factorial, solution = 1;
        int a, b, c;

        switch (userInput)
        {
            //if user selects [p]ower
            case 'p':
                //gets from user the value of base and power
                printf("\nEnter base: ");
                scanf("%d", &base);
                printf("Enter power: ");
                scanf("%d", &power);

                //solves base^power 
                solution = powerSolver (base, power);
                printf("%d^%d = %d\n", base, power, solution);           
                break;

            //if user selects [f]actorial
            case 'f':
                //gets from user the value of n from n!
                printf("\nEnter value of n: ");
                scanf("%d", &factorial);

                //solves !n
                solution = factorialSolver(factorial);
                printf("%d! = %d\n", factorial, solution);
                break;
            
            //if user selects [r]oots. its own function for code tidyness since solving quadratics takes many lines of code
            case 'r':
                //gets from user the coefficients a, b, and c from ax^2 + bx + c = 0
                printf("\nEnter coefficient of x^2 term: ");
                scanf("%d", &a);
                printf("Enter coefficient of x term: ");
                scanf("%d", &b);
                printf("Enter constant term: ");
                scanf("%d", &c);

                //solves the associated quadratic equation
                solution = quadraticSolver(a, b, c);

                switch(solution)
                {
                    case 0:
                        printf("No solutions found.\n");
                        break;

                    case 1:
                        printf("One solution found: %.2f\n", x1);
                        break;

                    case 2:
                        printf("Two solutions found: %.2f, %.2f\n", x1, x2);
                        break;
                }


                break;
        }
    }
    while (userInput != 'q'); //code exits only when user selects [q]uit
}

/*
============================================================================
 FUNCTION    : displayMenu()
 DESCRIPTION : prints the menu that the user sees
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
===========================================================================
*/

void displayMenu() {
    printf("\nproceed to?\n[p]ower\n[f]actorial\n[r]oots of quadratic equation\n[q]uit program\nselect one option: ");
}

/*
============================================================================
 FUNCTION    : powerSolver (base, p)
 DESCRIPTION : calculates base^p
 ARGUMENTS   :  int base: the number to be multiplied
                int p: the number of times the number is to be multiplied by
 RETURNS     : int: result of the operation base ^ p
===========================================================================
*/

int powerSolver (int base, int p){
    return pow(base, p);
}

/*
============================================================================
 FUNCTION    : factorialSolver (num)
 DESCRIPTION : calculates !num using loops
 ARGUMENTS   : int num: the number to be multiplied
 RETURNS     : int result: result of the operation !num
===========================================================================
*/

int factorialSolver (int num){
    int result = 1;

    //calculates the value of n! using for loops
    for (int i = 1; i <= num; i++)
        result *= i;
    return result;
}

/*
============================================================================
 FUNCTION    : quadraticSolver(a, b, c)
 DESCRIPTION : displays the real-numbered root of the quadratic equation ax^2 + bx + c = 0
 ARGUMENTS   : float a, b, c: coefficients a, b, and c from ax^2 + bx + c = 0
 RETURNS     : int: returns number of solutions
===========================================================================
*/


int quadraticSolver(int a, int b, int c)
{
    float discriminant;

    //calculates discriminant
    discriminant = b * b - 4 * a * c;

    if (a == 0 && b == 0) //degenerate case: c = 0
        return 0;
    else if (a == 0) //degenerate case: bx + c = 0
    {
        x1 = -1 * c / b;
        return 1;
    }
    else if (discriminant < 0) //no solutions in the reals: sqrt(negative)
        return 0;
    else
    {
        x1 = (-1 * b + sqrt(discriminant)) / (2 * a);
        x2 = (-1 * b - sqrt(discriminant)) / (2 * a);
        if (x1 == x2) //special case: solution x1 is of multiplicity 2
            return 1;
        else
            return 2;
    }

    return 0;
}