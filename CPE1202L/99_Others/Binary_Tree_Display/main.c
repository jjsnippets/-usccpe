// integer binary tree display
// can be modified to display leaves with non-integers (see Expression Tree, Trie) and general trees (see Heap, Trie)
//      although the latter can certainly be made more human readable

#include <stdio.h>

// ANSI escape codes for cursor movement
//      if it does not display properly in terminal, check https://superuser.com/a/1300251/1706673 
#define MOVE_UP(x) printf("\e[%dA", x)
#define MOVE_DOWN(x) printf("\e[%dB", x)
#define MOVE_LEFT(x) printf("\e[%dD", x)

// structure used
typedef struct node {
    int x;
    struct node* left;
    struct node* right;
} NODE;

// support funtion
// determines the depth of the tree (recursively)
int treeDepth(NODE* root, int depth){
    if (!root) return depth - 1;

    int dLeft = treeDepth(root->left, depth + 1);
    int dRight = treeDepth(root->right, depth + 1);

    return (dLeft > dRight) ? dLeft : dRight;
}

// support function; should not be called directly
// prints individual leaves of the tree (recursive, inorder traversal)
void showLeaves(NODE* root, int depth){
    if (!root) return;

    // left subtree, if any
    showLeaves(root->left, depth + 1);

    // main driver of the function (and the tree-printing process)
    // precondition: treeDisplay() and recursive calls of showLeaves() assure that the cursor is always at the top of the tree 
    MOVE_DOWN(depth); // moves the cursor down to the depth of the current node
    printf("[%3d]", root->x); // prints the current node's value
    MOVE_UP(depth); // moves the cursor back up to the top of the tree (acts as a reset)
    MOVE_LEFT(1); // moves the cursor to the left by 1; for human readability, can be omitted

    // right subtree, if any
    showLeaves(root->right, depth + 1);
}

// main function for printing the tree
//      acts as a set-up for the recursive function showLeaves()
void treeDisplay(NODE* root){
    if (!root) return;

    // determines and "allocates" the vertical space needed for the tree
    int maxDepth = treeDepth(root, 1);
    for (int i = 0; i < maxDepth; i++) printf("\n");
    MOVE_UP(maxDepth); // moves the cursor to the top of the tree (root node level)

    // prints the leaves of the tree, inorder traversal
    showLeaves(root, 1);

    // postcondition: moves the cursor to the very bottom, ready for the next output
    MOVE_DOWN(maxDepth);
    printf("\n");
}

// sample initialization values
NODE l5 = {5, NULL, NULL};
NODE l1 = {1, NULL, NULL};
NODE l4 = {4, NULL, &l5};
NODE l7 = {7, NULL, NULL};
NODE l2 = {2, &l1, NULL};
NODE l6 = {6, &l4, &l7};
NODE l3 = {3, &l2, &l6};

void main (){
    // fixes some bug where escape sequence does not display properly sometimes without clearing the screen initially
    system("cls"); // can be ommited

    // [... code ...]

        // prints the tree
        treeDisplay(&l3); // call treeDisplay() on root node

            // sample output
            //          [  3]
            //      [  2]           [  6]
            //  [  1]       [  4]       [  7]
            //                  [  5]
            //

    // [... code ...]
}