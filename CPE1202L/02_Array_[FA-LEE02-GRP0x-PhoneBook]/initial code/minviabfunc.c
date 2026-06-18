#include <stdio.h>
#include <string.h>
#include "minviabhead.h"

void minviabfunc (PBOOK* all, int* size, int maxSize){

    memset(all[0].mname, '\0', 100);
    strcpy(all[0].mname, "new mname");
    strcpy(all[1].fname, "updating size via pointers");

    (*size)++;
}