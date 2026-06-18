#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "sortheader.h"

void main(){

    char* numbers = calloc(250, sizeof(char));
    char* current = calloc(25, sizeof(char));
    int size = 0;

    printf("Enter sequence of numbers\n");
    printf("Separated by spaces, ! as the terminator\n");
    scanf("%[^\n]249s", numbers);

    int* temp = calloc(strlen(numbers) / 2, sizeof(int));
    int cwidth = (strlen(numbers) - 2);

    for(current = strtok(numbers, " "); strcmp(current, "!"); current = strtok(NULL, " ")){
        temp[size++] = atoi(current);
    }

    int* bubble = calloc(size, sizeof(int));
    int* selection = calloc(size, sizeof(int));
    int* insertion = calloc(size, sizeof(int));

    for(int i = 0; i < size; i++){
        bubble[i] = temp[i];
        selection[i] = temp[i];
        insertion[i] = temp[i];
    }

    // header
    printf("\n%7s %-10s %-*s\t%-*s\t%-*s\n", "Pass", "Iteration", cwidth, "Exchange Sort", cwidth, "Selection Sort", cwidth, "Insertion Sort");

    for (int i = 0; i < size; i++){

        int numswapped = 0;

        for (int j = 0; j < size; j++){
            printf("%7.2d %-10.2d ", i + 1, j + 1);

                    // bubble sort code
                    if (bubble[j] > bubble[j+1] && j < size - 1){
                        Swap(&bubble[j], &bubble[j+1]);
                        numswapped++;
                    }
                    printall(bubble, size);

                if(!i){

                    // selection sort code
                    int* smallest = &selection[j];

                    for (int k = j; k < size; k++)
                        if (*smallest > selection[k])
                            smallest = &selection[k];

                    Swap(smallest, &selection[j]);
                    printall(selection, size);

                    // insertion sort code
                    for (int k = j; k > 0; k--){
                        if (insertion[k-1] > insertion[k])
                            Swap(&insertion[k-1], &insertion[k]);
                        else
                            break;
                    }

                    printall(insertion, size);
                }

            printf("\n");
        }

        if (!i)
            // when both selection and insertion sort is done (first pass)
        printf("%7s %-10s %-*s\t%-*s\t%-*s", "", "", cwidth, "", cwidth, "DONE!", cwidth, "DONE!");

        getche();
        printf("\n");

        if (!numswapped){
                // if no swaps in bubble sort occured
            printf("%7.2d %-10.2d %-*s", i + 2, 1, cwidth, "DONE!");
            break;
        }
    }

    getche();
}
