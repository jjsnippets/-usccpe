/*
============================================================================
 FILE        : ilaGe_sarcolJo_LE7.13.c
 AUTHOR      : Georelle Ila, Joshua Sarcol
 DESCRIPTION : programming task for LE 7.13: Longest String
 COPYRIGHT   : Georelle Ila, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/18/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>
#include <string.h>

int longestString(char arr[5][100]);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines the longest string out of 5 user inputted strings
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main(){
    char words[5][100];

    //gets from user 5 strings
    for(int i = 0; i < 5; i++){
        printf("Enter word/string no. %d: ", i+1);
        gets(words[i]);
    }

    //prints the longest string
    printf("The (first) longest string is ");
    puts(words[longestString(words)]);
}

/*
============================================================================
 FUNCTION    : longestString (arr[5][100])
 DESCRIPTION : determines the index of the longest string in arr[5][100]
 ARGUMENTS   : char arr[5][100]: 2 dimensional array of characters of size [5][100]
 RETURNS     : int result: index of the longest string in arr[5][100]
============================================================================
*/

int longestString(char arr[5][100]){
    int length = strlen(arr[0]), result = 0;

    for(int i = 1; i < 5; i++){
        if(length < strlen(arr[i])){
            length = strlen(arr[i]);
            result = i;
        }
    }

    return result;
}


