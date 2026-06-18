#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook.h"

void changePrcs (PBOOK* all, int* size, int maxSize){

    char userInput;
    char* compare = calloc(100, sizeof(char));
    int inList = 0, indexList;

    char* separator = calloc(80, sizeof(char));
    memset(separator, '=', 79);

    do {
        inList = 0;
        memset(compare, '\0', 100);

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
                    free(separator);
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
                    free(separator);
                    return;
                }

                break;
            
            default:
                free(compare);
                free(separator);
                return;

        }

        printf("%-15s %-15s %-15s %-15s %-15s\n", "Last Name", "First Name", "Middle Name", "Mobile No.", "Email Address");
        printf("%s\n", separator);
        printf("%-15s %-15s %-15s %-15s %-15s\n", all[indexList].lname, all[indexList].fname, all[indexList].mname, all[indexList].num, all[indexList].email);
        printf("\n");

        changeChoiceMenu();
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

        printf("Replace with: ");
        fflush(stdin);
        memset(compare, '\0', 100);
        scanf("%[^\n,]s", compare);
        printf("\n");

        switch (userInput) {
        case 'l':
            strcpy(all[indexList].lname, compare);
            break;

        case 'm':
            strcpy(all[indexList].mname, compare);
            break;

        case 'f':
            strcpy(all[indexList].fname, compare);
            break;

        case 'n':
            strcpy(all[indexList].num, compare);
            break;

        case 'e':
            strcpy(all[indexList].email, compare);
            break;
        }

        printf("%-15s %-15s %-15s %-15s %-15s\n", "Last Name", "First Name", "Middle Name", "Mobile No.", "Email Address");
        printf("%s\n", separator);
        printf("%-15s %-15s %-15s %-15s %-15s\n", all[indexList].lname, all[indexList].fname, all[indexList].mname, all[indexList].num, all[indexList].email);
        printf("\n");        

        saveToFile(all, size, maxSize);
        printf("Again [Y/N]\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");
    
    } while (userInput != 'n');

    free(compare);
    free(separator);

}

void changeChoiceMenu (){

    printf("Change What?\n");
    printf("[L] Last Name\n");
    printf("[M] Middle Name\n");
    printf("[F] First Name\n");
    printf("[N] Mobile Number\n");
    printf("[E] Email Address\n");

}