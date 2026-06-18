#ifndef STACKSLL_H
    #define STACKSLL_H

    typedef struct node{
        char fn[100];
        char mn[100];
        char ln[100];
        char pn[100];
        char ea[100];
        struct node* next;
    } NODE;

    // in stackSLL.c
    void pushMenu(NODE** head);
    void popMenu(NODE** head);

    // in push.c
    void push(NODE** head, NODE* toAdd);
        // push operation on *head with object

    // in pop.c
    NODE* pop(NODE** head);
        // pops operation (FIFO)

    //in show.c
    void showAll(NODE** head);
        // shows all nodes in FIFO order

#endif
