#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minviabhead.h"

#define MAXSIZE 50

void main(){

    int maxSizePBook = MAXSIZE;
    PBOOK* list = calloc(maxSizePBook, sizeof(PBOOK));
    int currSizePBook = 0;

    strcpy(list[0].fname, "test first name");
    strcpy(list[0].mname, "mid name");
    currSizePBook = 1;

    printf("%s === %s === %s === %d\n", list[0].fname, list[0].mname, list[1].fname, currSizePBook);

    minviabfunc(list, &currSizePBook, maxSizePBook);

    printf("%s === %s === %s === %d", list[0].fname, list[0].mname, list[1].fname, currSizePBook);
    scanf("%s");


}