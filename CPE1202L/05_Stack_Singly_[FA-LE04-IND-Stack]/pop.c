#include <stdlib.h>
#include "stackSLL.h"

NODE* pop(NODE** head){

    NODE* outputNode = calloc(1, sizeof(NODE));

    outputNode = *head;
    *head = outputNode->next;
        //set *head to be the next node in stack

    return outputNode;
}
