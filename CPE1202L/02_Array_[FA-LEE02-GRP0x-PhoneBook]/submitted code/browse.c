#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook.h"

void browsePrcs(PBOOK* all, int* size, int maxSize){

    char userInput = 'a';
    char* compare = calloc(100, sizeof(char));
    int inList, indexList;

    char* separator = calloc(80, sizeof(char));
    memset(separator, '=', 79);

    do {
        inList = 0;
        memset(compare, '\0', 100);

        browseChoiceMenu();
        fflush(stdin);
        userInput = tolower(getche());

        printf("\n\n");

        switch (userInput) {
            case 'b':
                printf("%-15s %-15s %-15s %-15s %-15s\n", "Last Name", "First Name", "Middle Name", "Mobile No.", "Email Address");
                printf("%s\n", separator);
                
                for(int i = 0; i < *size; i++){
                    printf("%-15s %-15s %-15s %-15s %-15s\n", all[i].lname, all[i].fname, all[i].mname, all[i].num, all[i].email);
                }

                printf("\n");       

                break;
            
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
                    break;
                }
                
                printf("%-15s %-15s %-15s %-15s %-15s\n", "Last Name", "First Name", "Middle Name", "Mobile No.", "Email Address");
                printf("%s\n", separator);
                printf("%-15s %-15s %-15s %-15s %-15s\n", all[indexList].lname, all[indexList].fname, all[indexList].mname, all[indexList].num, all[indexList].email);
                printf("\n");

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
                    printf("Mobile Number not found!\n\n");
                    break;
                }
                
                printf("%-15s %-15s %-15s %-15s %-15s\n", "Last Name", "First Name", "Middle Name", "Mobile No.", "Email Address");
                printf("%s\n", separator);
                printf("%-15s %-15s %-15s %-15s %-15s\n", all[indexList].lname, all[indexList].fname, all[indexList].mname, all[indexList].num, all[indexList].email);
                printf("\n");

                break;
        }

        printf("Again [Y/N]\n");
        fflush(stdin);
        userInput = tolower(getche());
        printf("\n\n");

    } while ( userInput != 'n');

    free(compare);
    free(separator);
    return;

}

void browseChoiceMenu(){

    printf("[B]rowse All\n");
    printf("[L] Browse by Last Name\n");
    printf("[N] Browse by Mobile Number\n");

}