/*
============================================================================
 FILE        : ilaGe_sarcolJo_LE7.11.c
 AUTHOR      : Georelle Ila, Joshua Sarcol
 DESCRIPTION : programming task for LE 7.11: Largest and Smallest
 COPYRIGHT   : Georelle Ila, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/18/2023         Sarcol          made code

============================================================================
*/

#include <stdio.h>

int smallestInList(int arr[]);
int largestInList(int arr[]);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines the largest and smallest of the user inputs
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main (){
    int list[10];

    //grabs from user 10 integers
    for(int i = 0; i < 10; i++){
        printf("n%d: ", i+1);
        scanf("%d", &list[i]);
    }

    //prints the 10 integers
    for(int i = 0; i < 10; i++)
        printf("%d: %d\n", i+1, list[i]);

    //prints the largest and smallest of the 10 integers 
    printf("largest: %d\n", largestInList(list));
    printf("smallest: %d\n", smallestInList(list));

}

/*
============================================================================
 FUNCTION    : smallestInList (arr[])
 DESCRIPTION : determines the smallest integer of an array
 ARGUMENTS   : int arr: array of size [10]
 RETURNS     : int result: smallest integer of arr[]
============================================================================
*/

int smallestInList(int arr[]){
    int result = arr[0];

    for(int i = 1; i < 10; i++)
        (arr[i] < result) ? result = arr[i] : 0;

    return result;

}

/*
============================================================================
 FUNCTION    : largestInList (arr[])
 DESCRIPTION : determines the largest integer of an array
 ARGUMENTS   : int arr: array of size [10]
 RETURNS     : int result: largest integer of arr[]
============================================================================
*/

int largestInList(int arr[]){
    int result = arr[0];

    for(int i = 0; i < 10; i++)
        (arr[i] > result) ? result = arr[i] : 0;

    return result;

}