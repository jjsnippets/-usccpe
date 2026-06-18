/*
============================================================================
 FILE        : sarcolJo_ME.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of Midterm Exam B | CO2
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By:             Description:
 10/18/2023         Sarcol          made code in void main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : int main ()
 DESCRIPTION : determines from the series of inputs from user the largest and smallest values and prints them when the user types -99
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
============================================================================
*/

int main (){

    //initializes the variables for worst case scenarios (ie. all numbers are negative numbers etc)
    int current, largest = -10000, smallest = 10000;

    //stops when user inputs -99
    while (current != -99) {

        //asks user for number
        printf("user input: ");
        scanf("%d", &current);

        //when the recent number is larger than the currently largest value, it becomes the new largest number
        (current > largest) ? largest = current : 0;

        //when the recent number is smaller than the currently smalles value, it becomes the new smallest number
        //exeption is when user inputs -99 itself. in this case, no extra logic should be performed
        (current < smallest && current != -99) ? smallest = current : 0;
    }

    //prints the largest and smallest values (optimized in 1 line)
    printf("largest: %d\nsmallest: %d", largest, smallest);

    return 0;
}







