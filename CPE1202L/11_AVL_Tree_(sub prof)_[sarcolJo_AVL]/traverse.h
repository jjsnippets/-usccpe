/*
======================================================
FILE        : traverse.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : interface file displaying tree traversals
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#include "add.h"

#ifndef DISPLAY_H
    #define DISPLAY_H

    void enqueue(LIST** root, NODE* toAdd);
    NODE* dequeue(LIST** root);

    void traverseMenu(NODE* root);

    void breadthFirst(NODE* root);
    void inFix(NODE* root);
    void preFix(NODE* root);
    void postFix(NODE* root);
    void treeDisplay(NODE* root, int match);

    void showLeaves(NODE* root, int depth, int match);
    int treeDepth(NODE* root, int depth);

#endif