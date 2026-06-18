#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "phonebook-sll.h"

#define FILENAME "phonebook.txt"
    // name of the file

void saveToFile (NODE** start, int* size){
    NODE* currentNode;

    // file opened in write mode
    FILE* fp = fopen(FILENAME, "w");
    rewind(fp);

    fprintf(fp, ",lname,mname,fname,num,email\n");
        // header of the file

    //prints out the rest of the fields in the file
    for(int i = 0; i < *size; i++){
        currentNode = (i == 0 ? *start : currentNode->next);
        fprintf(fp, "%d,%s,%s,%s,%s,%s\n", i, currentNode->lname, currentNode->fname, currentNode->mname,currentNode->num, currentNode->email);
    }

    fclose(fp);
}

void loadFromFile (NODE** start, int* size){

    // file opened in read mode
    FILE* fp = fopen(FILENAME, "r");
    char* row = calloc(1000, sizeof(char));

    // if file does not exist
    if (fp == NULL){
       printf("A file named \"%s\" was not found. This will be automatically made after using this program.\n", FILENAME);
       printf("Press any key to continue\n");
       getche();
       fclose(fp);
       return;
    }

    // minimal error checking: checks if header is correct
    fgets(row, 1000, fp);
    if (strcmp(row, ",lname,mname,fname,num,email\n") != 0){
        printf("File format of \"%s\" is wrong. No data will be loaded in.\n", FILENAME);
        printf("Press any key to continue\n");
        getche();
        fclose(fp);
        return;
    }

    // each time the loop runs, grabs a row
    // stops when the row is empty (NULL)
    while (fgets(row, 1000, fp) != NULL)
    {
        NODE* addNode = calloc(1, sizeof(NODE));
        addNode->next = NULL;

        // grabs individual values from rows
        strtok(row, ",");
            // skips index
        strcpy(addNode->lname, strtok(NULL, ","));
        strcpy(addNode->fname, strtok(NULL, ","));
        strcpy(addNode->mname, strtok(NULL, ","));
        strcpy(addNode->num, strtok(NULL, ","));
        strcpy(addNode->email, strtok(NULL, "\n"));

        if(*size == 0){
                // special case when it is the first node to be added
            *start = addNode;
        } else {
            NODE* lastNode = (*start);

            for(int i = 0; i < (*size) - 1; i++){
                lastNode = lastNode->next;
            }

            lastNode->next = addNode;
        } // *better implementation: lastNode->next = addNode; lastNode = lastNode->next; without redeclaration of lastNode

        (*size)++;
    }

    printf("Data from \"%s\" successfully loaded!\n", FILENAME);
    printf("Press any key to continue\n");
    getche();
    fclose(fp);

}
