/*
============================================================================
 FILE        : sarcolJo_LE4.13.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE4_13: Student’s Final Grade
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/20/2023         Sarcol          made code in int main()

============================================================================
*/

#include<stdio.h>
#include<stdlib.h>

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : calculates the students final grade; 50 and above is marked as passed
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main()
{
    float first, second, third, fourth, average;
    int bound1st = 0, bound2nd = 0, bound3rd = 0, bound4th = 0;

    //gets 1st mark from user and check if its between 0 - 100
    printf("1st Mark : ");
    scanf("%f", &first);
    (first >= 0 && first <= 100) ? bound1st = 1 : 0;

    //gets 2nd mark from user and check if its between 0 - 100
    printf("2nd Mark : ");
    scanf("%f", &second);
    (second >= 0 && second <= 100) ? bound2nd = 1 : 0;

    //gets 3rd mark from user and check if its between 0 - 100
    printf("3rd Mark : ");
    scanf("%f", &third);
    (third >= 0 && third <= 100) ? bound3rd = 1 : 0;

    //gets 4th mark from userand check if its between 0 - 100
    printf("4th Mark : ");
    scanf("%f", &fourth);
    (fourth >= 0 && fourth <= 100) ? bound4th = 1 : 0;

    system("cls");
    printf("1st Mark : %.2f2\t2nd Mark : %.2f\t3rd Mark : %.2f\t4th Mark : %.2f\n", first, second, third, fourth);

    //checks if all 4 marks are between 0 - 100
    if (bound1st + bound2nd + bound3rd + bound4th == 4)
    {
        average = (first + second + third + fourth) / 4;    //calculates average
        printf("FINAL GRADE: %.2f\t", average);
        //analyzes average if 'pass' (50 and above) or 'fail' (49 and below)
        if (average >= 50)
            printf("REMARKS : PASSED");
        else
            printf("REMARKS : FAILED");
    }
    else
        printf("INVALID INPUT!");

    return 0;
}
