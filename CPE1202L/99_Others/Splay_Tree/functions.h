#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

        #define TEXT_RESET printf("\e[m")
        #define BOLD_TEXT printf("\e[1m")
        #define COLOR_RED printf("\e[91m")
        #define COLOR_GREEN printf("\e[92m")
        #define COLOR_BLUE printf("\e[94m")
        #define COLOR_PINK printf("\e[95m") 

        #define MOVE_UP(x) printf("\e[%dA", x)
        #define MOVE_DOWN(x) printf("\e[%dB", x)
        #define MOVE_LEFT(x) printf("\e[%dD", x)

    // structure definitions
    typedef struct node {
        int data;
        struct node* left;
        struct node* right;
    } NODE;

    typedef struct list{
        NODE* node;
        struct list* next;
    } LIST;

    // from add.c
    void addMenu(NODE** root);
    LIST* addNode(NODE** root, int data);

    // from splay.c
    void splayTree(NODE** root, LIST* checkNodes);

    NODE* rotateLeft(NODE* A, NODE* B);
    NODE* rotateRight(NODE* A, NODE* B);
    NODE** parentOf(NODE** root, NODE* child);

    void push(LIST** head, NODE* toAdd);
    NODE* pop(LIST** head);

    // from delete.c
    void deleteMenu(NODE** root);
    LIST* deleteNode(NODE** root, int data);

    // from search.c
    void searchMenu(NODE** root);
    NODE* searchNode(NODE* root, int data);
    LIST* searchNodePath(NODE* root, LIST** result, int x);

    // from traverse.c
    void treeDisplay(NODE* root, int match);
    void waitForUser();

    void showLeaves(NODE* root, int depth, int match);
    int treeDepth(NODE* root, int depth);

        void traverseMenu(NODE* root);
        void enqueue(LIST** root, NODE* toAdd);
        NODE* dequeue(LIST** root);
        void breadthFirst(NODE* root);
        void inFix(NODE* root);
        void preFix(NODE* root);
        void postFix(NODE* root);

    // from zdebug.c
    void balanceDisplay(NODE* root);
    void showBalance(NODE* root, int depth);
    void printNode(NODE* toShow);
    void printStack(LIST* toShow);

#endif