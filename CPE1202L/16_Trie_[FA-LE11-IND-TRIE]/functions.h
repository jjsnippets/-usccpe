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
        #define MOVE_RIGHT(x) printf("\e[%dC", x)
        #define MOVE_LEFT(x) printf("\e[%dD", x)

    typedef struct node {
        struct node* children[26];
        int isWord;
        char finalWord[20];
    } NODE;

    typedef struct list{
        NODE* node;
        struct list* next;
    } LIST;

    // in add.c
        void addMenu(NODE** root, int* longestWord);
        void addNode(NODE** root, char* word, int wordLen);

    // NODE* split(NODE* root, int* median);

    // in delete.c
        void deleteMenu(NODE** root, int* longestWord);
        void deleteNode(NODE** root, char* word, int wordLen);

        void push(LIST** head, NODE* toAdd);
        NODE* pop(LIST** head);

    // in search.c
        void searchMenu(NODE* root, int longestWordLen);
        NODE* search(NODE* root, char* word, int wordLen);

        void displayTree(NODE* root, int longestWordLen, char* match);
        void showNodes(NODE* root, int depth, char* match);

#endif
