#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    typedef struct node {
        int x;
        struct node* left;
        struct node* right;
    } NODE;

    typedef struct queue {
        NODE* data;
        struct queue* next;
    } QUEUE;

    void displayNode(NODE* toShow);
    void displayAll(NODE* root, int count);

    void enqueue(QUEUE** head, NODE* toAdd);
    NODE* dequeue(QUEUE** head);

    void addNode(NODE** root, int data, int* count);
    void deleteNode(NODE** root, int data, int* count);

    void addMenu(NODE** root, int* count);
    void deleteMenu(NODE** root, int* count);
    void traversalMenu(NODE** root, int* count);

#endif // FUNCTIONS_H
