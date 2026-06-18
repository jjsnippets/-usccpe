#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queueDLL.h"

void showAll(QUEUESTRUCT** List){

    NODE* toDisplay = (*List)->queueHead;
    char* separator = calloc(106, sizeof(char));
    memset(separator, '=', 105);

    // displays header
    printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n", "Last name", "First name", "Middle name", "Phone number", "Email Address");
    printf("%s\n", separator);

    while (toDisplay){
        printf("%-20s|%-20s|%-20s|%-20s|%-20s|\n", toDisplay->ln, toDisplay->fn, toDisplay->mn, toDisplay->pn, toDisplay->ea);
        toDisplay = toDisplay->next;
    }
    printf("\n");

    printf("Press any key to continue\n");
    getche();
    free(separator);
}
