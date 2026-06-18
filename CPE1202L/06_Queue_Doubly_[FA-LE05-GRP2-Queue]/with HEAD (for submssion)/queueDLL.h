
//Hatulan - enqueueMenu, enqueue
//Sarcol - dequeueMenu, dequeue

//shared - show, main, queueDLL

#ifndef QUEUEDLL_H
    #define QUEUEDLL_H

    typedef struct node{
        char fn[100];
        char mn[100];
        char ln[100];
        char pn[100];
        char ea[100];
        struct node* next;
        struct node* prev;
    } NODE;

    typedef struct queueStruct{
        struct node* queueHead;
        int queueSize;
        struct node* queueTail;
    } QUEUESTRUCT;

    void enqueueMenu(QUEUESTRUCT** List);
    void dequeueMenu(QUEUESTRUCT** List);

    void enqueue(QUEUESTRUCT** List, NODE* toAdd);

    NODE* dequeue(QUEUESTRUCT** head);

    void showAll(QUEUESTRUCT** List);

#endif
