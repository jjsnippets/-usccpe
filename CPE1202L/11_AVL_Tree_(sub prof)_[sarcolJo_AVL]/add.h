/*
======================================================
FILE        : add.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : interface file for adding a node into a tree
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#ifndef ADD_H
    #define ADD_H

    typedef struct node {
        int data;
        struct node* left;
        struct node* right;
    } NODE;

    typedef struct list{
        NODE* node;
        struct list* next;
    } LIST;

    void addMenu(NODE** root);
    LIST* addNode(NODE** root, int data);

#endif