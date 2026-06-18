/*
============================================================================
 FILE        : cardenasRo_sarcolJo_LE8.11.c
 AUTHOR      : Roy Lorenz Cardenas, Joshua Sarcol
 DESCRIPTION : programming task for LE 8.11 Days of the Week
 COPYRIGHT   : Roy Lorenz Cardenas, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/25/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>
#include <conio.h>

char* days(int n);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines the day of the week from the user input
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main(){
    int input;

    //gets from user the day of the week
    printf("Enter day: ");
    input = getche() - '0';
    printf("\t");

    //prints the name of the day of the week
    printf("Day of the week: %s", days(input));
}

/*
============================================================================
 FUNCTION    : days (n)
 DESCRIPTION : contains all the names of the week
 ARGUMENTS   : int n - the day of the week
 RETURNS     : char *name[] - the pointer to the name of the week
============================================================================
*/

char* days(int n){
    //contains the names of the days of the week
    char* name[8][10] = {
        {"Monday"},
        {"Tuesday"},
        {"Wednesday"},
        {"Thursday"},
        {"Friday"},
        {"Saturday"},
        {"Sunday"},
        {"INVALID"}
    };

    if (n > 0 && n < 8) //in between 1 to 7
        return *name[n - 1];
    else //everything else = INVALID
        return *name[7];

}