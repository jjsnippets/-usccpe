/*
============================================================================
 FILE        : enabeAl_sarcolJo_LE6.11.c
 AUTHOR      : Albert Justin Joe Enabe, Joshua Sarcol
 DESCRIPTION : programming task for LE6.11: Add Digits
 COPYRIGHT   : Albert Justin Joe Enabe, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/11/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>

int extractFirstLSD (int num);
int extractSecondLSD (int num);
int sumDigits (int x, int y);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : sums the ones and tens digit of a number
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main ()
{
    //grabs number from user. no input checking; assumes user always types integer
    int originalNumber;
    printf("Enter a number\t: ");
    scanf("%d", &originalNumber);

    //grabs the ones digit of the number
    int onesPlace = extractFirstLSD (originalNumber);

    //grabs the tens digit of the number
    int tensPlace = extractSecondLSD (originalNumber);

    //prints the sum of the ones and tens digit
    int sum = sumDigits (onesPlace, tensPlace);
    printf("Sum\t\t: %d + %d = %d", tensPlace, onesPlace, sum);
}

/*
============================================================================
 FUNCTION    : extractFirstLSD (num)
 DESCRIPTION : grabs the ones digit of a number
 ARGUMENTS   : int num: the number to which the ones place is taken
 RETURNS     : int: ones place digit
============================================================================
*/

int extractFirstLSD (int num){
    return num % 10;
}

/*
============================================================================
 FUNCTION    : extractSecondLSD (num)
 DESCRIPTION : grabs the tens digit of a number
 ARGUMENTS   : int num: the number to which the tens place is taken
 RETURNS     : int: tens place digit
============================================================================
*/

int extractSecondLSD (int num){
    return (num / 10) % 10;
}

/*
============================================================================
 FUNCTION    : sumDigits (x, y)
 DESCRIPTION : sums two numbers together
 ARGUMENTS   : int x, int y: the numbers to be added
 RETURNS     : int: result of the operation x = y
============================================================================
*/

int sumDigits (int x, int y){
    return x + y;
}