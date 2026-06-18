#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

#define MOVEUP(x) printf("\e[%dA", x)
#define MOVEDOWN(x) printf("\e[%dB", x)

typedef struct node {
    int type; // 1:( 2:) 3:= 4:numbers 5:variables 6:+- 7:*/ 8:^
    float num;
    char operate;
    struct node* left;
    struct node* right;
} NODE;

typedef struct list {
    NODE* data;
    struct list* next;
} LIST;

void enqueue(LIST** head, NODE* toAdd){

    LIST* insert = calloc(1, sizeof(LIST));
    insert->data = toAdd;

    if (!*head){
        *head = insert;
    
    } else {
        LIST* current = *head;
        while(current->next) current = current->next;
        current->next = insert;
    }

}

NODE* dequeue(LIST** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->data;

    LIST* newHead = ((*head)->next) ? (*head)->next : NULL;
    free(*head);
    *head = newHead;

    return result;
}

void push(LIST** head, NODE* toAdd){

    LIST* insert = calloc(1, sizeof(LIST));
    insert->data = toAdd;

    if (!*head){
        *head = insert;
    } else {
        insert->next = *head;
        *head = insert;
    }
}

NODE* pop(LIST** head){

    NODE* result = calloc(1, sizeof(NODE));
    result = (*head)->data;

    LIST* newHead = ((*head)->next) ? (*head)->next : NULL;
    *head = newHead;

    return result;
}

NODE* convIntNode(float input){
    NODE* result = calloc(1, sizeof(NODE));

    result->type = 4;
    result->num = input;

    return result;
}

NODE* convCharNode (char input){
    NODE* result = calloc(1, sizeof(NODE));

    switch (input) {
        case '=':
            result->type = 3;
            result->operate = '=';
            break;

        case '+':
            result->type = 6;
            result->operate = '+';
            break;

        case '-':
            result->type = 6;
            result->operate = '-';
            break;
        
        case '*':
            result->type = 7;
            result->operate = '*';
            break;
        
        case '/':
            result->type = 7;
            result->operate = '/';
            break;

        case '^':
            result->type = 8;
            result->operate = '^';
            break;
        
        case '(':
            result->type = 1;
            result->operate = '(';
            break;
        
        case ')':
            result->type = 2;
            result->operate = ')';
            break;
        
        default:
            result->type = 5;
            result->operate = input;
            break;
    }
    
    return result;
}

NODE* multNode(){

    NODE* result = calloc(1, sizeof(NODE));
    result->type = 7;
    result->operate = '*';
    return result;

}

NODE* zeroNode(){

    NODE* result = calloc(1, sizeof(NODE));
    result->type = 4;
    result->num = 0;
    return result;

}

int treeDepth(NODE* tree, int depth){
    if (!tree) return depth - 1;

    int l = treeDepth(tree->left, depth + 1);
    int r = treeDepth(tree->right, depth + 1);

    return (l > r) ? l : r;
}

void dispNode(NODE* toShow){
    if(!toShow)
        printf("[BLANK!]\n");

    else if (toShow->type == 4)
        printf("[%d (%d):%f |%d |%d ]\n", toShow, toShow->type, toShow->num, (toShow->left) ? toShow->left : NULL, (toShow->right) ? toShow->right : NULL);
    
    else
        printf("[%d (%d):%c |%d |%d ]\n", toShow, toShow->type, toShow->operate, (toShow->left) ? toShow->left : NULL, (toShow->right) ? toShow->right : NULL);

}

void dispList(LIST* root){
    if (!root){
        printf("EMPTY LIST!\n\n");
        return;
    }

    dispNode(root->data);
    dispList(root->next);

}

void dispLeaves(NODE* leaf, int depth){
    if(!leaf) return;

    dispLeaves(leaf->left, depth + 1);

    MOVEDOWN(depth);
    if (leaf->type == 4) printf("[%5.2f]", leaf->num);
    else printf("[%c]", leaf->operate);
    MOVEUP(depth);

    dispLeaves(leaf->right, depth + 1);
}

void dispTree(NODE* root){
    if (!root) return;

    int maxDepth = treeDepth(root, 1);
    for (int i = 0; i < maxDepth; i++) printf("\n");
    MOVEUP(maxDepth);

    dispLeaves(root, 1);
    MOVEDOWN(maxDepth);
    printf("\n");
}

LIST* nodify(char* input, int len){
    if (!len) return NULL;

    LIST* start = NULL;

    for (int i = 0; i < len; i++){
        if (isspace(input[i])) continue;

        if (isdigit(input[i])){
            char digits[6];
            memset(digits, '\0', 6);
            int j = 0;
            while (isdigit(input[i])) digits[j++] = input[i++];
            i--;
            NODE* toAdd = convIntNode(atof(digits));
            enqueue(&start, toAdd);
            continue;
        } else {
            NODE* toAdd = convCharNode(input[i]);
            enqueue(&start, toAdd);
        }

    }

    return start;

}

LIST* postify(LIST* inOrdered){
    if (!inOrdered) return NULL;

    LIST* result = NULL;
    LIST* stack = NULL;
    NODE* toAdd = NULL;
    NODE* curDat = NULL;
    int curType = 0, prevType = 0;

    do{
        curDat = dequeue(&inOrdered);
        curType = curDat->type;
        
        switch (curType) {
        case 1:
            if (prevType == 4 || prevType == 5 || prevType == 2) push(&stack, multNode());
            push(&stack, curDat);
            break;

        case 4:
            if (prevType == 5) push(&stack, multNode());
            enqueue(&result, curDat);
            break;
        
        case 5:
            if (prevType == 4 || prevType == 5 || prevType == 2) push(&stack, multNode());
            enqueue(&result, curDat);
            break;
        
        case 3:
        case 6:
        case 7:
        case 8:
            if (curDat->operate == '-' && !(prevType == 4 || prevType == 5 || prevType == 2)) enqueue(&result, zeroNode());
            if (stack)
                while (stack){
                if(curType > stack->data->type) {
                    push(&stack, curDat);
                    break;
                }
                else enqueue(&result, pop(&stack));
                }
            else push(&stack, curDat);
            break;

        case 2:
            while(stack->data->type != 1) enqueue(&result, pop(&stack));
            enqueue(&result, pop(&stack));
            
            LIST* toDel = result;
            LIST* prev = NULL;
            while (toDel->next){
                prev = toDel;
                toDel = toDel->next;
            }
            prev->next = NULL;
            free(toDel);

            break;

        default:
            break;
        }

        prevType = curType;

    } while (inOrdered);

    while(stack) enqueue(&result, pop(&stack));

    return result;

}

NODE* treefy(LIST* postordered){
    if (!postordered) return NULL;
    LIST* stack = NULL;

    while(postordered){
        NODE* current = pop(&postordered);

        if (current->type == 4 || current->type == 5) push(&stack, current);
        else {
            NODE* toRight = pop(&stack);
            NODE* toLeft = pop(&stack);

            NODE* toAdd = calloc(1, sizeof(NODE));
            toAdd->type = current->type;
            toAdd->operate = current->operate;

            toAdd->left = toLeft;
            toAdd->right = toRight;
            push(&stack, toAdd);
        }
    }
    return stack->data;
}

LIST* searchVar(LIST* root, char var){
    if (!root) return NULL;

    LIST* current = root;

    while(current){
        if (current->data->operate == var) return current;
        current = current->next;
    }

    return NULL;
}

NODE* substitute (NODE* root){
    if (!root) return NULL;

    NODE* current = NULL;
    LIST* line = NULL;
    LIST* dict = NULL;

    push(&line, root);

    while(line){
        current = pop(&line);

        if (current->left) push(&line, current->left);
        if (current->right) push(&line, current->right);

        if (current->type != 5) continue;

        char curVar = current->operate;

        LIST* toSubstitute = searchVar(dict, curVar);

        if (!toSubstitute){
            NODE* newEntry = calloc(1, sizeof(NODE));
            newEntry->operate = curVar;

            printf("Enter value of <%c>: ", curVar);
            scanf(" %f", &(newEntry->num));

            current->type = 4;
            current->num = newEntry->num;
            current->operate = '\0';

            push(&dict, newEntry);
        } else {
            current->type = 4;
            current->num = toSubstitute->data->num;
            current->operate = '\0';
        }
    }

    return root;
}

float evaluate(NODE* root){
    if (!root) return 0;
    if (root->type == 4) return root->num;

    if (root->operate == '+') return (evaluate(root->left) + evaluate(root->right));
    if (root->operate == '-') return (evaluate(root->left) - evaluate(root->right));
    if (root->operate == '*') return (evaluate(root->left) * evaluate(root->right));
    if (root->operate == '/') return (evaluate(root->left) / evaluate(root->right));
    if (root->operate == '^') return (pow(evaluate(root->left), evaluate(root->right)));
}

int main(){

    char* input = calloc(250, sizeof(char));

    printf("Enter expression: ");
    scanf(" %250[^\n]s", input);

    char* lhs = calloc(10, sizeof(char));
    strncpy(lhs, input, (strchr(input, '=') - input + 1));

    LIST* inordered = nodify(input, strlen(input));
    // printf("\nINORDERED:\n");
    // dispList(inordered);

    LIST* postordered = postify(inordered);
    // printf("\nPOSTORDERED:\n");
    // dispList(inordered);

    NODE* root = treefy(postordered);
    printf("\nExpression Tree:");
    dispTree(root);
    printf("\n");

    NODE* substituted = substitute(root->right);
    printf("\nSubstituted values:");
    dispTree(root);

    float answer = evaluate(root->right);
    printf("\n%s %3.2f\n", lhs, answer);

    return 0;
}