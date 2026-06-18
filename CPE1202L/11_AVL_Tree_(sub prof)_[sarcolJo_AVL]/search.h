/*
======================================================
FILE        : search.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : interface file for searching a node from a tree
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include "add.h"

#ifndef SEARCH_H
    #define SEARCH_H

    void searchMenu(NODE* root);
    NODE* searchNode(NODE* root, int x);

#endif