#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "queueDLL.h"

#define HEAD (*List)->queueHead
#define TAIL (*List)->queueTail

void enqueue(QUEUESTRUCT** List, NODE* toAdd)
{

    if (HEAD == NULL)
    {
        HEAD = toAdd;
        TAIL = toAdd;
    }
    else
    {
        TAIL->next = toAdd;
        toAdd->prev = TAIL;
        TAIL = TAIL->next;
    };

    ((*List)->queueSize)++;

    //showAll(head);
}

