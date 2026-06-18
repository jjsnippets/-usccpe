#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queueDLL.h"

NODE* dequeue(NODE** head){

    // dynamically allocated for return to work
    NODE* removedNode = calloc(1, sizeof(NODE));
    removedNode = *head;

    NODE* newHead = (*head)->next;

    *head = newHead;
    if(newHead) newHead->prev = NULL;
        // if newHead is a valid address, change .prev
        // otherwise (ie newHead == NULL), do nothing

    return removedNode;
}
