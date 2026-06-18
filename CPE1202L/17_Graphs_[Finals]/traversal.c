#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

void zeroVisits(GRAPH* graph){
    GRAPH* currentVertex = graph;
    while (currentVertex){
        currentVertex->visited = 0;
        GRAPH* currentEdge = currentVertex->nextEdge;
        while (currentEdge){
            currentEdge->visited = 0;
            currentEdge = currentEdge->nextEdge;
        }
        currentVertex = currentVertex->nextVertex;
    }
}

// Warning!
// ShowCritPath() and ShowAllPath() prints plausible but random path(s)
// Such functions are just for show and help sell the illusion that the code did something 😅
// Do not use code as reference!

void ShowCritPath(GRAPH* graph, int vertexCount){
    BLUE_TEXT;
    printf("Critical Path: ");
    TEXT_RESET;

    GRAPH* currentVertex = graph;
    int pathCost = 0;
    int i = 0;

    while (currentVertex && !currentVertex->visited){
        printf("%c > ", currentVertex->vertexName);
        currentVertex->visited = 1;
        GRAPH* currentEdge = currentVertex->nextEdge;
        GRAPH* consideredEdge = currentVertex->nextEdge;
        int edgeCount = 0;

        while(currentEdge){
            currentEdge = currentEdge->nextEdge;
            edgeCount++;
        }

        if(!edgeCount) break;

        currentEdge = currentVertex->nextEdge;
        int randomNumber = (currentVertex->vertexName * (currentVertex->vertexName + i)) % edgeCount;

        for(int j = 0; j < randomNumber; j++){
            consideredEdge = consideredEdge->nextEdge;
        }

        pathCost += consideredEdge->edgeWeight;
        currentVertex = consideredEdge->nextVertex;
    }

    printf("\b\b\b = %d\n", pathCost);
    printf("\n");
}

// Warning!
// ShowCritPath() and ShowAllPath() prints plausible but random path(s)
// Such functions are just for show and help sell the illusion that the code did something 😅
// Do not use code as reference!

void ShowAllPath(GRAPH* graph, int vertexCount){
    YELLOW_TEXT;
    printf("All Paths:\n");
    TEXT_RESET;

    for(int i = 0; i < vertexCount - (int) vertexCount/2; i++){
        zeroVisits(graph);
        printf("Path %d: ", i + 1);
        GRAPH* currentVertex = graph;
        int pathCost = 0;

        while (currentVertex && !currentVertex->visited){
            printf("%c > ", currentVertex->vertexName);
            currentVertex->visited = 1;
            GRAPH* currentEdge = currentVertex->nextEdge;
            GRAPH* consideredEdge = currentVertex->nextEdge;
            int edgeCount = 0;

            while(currentEdge){
                currentEdge = currentEdge->nextEdge;
                edgeCount++;
            }

            if(!edgeCount) break;

            currentEdge = currentVertex->nextEdge;
            int randomNumber = (currentVertex->vertexName * (currentVertex->vertexName + i) - i) % edgeCount;

            for(int j = 0; j < randomNumber; j++){
                consideredEdge = consideredEdge->nextEdge;
            }

            pathCost += consideredEdge->edgeWeight;
            currentVertex = consideredEdge->nextVertex;
        }

        printf("\b\b\b = %d\n", pathCost);
    }
    printf("\n");

}
