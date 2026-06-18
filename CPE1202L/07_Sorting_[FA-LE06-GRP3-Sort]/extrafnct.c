#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void Swap(int* x, int* y){
    int z = *x;
    *x = *y;
    *y = z;
}

void printall(int* List, int Size){
    for(int i = 0; i < Size; i++)
        printf("%d ", List[i]);
    printf("\t");
}
