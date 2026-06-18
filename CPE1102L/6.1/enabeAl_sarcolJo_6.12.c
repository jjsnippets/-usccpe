/*
============================================================================
 FILE        : enabeAl_sarcolJo_LE6.12.c
 AUTHOR      : Albert Justin Joe Enabe, Joshua Sarcol
 DESCRIPTION : C code implementation of LE6.12: Vowel and Consonant
 COPYRIGHT   : Albert Justin Joe Enabe, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/11/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>
#include <stdbool.h>

bool isLetter (char ch);
bool isVowel (char ch);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : reads user input and prints to user if it is a vowel, consonant or neither
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
===========================================================================
*/

void main()
{
    char letter;

    //gets input from user
    printf("Enter a letter: ");
    scanf("%c", &letter);

    //checks if user input is either vowel, consonant, or neither
    if (!isLetter(letter))
        printf("INVALID INPUT!");
    else if (isVowel(letter))
        printf("VOWEL!");
    else
        printf("CONSONANT!");

}

/*
============================================================================
 FUNCTION    : isLetter (ch)
 DESCRIPTION : checks whether ch is a letter or not
 ARGUMENTS   : char ch: the letter to be checked 
 RETURNS     : bool: whether ch is a letter or not
===========================================================================
*/

bool isLetter (char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else
        return false;
}

/*
============================================================================
 FUNCTION    : isVowel (ch)
 DESCRIPTION : checks whether ch is a vowel letter or not
 ARGUMENTS   : char ch: the letter to be checked 
 RETURNS     : bool: whether ch is a vowel letter or not
===========================================================================
*/

bool isVowel (char ch){
    switch (ch) {
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
            return true;

        default:
            return false;
    }
}
