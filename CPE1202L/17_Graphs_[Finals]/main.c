#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "functions.h"

int main(){

    char* string = calloc(500, sizeof(char));
    char* single = calloc(25, sizeof(char));

    GRAPH* graph = NULL;
    int vertexCount = 0;

    system("cls");
    printf("Input a String: ");

    BOLD_TEXT;
    scanf(" %250[^\n]s", string);
    TEXT_RESET;
    printf("\n");



    do{
        single = strtok(vertexCount ? NULL : string, ", ");
        char outbound = toupper(single[0]);
        char inbound = toupper(single[1]);
        int weight = atoi(single + 2);

        printf("Outbound: %c\tInbound: %c\tWeight: %d\n", outbound, inbound, weight);

        addVertex(&graph, outbound, &vertexCount);
        addVertex(&graph, inbound, &vertexCount);
        addEdge(&graph, outbound, inbound, weight);
    } while(!strchr(single, '!'));

    printf("Vertex count: %d\n", vertexCount);
    printf("\n");

    ShowAdjMatrix(graph, vertexCount);
    ShowAdjList(graph, vertexCount);

    // Warning!
    // ShowCritPath() and ShowAllPath() prints plausible but random path(s)
    // Such functions are just for show and help sell the illusion that the code did something 😅
    // Do not use code as reference!

    ShowCritPath(graph, vertexCount);
    ShowAllPath(graph, vertexCount);

    GREEN_TEXT;
    printf("Ran Succesfully!");
    TEXT_RESET;
    return 0;
}
