
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



    void enqueueMenu(NODE** head);
    void dequeueMenu(NODE** head);

    void enqueue(NODE** head, NODE* toAdd);

    NODE* dequeue(NODE** head);

    void showAll(NODE** head);

#endif
