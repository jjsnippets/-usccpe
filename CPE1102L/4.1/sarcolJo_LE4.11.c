/*
============================================================================
 FILE        : sarcolJo_LE4.11.c
 AUTHOR      : Sarcol, Joshua
 DESCRIPTION : C code implementation of LE4_11: Vowel and Consonant
 COPYRIGHT   : Sarcol, Joshua
 REVISION HISTORY
 Date:              By: 	        Description:
 09/20/2023         Sarcol          made code in int main()

============================================================================
*/

#include <stdio.h>

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : reads user input and prints to user if it is a vowel, consonant or neither
 ARGUMENTS   : void - no passed variables
 RETURNS     : int: 0 - integer constant
===========================================================================
*/

int main()
{
    char letter;

    //gets input from user
    printf("Enter a letter: ");
    scanf("%c", &letter);

    switch(letter)
    {
        //all cases where user input is a vowel
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'i':
        case 'I':
        case 'o':
        case 'O':
        case 'u':
        case 'U':
            printf("VOWEL!");
            break;

        //all cases where user input is a consonant
        case 'b':
        case 'B':
        case 'c':
        case 'C':
        case 'd':
        case 'D':
        case 'f':
        case 'F':
        case 'g':
        case 'G':
        case 'h':
        case 'H':
        case 'j':
        case 'J':
        case 'k':
        case 'K':
        case 'l':
        case 'L':
        case 'm':
        case 'M':
        case 'n':
        case 'N':
        case 'p':
        case 'P':
        case 'q':
        case 'Q':
        case 'r':
        case 'R':
        case 's':
        case 'S':
        case 't':
        case 'T':
        case 'v':
        case 'V':
        case 'w':
        case 'W':
        case 'x':
        case 'X':
        case 'y':
        case 'Y':
        case 'z':
        case 'Z':
            printf("CONSONANT!");
            break;

        //all cases where user input is not a letter
        default:
            printf("INVALID INPUT!");
            break;
    }
    return 0;
}
