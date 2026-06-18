/*
============================================================================
 FILE        : ilaGe_sarcolJo_LE7.12.c
 AUTHOR      : Georelle Ila, Joshua Sarcol
 DESCRIPTION : programming task for LE 7.12: Vowels and Consonants in String
 COPYRIGHT   : Georelle Ila, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/18/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int vowelCount(char arr[]);
int consonantCount(char arr[]);
int isVowel(char a);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines the number of vowels and consonants of the user inputted string
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main (){
    char word[100];

    //gets from user string
    printf("Enter a word/string: ");
    gets(word);

    //prints the number of vowels and consonants in the string
    printf("Number of vowels: %d\n", vowelCount(word));
    printf("Number of consonants: %d\n", consonantCount(word));

}

/*
============================================================================
 FUNCTION    : vowelCount (arr[])
 DESCRIPTION : counts the number of vowels in an array
 ARGUMENTS   : char arr[]: array of characters of arbitrary size
 RETURNS     : int result: number of vowels in arr[]
============================================================================
*/

int vowelCount(char arr[]) {
    int result = 0;

    for(int i = 0; i < strlen(arr); i++)
        if (isalpha(arr[i]) && isVowel(arr[i]))
            result++;

    return result;
}

/*
============================================================================
 FUNCTION    : consonantCount (arr[])
 DESCRIPTION : counts the number of consonants in an array
 ARGUMENTS   : char arr[]: array of characters of arbitrary size
 RETURNS     : int result: number of consonants in arr[]
============================================================================
*/

int consonantCount(char arr[]) {
    int result = 0;

    for(int i = 0; i < strlen(arr); i++)
        if (isalpha(arr[i]) && !isVowel(arr[i]))
            result++;

    return result;
}

/*
============================================================================
 FUNCTION    : isVowel (char a)
 DESCRIPTION : determines if the input is a vowel or not
 ARGUMENTS   : char a: character of interest
 RETURNS     : int result: 1 if vowel, 0 otherwise
============================================================================
*/

int isVowel(char a) {
    switch (tolower(a)) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return 1;
    
    default:
        return 0;
    }
}