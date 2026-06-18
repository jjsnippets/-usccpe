#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queueDLL.h"

#define HEAD (*List)->queueHead
#define TAIL (*List)->queueTail

NODE* dequeue(QUEUESTRUCT** List){

    // dynamically allocated for return to work
    NODE* removedNode = calloc(1, sizeof(NODE));
    removedNode = HEAD;

    HEAD = HEAD->next;
    if(HEAD) HEAD->prev = NULL;
        // if newHead is a valid address, change .prev
        // otherwise (ie newHead == NULL), do nothing

    ((*List)->queueSize)--;

    return removedNode;
}
