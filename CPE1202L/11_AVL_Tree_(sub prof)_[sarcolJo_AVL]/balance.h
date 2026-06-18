/*
======================================================
FILE        : balance.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : interface file for balancing trees
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include "add.h"
#include "traverse.h"

#ifndef BALANCE_H
    #define BALANCE_H

    void balanceTree(NODE** root, LIST* checkNodes);

    NODE* rotateLeft(NODE* A, NODE* B);
    NODE* rotateRight(NODE* A, NODE* B);
    NODE** parentOf(NODE** root, NODE* child);

    void push(LIST** head, NODE* toAdd);
    NODE* pop(LIST** head);

#endif