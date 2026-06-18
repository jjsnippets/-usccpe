// gcc -o phonebook-sll.exe -g phonebook-sll.c append-sll.c browse-sll.c change-sll.c delete-sll.c filehandling-sll.c

#ifndef PHONEBOOK_SLL_H
    #define PHONEBOOK_SLL_H
 
    typedef struct node{
        char fname[100];
        char mname[100];
        char lname[100];
        char num[100];
        char email[100];
        struct node* next;
    } NODE;

    // in phonebook-sll.c
    void mainMenuDisp();
        // displays choice menu

    // in append-sll.c
    void appendPrcs (NODE** start, int* size);
        // when successful, adds a new node in the linked list
    char* appendMenu(char* menu);
        // crudely, combination of printf() and scanf functions
    void infoAdder(NODE* singleNode);
        // fills in details for the node fields

    // in browse-sll.c
    void displayChoiceMenu ();
        // displays menu in [b]
    void browsePrcs (NODE** start, int* size);
        // [b] process
    void displayTable (NODE* start, int showAll);
        // when showAll == 1, shows all nodes, otherwise, shows the node specified by NODE* start

    // in change-sll.c
    void changeChoiceMenu ();
        // displays menu in [c]
    void changePrcs (NODE** start, int* size);
        // [c] process

    // in delete-sll.c
    void deletePrcs (NODE** start, int* size);
        // [d] process

    // in filehandling-sll.c
    void loadFromFile (NODE** start, int* size);
        // loads from file named in define directive FILENAME
    void saveToFile (NODE** start, int* size);
        // saves to file named in define directive FILENAME

#endif
