#include <stdio.h>
#include <string.h>
#define SIZE 10

float calculateAverage(int numArray[]);
void printNumStatusAverage(int numArray[], float average);

void main(){
    int list[SIZE];
    float average;

    for(int i = 0; i < SIZE; i++){
        printf("Enter integer no.%d: ", i + 1);
        scanf("%d", &list[i]);
    }

    average = calculateAverage(list);
    printf("\nAverage is %.2f\n", average);

    printNumStatusAverage(list, average);
}


float calculateAverage(int numArray[]){
    float sum = 0;

    for(int i = 0; i < SIZE; i++)
        sum += (float)numArray[i];

    return sum/SIZE;
}

void printNumStatusAverage(int numArray[], float average){
    char word[6];

    for(int i = 0; i < SIZE; i++){
        if ((float)numArray[i] > average)
            strcpy(word, "ABOVE");
        else if ((float)numArray[i] < average)
            strcpy(word, "BELOW");
        else
            strcpy(word, "EQUAL");

        printf("no.%d (%.2f) is %s the average of %.2f\n", i + 1, (float)numArray[i], word, average);
    }
}
