#ifndef MINVIABHEAD_H
    #define MINVIABHEAD_H

    typedef struct pbook{
        char fname[100];
        char mname[100];
        char lname[100];
        char num[100];
        char email[100];
    } PBOOK;

    void minviabfunc (PBOOK* all, int* size, int maxSize);

#endif