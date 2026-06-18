#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    typedef struct node {
        int x;
        struct node* left;
        struct node* right;
    } NODE;

    typedef struct queue {
        NODE* current;
        struct queue* next;
    } QUEUE;

    void displayNode(NODE* toShow);
    void displayAll(NODE* root, int size);

    void enqueue(QUEUE** head, NODE* toAdd);
    NODE* dequeue(QUEUE** head);

    void addNode(NODE** root, int data, int* size);
    int deleteNode(NODE** root, int data, int* size);

    NODE* postOrderSearch(NODE* tree, int find);

    void addMenu(NODE** root, int* count);
    void deleteMenu(NODE** root, int* count);
    void traversalMenu(NODE** root, int* count);

#endif // FUNCTIONS_H
