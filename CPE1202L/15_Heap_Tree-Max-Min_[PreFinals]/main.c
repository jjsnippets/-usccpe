#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

int main(){

    NODE* maxHeap = NULL;
    NODE* minHeap = NULL;
    int count = 0;
    char userInput;

    do{
        system("cls");

        BOLD_TEXT;
        printf("=== MAIN MENU ===\n");
        TEXT_RESET;
        printf("[1] Add new node\n");
        printf("[2] Delete a node\n");
        printf("[3] Exit\n");

        userInput = getche();
        printf("\n\n");

        switch (userInput) {
            case '1':
                addMenu(&maxHeap, &minHeap, &count);
                break;

            case '2':
                deleteMenu(&maxHeap, &minHeap, &count);
                break;
        }
    } while (userInput != '3');

    return 0;
}
