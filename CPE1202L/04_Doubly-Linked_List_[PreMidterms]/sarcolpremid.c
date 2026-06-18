#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "sarcolpremid.h"

void main(){

    NODE* head = NULL;
    char userInput;

    while (1){
        // main menu
        system("cls");
        printf("=== PAYMENT RECORD MAIN MENU ===\n");
        printf("[+] add new payment record\n");
        printf("[-] delete payment record\n");
        printf("[X] exit program\n");
        printf("\nChoice?\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

        if (userInput == 'x')
            break;

        switch (userInput){

            case 'a':
            case '+':
                addNode(&head);
                break;

            case 'r':
            case '-':
                removeFirst(&head);
                break;
        }
    }
}



void addNode(NODE** start){

    char userInput;
    NODE* lastNode = *start;
    NODE* currentNode;
    float total = 0;

    char* separator = calloc(75, sizeof(char));
    memset(separator, '=', 74);

    do {
        // initialization of values
        NODE* newNode = calloc(1, sizeof(NODE));
        newNode->prev = NULL;
        newNode->next = NULL;

        // input menu
        fflush(stdin);
        printf("Input ID #: ");
        scanf(" %99[^\n]s", newNode->id);

        printf("Input payee's full name: ");
        scanf(" %99[^\n]s", newNode->name);

        printf("Input month: ");
        scanf(" %d", &(newNode->month));

        printf("Input day: ");
        scanf(" %d", &(newNode->day));

        printf("Input year: ");
        scanf(" %d", &(newNode->year));

        printf("Input pay amount: ");
        scanf(" %f", &(newNode->amount));

        fflush(stdin);
        printf("\nAgain [y/n]?\n");
        userInput = tolower(getche());
        printf("\n\n");

        if (*start == NULL){
                // when linked list size is zero
            *start = newNode;
            lastNode = newNode;

        } else {
            while (lastNode->next != NULL){
                    // determines last node in the linked list
                lastNode = lastNode->next;
            }

            lastNode->next = newNode;
            newNode->prev = lastNode;
            lastNode = newNode;
        }

    } while (userInput == 'y');

    // teller output
    printf("%10s %15s %15s %15s %15s\n", "Record #", "Pay Date", "Pay Amt", "Pay ID", "Payee");
    printf("%s\n", separator);

    currentNode = *start;
    for(int i = 1; currentNode != NULL; i++){
        printf("%10.03d %7.02d/%02d/%04d %15.2f %15s %15s\n", i, currentNode->month, currentNode->day, currentNode->year, currentNode->amount, currentNode->id, currentNode->name);
        total += currentNode->amount;
        currentNode = currentNode->next;
    }

    printf("\n%26s %15.2f\n\n", "Grand Total:", total);

    printf("Press any key to continue\n");
    getche();

}



void removeFirst(NODE** start){

    if (*start == NULL){
            // when linked list size is zero
        printf("No record to be removed!\n\n");
        printf("Press any key to continue\n");
        getche();
        return;
    }

    NODE* toRemove = *start;
    NODE* nextNode = toRemove->next;

    char userInput;
    float total = 0;

    char* separator = calloc(75, sizeof(char));
    memset(separator, '=', 74);

    // prompt to delete
    printf("%10s %15s %15s %15s %15s\n", "Record #", "Pay Date", "Pay Amt", "Pay ID", "Payee");
    printf("%s\n", separator);
    printf("%10.03d %7.02d/%02d/%04d %15.2f %15s %15s\n\n", 1, toRemove->month, toRemove->day, toRemove->year, toRemove->amount, toRemove->id, toRemove->name);
    printf("WARNING - the record above will be deleted!\n\n");
    printf("Proceed [y/n]?\n");
    userInput = tolower(getche());
    printf("\n\n");

    if (userInput != 'y'){
        printf("Operation cancelled\n\n");
        printf("Press any key to continue\n");
        return;
    }

    // first node removal code
    if (nextNode == NULL){
            // when linked list size is one
        *start = NULL;
        free(toRemove);

    } else {
        *start = nextNode;
        nextNode->prev = NULL;
        free(toRemove);
    }

    // teller output after removal
    printf("%10s %15s %15s %15s %15s\n", "Record #", "Pay Date", "Pay Amt", "Pay ID", "Payee");
    printf("%s\n", separator);

    NODE* currentNode = *start;
    for(int i = 1; currentNode != NULL; i++){
        printf("%10.03d %7.02d/%02d/%04d %15.2f %15s %15s\n", i, currentNode->month, currentNode->day, currentNode->year, currentNode->amount, currentNode->id, currentNode->name);
        total += currentNode->amount;
        currentNode = currentNode->next;
    }

    printf("\n%26s %15.2f\n\n", "Grand Total:", total);

    printf("Press any key to continue\n");
    getche();
}
