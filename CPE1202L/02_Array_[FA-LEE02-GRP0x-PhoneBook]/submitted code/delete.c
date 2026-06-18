#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook.h"

void deletePrcs (PBOOK* all, int* size, int maxSize){

    char userInput;
    char* compare = calloc(100, sizeof(char));
    int inList = 0, indexList;

    printf("[L] Search by Last Name\n[N] Search by Mobile Number\n");
    fflush(stdin);
    userInput = tolower(getche());
    printf("\n\n");


    switch (userInput) {
        case 'l':
            
            printf("Input Last Name: ");
            fflush(stdin);
            scanf("%[^\n,]s", compare);
            printf("\n");

            for(int i = 0; i < *size; i++){
                if (strcmp(compare, all[i].lname) == 0){
                    inList = 1;
                    indexList = i;
                    break;
                }
            }

            if (!inList){
                printf("Last Name not found!\n");
                fflush(stdin);
                getche();
                free(compare);
                return;
            }

            break;
        
        case 'n':
            
            printf("Input Mobile Number: ");
            fflush(stdin);
            scanf("%[^\n,]s", compare);
            printf("\n");

            for(int i = 0; i < *size; i++){
                if (strcmp(compare, all[i].num) == 0){
                    inList = 1;
                    indexList = i;
                    break;
                }
            }

            if (!inList){
                printf("Mobile number not found!\n");
                fflush(stdin);
                getche();
                free(compare);
                return;
            }

            break;

        default:
            free(compare);
            return;

    }

    for(int i = indexList; i < (*size - 1); i++){
        strcpy(all[i].fname, all[i + 1].fname);
        strcpy(all[i].mname, all[i + 1].mname);
        strcpy(all[i].lname, all[i + 1].lname);
        strcpy(all[i].num, all[i + 1].num);
        strcpy(all[i].email, all[i + 1].email);
    }

    (*size)--;

    saveToFile(all, size, maxSize);
    printf("Entry Successfully deleted!\n");
    fflush(stdin);
    getche();

    free(compare);
    return;
}