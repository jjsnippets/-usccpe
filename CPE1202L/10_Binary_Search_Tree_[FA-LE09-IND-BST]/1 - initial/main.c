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
    NODE* data;
    struct queue* next;
} QUEUE;

void displayNode(NODE* toShow);
void displayAll(NODE* root, int count);

void enqueue(QUEUE** head, NODE* toAdd);
NODE* dequeue(QUEUE** head);

void addNode(NODE** root, int data, int* count);
void deleteNode(NODE** root, int data, int* count);


void main(){

    NODE* root = calloc(1, sizeof(NODE));
    int count = 0;

    // [10, 6, 2, 21, 17, 13, 9, 5, 1, 20, 16]
    for (int i = 0; i < 11; i++){
        // printf("[%d %d] ", i, ((i+10)*295) % 23);
        addNode(&root, ((i+9)*295) % 23, &count);
    }

    // addNode(&root, 6, &count);
    // addNode(&root, 2, &count);
    // addNode(&root, 11, &count);

    displayAll(root, count);

    printf("===\n");

    deleteNode(&root, 17, &count);

    printf("=CODE RAN WITHOUT CRASHING=\n\n");

}

void displayNode(NODE* toShow){

    // debug
    printf("[%d %ld %ld %ld]\n", toShow->x, toShow, toShow->left, toShow->right);

    printf("Parent: %d\n", toShow->x);

    if (toShow->left)
        printf("\tLeft child: %d\n", toShow->left->x);
    if (toShow->right)
        printf("\tRight child: %d\n", toShow->right->x);

    printf("\n");

}

void displayAll(NODE* root, int count){

    if (!count) return;
    int inLine = 1;

    QUEUE* bft = calloc(1, sizeof(QUEUE));
    enqueue(&bft, root);

    while (inLine){

        NODE* display = dequeue(&bft);
        displayNode(display);
        inLine--;

        if (display->left){
            enqueue(&bft, display->left);
            inLine++;
        }
        if (display->right){
            enqueue(&bft, display->right);
            inLine++;
        }
    }
}

void enqueue(QUEUE** head, NODE* toAdd){

    if (!(*head)->data){
        (*head)->data = toAdd;
        return;
    }

    QUEUE* lastQueue = *head;
    QUEUE* insert = calloc(1, sizeof(QUEUE));
    insert->data = toAdd;

    while (lastQueue->next) lastQueue = lastQueue->next;
    lastQueue->next = insert;

}

NODE* dequeue(QUEUE** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->data;

    QUEUE* newHead = ((*head)->next) ? (*head)->next : calloc(1, sizeof(NODE));

    *head = newHead;
    return result;

}

void addNode(NODE** root, int data, int* count){

    printf("{%d: %d}", *count+1, data);

    NODE* newNode = calloc(1, sizeof(NODE));
    newNode->x = data;

    if (!(*count)++){
        *root = newNode;
        return;
    }

    NODE* currentNode = *root;

    while (1){
        if (data < currentNode->x){
            if (!(currentNode->left)){
                currentNode->left = newNode;
                break;
            } else
                currentNode = currentNode->left;

        } else {
            if (!(currentNode->right)){
                currentNode->right = newNode;
                break;
            } else
                currentNode = currentNode->right;
        }
    }
}

void deleteNode(NODE** root, int data, int* count){

    printf("CALLED FUNCTION\n");

    NODE* toDelete = calloc(1, sizeof(NODE));
    NODE* parentDelete;
    
    // if ((*root)->x = data){

    // } else {

        toDelete = *root;

        while(1){
            printf("<%d %d>", data, toDelete->x);

            if (data == toDelete->x){
                break;
            }

            if (data < toDelete->x){
                if (toDelete->left) {
                    printf("went left\n");
                    parentDelete = toDelete;
                    toDelete = toDelete->left;
                    continue;
                } else {
                    printf("end of left\n");
                    parentDelete = NULL;
                    toDelete = NULL;
                    break;
                }
            } else if (data > toDelete->x){
                if (toDelete->right) {
                    printf("went right\n");
                    parentDelete = toDelete;
                    toDelete = toDelete->right;
                    continue;
                } else {
                    printf("end of right\n");
                    parentDelete = NULL;
                    toDelete = NULL;
                    break;
                }
            }
        }

        if (!toDelete) {
            return;

        } else {
            displayNode(parentDelete);
            displayNode(toDelete);

            NODE* reconnectNode = toDelete;

            if (toDelete->right){
                reconnectNode = toDelete->right;
                while (reconnectNode->left) reconnectNode = reconnectNode->left;
                // ENDED HERE

            }



        }
            

        



    // }




}
