#include "stackSLL.h"

void push(NODE** head, NODE* toAdd){

    if(*head) toAdd->next = *head;
        // when *head is !NULL
    *head = toAdd;
        // set *head to be newly added node

}
