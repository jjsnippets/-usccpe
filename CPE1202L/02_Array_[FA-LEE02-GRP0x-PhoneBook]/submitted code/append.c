#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "phonebook.h"

void appendPrcs(PBOOK* all, int* size, int maxSize){

    PBOOK* append = calloc(1, sizeof(PBOOK));
    char confirm;

    strcpy(append->fname, appendMenu("Input First Name: "));
    strcpy(append->mname, appendMenu("Input Middle Name: "));
    strcpy(append->lname, appendMenu("Input Last Name: "));
    strcpy(append->num, appendMenu("Input Mobile Number: "));
    strcpy(append->email, appendMenu("Input Email: "));

    printf("\nSave record [Y/N]?\n");
    confirm = tolower(getche());

    if (confirm == 'n')
        return;

    strcpy(all[*size].fname, append->fname);
    strcpy(all[*size].mname, append->mname);
    strcpy(all[*size].lname, append->lname);
    strcpy(all[*size].num, append->num);
    strcpy(all[*size].email, append->email);

    (*size)++;

    //saveToFile(all, size, maxSize);
    saveToFile(all, size, maxSize);
    printf("\n\nSaved successfully\n");
    free(append);
    fflush(stdin);
    getche();

}

char* appendMenu(char* menu){
    fflush(stdin);
    char* text = calloc(100, sizeof(char));
    printf("%s", menu);
    scanf("%[^\n,]s", text);
    return text;
}