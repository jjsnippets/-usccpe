/*
============================================================================
 FILE        : cardenasRo_sarcolJo_LE8.13.c
 AUTHOR      : Roy Lorenz Cardenas, Joshua Sarcol
 DESCRIPTION : programming task for LE 8.13 Maximum Number
 COPYRIGHT   : Roy Lorenz Cardenas, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/25/2023         Sarcol          made code
 11/26/2023         Sarcol          used calloc() in main()

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int largestNumber(int* arr, int size);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines the largest number of the user inputs
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main(){
    int size;

    //gets from the user the number of numbers to be recorded
    printf("Enter number of entries: ");
    scanf("%d", &size);

    //dynamically allocates the list
    int* list = calloc(size, sizeof(int));

    //gets from user the numbers
    for(int i = 0; i < size; i++){
        printf("Enter number %d: ", i + 1);
        scanf("%d", &list[i]);
    }

    //prints the largest number in the list
    printf("Maximum Number: %d\n", largestNumber(list, size));

    free(list);
}

/*
============================================================================
 FUNCTION    : largestNumber(*arr, size)
 DESCRIPTION : does the determination of the largest number
 ARGUMENTS   : int* arr - pointer of the list of numbers
               int size - size of the list
 RETURNS     : int large - the largest number in the list
============================================================================
*/

int largestNumber(int* arr, int size){
    int large = *arr++;

    for(int i = 1; i < size; i++, arr++)
        if(large < *arr)
            large = *arr;
    
    return large;

}