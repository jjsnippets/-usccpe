#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    // reset text alterations
    #define TEXT_RESET printf("\e[m")

    // only one of the following text alterations can be applied at a time
        // applies bold to text
        #define BOLD_TEXT printf("\e[1m")

        // applies color to text
        #define COLOR_RED printf("\e[91m")
        #define COLOR_GREEN printf("\e[92m")
        #define COLOR_BLUE printf("\e[94m")
        #define COLOR_PINK printf("\e[95m")

        #define MIN_COLOR printf("\e[93m")
        #define MAX_COLOR printf("\e[33m")


    // moves cursor by 'x' spaces
    #define MOVE_UP(x) printf("\e[%dA", x)
    #define MOVE_DOWN(x) printf("\e[%dB", x)
    #define MOVE_LEFT(x) printf("\e[%dD", x)

    // structure definitions
    typedef struct node {
        int data;
        char text[4];
        struct node* left;
        struct node* right;
    } NODE;

    typedef struct list{
        NODE* node;
        struct list* next;
    } LIST;

    // in add.c
    void addMenu(NODE** maxHeap, NODE** minHeap, int* count);
        void addMax(NODE** root, int addValue, char* addText, int* size);
        void addMin(NODE** root, int addValue, char* addText, int* size);

    void push(LIST** head, NODE* toAdd);
    NODE* pop(LIST** head);

    // in delete.c
    void deleteMenu(NODE** maxHeap, NODE** minHeap, int* count);
        void deleteMax(NODE** root, int delValue, int* size);
        void deleteMin(NODE** root, int delValue, int* size);

    // in traverse.c
    void treeDisplay(NODE* root, int match);
    void showLeaves(NODE* root, int depth, int match);
    int treeDepth(NODE* root, int depth);

#endif
