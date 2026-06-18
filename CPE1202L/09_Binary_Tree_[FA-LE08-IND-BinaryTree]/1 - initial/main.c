#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

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
void deleteNode(NODE** root, int data, int* size);

NODE* postOrderSearch(NODE* tree, int find);

void main(){

    NODE* root = calloc(1, sizeof(NODE));
    int count = 0;

    int list[] = {3, 5, 7, 1, 4, 8, 2, 6};

    for (int i = 1; i < 9; i++)
        addNode(&root, i, &count);

    displayAll(root, count);

    deleteNode(&root, 9, &count);
    deleteNode(&root, 2, &count);
    deleteNode(&root, 4, &count);
    deleteNode(&root, 1, &count);
    deleteNode(&root, 4, &count);
    deleteNode(&root, 5, &count);

    displayAll(root, count);

    printf("Successfully ran!");

}

void displayNode(NODE* toShow){

    // debug
    // printf("[%d %ld %ld %ld]\n", toShow->x, toShow, toShow->left, toShow->right);

    printf("Parent: %d\n", toShow->x);

    if (toShow->left)
        printf("\tLeft child: %d\n", toShow->left->x);
    if (toShow->right)
        printf("\tRight child: %d\n", toShow->right->x);

    printf("\n");

}

void displayAll(NODE* root, int size){

    if (!size) return;
    
    QUEUE* bft = calloc(1, sizeof(QUEUE));
    NODE* display;
    enqueue(&bft, root);

    while(size--){

        display = dequeue(&bft);
        displayNode(display);
        
        if (display->left) enqueue(&bft, display->left);
        if (display->right) enqueue(&bft, display->right);

    }
    free(bft);
}

void enqueue(QUEUE** head, NODE* toAdd){

    if (!(*head)->current){
        (*head)->current = toAdd;
        return;
    }

    QUEUE* lastQueue = *head;
    QUEUE* insertEnd = calloc(1, sizeof(QUEUE));
    insertEnd->current = toAdd;

    while (lastQueue->next)
        lastQueue = lastQueue->next;

    lastQueue->next = insertEnd;

}

NODE* dequeue(QUEUE** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->current;

    QUEUE* newHead = (*head)->next ? (*head)->next : calloc(1, sizeof(QUEUE));

    (*head) = newHead;
    return result;
}

void addNode(NODE** root, int data, int* size){

    NODE* newNode = calloc(1, sizeof(NODE));
    newNode->x = data;
    
    if (!(*size)++){
        *root = newNode;
        return;
    }

    int movement = 1;
    for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
    movement >>= 1;

    NODE* currentNode = *root;

    for (; movement > 1; movement >>= 1){

        if (*size & movement){
            (currentNode = currentNode->right);
        } else {
            (currentNode = currentNode->left);
        }
    }

    if (*size % 2){
            (currentNode->right = newNode);
    } else {
            (currentNode->left = newNode);
    } 
}

void deleteNode(NODE** root, int data, int* size){

    NODE* parentDelete = calloc(1, sizeof(NODE));
    printf("(%d)", *size);

    NODE* toLastNode = *root;
    int movement = 1;
    for (int i = *size >> 1; i > 0; movement <<= 1, i >>= 1);
    movement >>= 1;

    if (*size > 1){
        for (; movement > 1; movement >>= 1){

            if (*size & movement){
                (toLastNode = toLastNode->right);
            } else {
                (toLastNode = toLastNode->left);
            }
        }
    }

    if ((*root)->x == data){
        (*size)--;
        NODE* leftReattach = (*root)->left;
        NODE* rightReattach = (*root)->right;

        (*root) = (toLastNode->right) ? toLastNode->right : toLastNode->left;
        (*root)->left = leftReattach;
        (*root)->right = rightReattach;
        
        if (toLastNode->right){
            toLastNode->right = NULL;
        } else
            toLastNode->left = NULL;

        printf("Successfully removed!\n");

    } else {

        parentDelete = postOrderSearch(*root, data);
        if (parentDelete){
            (*size)--;
            NODE* deleteNode = (parentDelete->left->x == data) ? parentDelete->left : parentDelete->right;
            NODE* leftReattach = parentDelete->left->left;
            NODE* rightReattach = parentDelete->left->right;

            if (parentDelete->left->x == data){
                parentDelete->left = (toLastNode->right) ? toLastNode->right : toLastNode->left;

                    // reattach to new node
                if (toLastNode->right){
                    parentDelete->left->left = leftReattach;
                    parentDelete->left->right = rightReattach;
                } else {
                    parentDelete->left->left = leftReattach;
                    parentDelete->left->right = rightReattach;
                }

            } else {
                parentDelete->right = (toLastNode->right) ? toLastNode->right : toLastNode->left;

                // reattach to new node
                if (toLastNode->right){
                    parentDelete->right->left = leftReattach;
                    parentDelete->right->right = rightReattach;
                } else {
                    parentDelete->right->left = leftReattach;
                    parentDelete->right->right = rightReattach;
                }
            }

            if (toLastNode->right){
                toLastNode->right = NULL;
            } else
                toLastNode->left = NULL;
            
            printf("Successfully removed!\n");
        
        } else 
            printf("Data not found.\n");
    }
}

NODE* postOrderSearch(NODE* tree, int find){

    NODE* result = NULL;

    if (tree->left){

        if (tree->left->x == find){
            return tree;
        }
            
        else if (tree->left == NULL){
            return NULL;
        }
            
        else{
            result = postOrderSearch(tree->left, find);
            if (result)
                return result;

        }
    }

    if (tree->right){

        if (tree->right->x == find){
            return tree;
        }
            
        else if (tree->right == NULL){
            return NULL;
        }
            
        else{
            result = postOrderSearch(tree->right, find);
            if (result)
                return result;
        }
    }

    return result;
}