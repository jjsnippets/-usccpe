/*
======================================================
FILE        : delete.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : interface file for removing a node from a tree
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include "add.h"

#ifndef DELETE_H
    #define DELETE_H

    void deleteMenu(NODE** root);
    LIST* deleteNode(NODE** root, int data);

#endif