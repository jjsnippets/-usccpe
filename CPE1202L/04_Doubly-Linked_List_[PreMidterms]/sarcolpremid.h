#ifndef SARCOLPREMID_H_INCLUDED
    #define SARCOLPREMID_H_INCLUDED

    // double linked list implemantation
    typedef struct node{
        int month;
        int day;
        int year;
        float amount;
        char id[100];
        char name[100];
        struct node* prev;
        struct node* next;
    } NODE;

    void addNode(NODE** start);
        // process for adding node(s) in the linked list

    void removeFirst(NODE** start);
        // process for removing the first node in the linked list

#endif
