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

    void addMenu(NODE** root, int* count);
    void addNode(NODE** root, int data, int* size);


    void deleteMenu(NODE** root, int* count);
    int deleteNode(NODE** root, int data, int* size);
    NODE* searchNode(NODE* tree, int find);


    void traversalMenu(NODE** root, int* count);
    void breadthFirst(NODE** root);
    void inOrder(NODE* root, int depth);
    void preOrder(NODE* root, int depth);
    void postOrder(NODE* root, int depth);

    void treeDisplay(NODE* root, int depth);
    void treeMode(NODE* root);
    int treeDepth(NODE* root, int depth);

    void enqueue(QUEUE** head, NODE* toAdd);
    NODE* dequeue(QUEUE** head);

#endif
