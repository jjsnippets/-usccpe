/*
============================================================================
 FILE        : cardenasRo_sarcolJo_LE8.12.c
 AUTHOR      : Roy Lorenz Cardenas, Joshua Sarcol
 DESCRIPTION : programming task for LE 8.12 Search Element
 COPYRIGHT   : Roy Lorenz Cardenas, Joshua Sarcol
 REVISION HISTORY
 Date:              By: 	        Description:
 11/25/2023         Sarcol          made code
 11/26/2023         Sarcol          used calloc() in main()

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int find(int *arr, int size, int search);

/*
============================================================================
 FUNCTION    : main ()
 DESCRIPTION : determines if a number is in the user inputs
 ARGUMENTS   : void: no passed variables
 RETURNS     : void: no returned variables
============================================================================
*/

void main(){
    int size, search;

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

    //prompts and gets from user the number to be searched
    printf("\nSearch data: ");
    scanf("%d", &search);

    //determines if the number is found in the data or not
    int result = find(list, size, search);

    //prints the result
    if (result != -1)
        printf("FOUND in Index %d", result);
    else
        printf("NOT FOUND");

    free(list);
}

/*
============================================================================
 FUNCTION    : find (*arr, size, search)
 DESCRIPTION : does the searching of the number in the list of inputs
 ARGUMENTS   : int* arr - pointer of the list of numbers
               int size - size of the list
               int search - the number to be searched in the list
 RETURNS     : int i - index of the number in the list if in the list, -1 otherwise
============================================================================
*/

int find(int *arr, int size, int search){
    for(int i = 0; i < size; i++, arr++)
        if (*arr == search) //if search is in the data
            return i;
    
    return -1;
}