#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "queueDLL.h"

void enqueue(NODE** head, NODE* toAdd)
{
    if (*head == NULL)
    {
        *head = toAdd;
    }
    else
    {
        NODE* temp;
        temp = *head;

        if(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = toAdd;
        toAdd->prev = temp;
    };

    //showAll(head);
}

