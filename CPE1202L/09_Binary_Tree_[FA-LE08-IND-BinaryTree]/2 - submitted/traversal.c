#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

#define BOLD_TEXT printf("\e[1m")
#define COLOR_RED printf("\e[91m")
#define COLOR_GREEN printf("\e[92m")
#define COLOR_BLUE printf("\e[94m")
#define TEXT_RESET printf("\e[m")

void enqueue(QUEUE** head, NODE* toAdd){

    if (!(*head)->current){
        (*head)->current = toAdd;
        return;
    }

    QUEUE* lastQueue = *head;
    QUEUE* insertEnd = calloc(1, sizeof(QUEUE));
    insertEnd->current = toAdd;

    while (lastQueue->next)
        lastQueue = lastQueue->next;

    lastQueue->next = insertEnd;

}

NODE* dequeue(QUEUE** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->current;

    QUEUE* newHead = (*head)->next ? (*head)->next : calloc(1, sizeof(QUEUE));

    (*head) = newHead;
    return result;
}
