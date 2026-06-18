#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

void deleteMenu(NODE** root){

    int delValue;
    LIST* delPath = NULL;

    // submenu
    COLOR_BLUE;
    printf("=== DELETE A NODE ===\n");
    TEXT_RESET;
    printf("value to delete: ");
    scanf(" %d", &delValue);
    printf("\n");

    if(*root){
        // traverses tree to find value
        searchNodePath(*root, &delPath, delValue);
        printf("Tree display: ");
        treeDisplay(*root, delValue);
        printf("\n");

        // if value is not in tree
        if (delPath->node->data != delValue){
            COLOR_RED;
            printf("FAILED!\n");
            TEXT_RESET;
            printf("Value %d is not found in tree!\n", delValue);
            printf("Last node visited: %d\n", delPath->node->data);
            delValue = delPath->node->data;

        // otherwise
        } else {
            COLOR_GREEN;
            printf("Success!\n");
            TEXT_RESET;
            printf("Node removed\n");

            // initial removal of node from tree
            delPath = deleteNode(root, delValue);
        }

        splayTree(root, delPath);
        printf("Finished splaying!\n");
        
    } else {
        COLOR_RED;
        printf("FAILED!\n");
        TEXT_RESET;
        printf("Tree is empty!\n");
    }

    printf("Press any key to continue\n");
    getche();
}

LIST* deleteNode(NODE** root, int data){

    LIST* traversed = NULL;
    NODE* toDelete = *root;

    // traversal to the node to be deleted ('toDelete')
    while(toDelete->data != data){
        push(&traversed, toDelete);
        toDelete = (toDelete->data > data) ? toDelete->left : toDelete->right;
    }

    // pointer that points to 'toDelete'
    NODE** parentNode = parentOf(root, toDelete);
    
    // value that replaces 'toDelete' ('toReplace')
    NODE* toReplace = toDelete->right;

    // when nodes right of 'toDelete' exist
    if(toReplace){
        // determines leftmost node
        while(toReplace->left)
            toReplace = toReplace->left;

        // parent of replacement node
        NODE** upperCon = parentOf(root, toReplace);

        // right subtree of replacement node
        NODE* lowerCon = toReplace->right;

        // deletion of 'data'
        (*parentNode)->data = toReplace->data;

        // reconnecting right subtree to parent
        *upperCon = lowerCon;

    // when there are no nodes to the right of 'toDelete'
    } else 
        // replace 'toDelete'
        *parentNode = toDelete->left;

    return traversed;
}