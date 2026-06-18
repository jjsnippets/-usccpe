#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

void ShowAdjList(GRAPH* graph, int vertexCount){
    RED_TEXT;
    printf("Adjacency List:\n");
    TEXT_RESET;

    char* vertexList = calloc(vertexCount + 1, sizeof(char));

    {
        GRAPH* currentVertex = graph;
        for(int i = 0; i < vertexCount; i++){
            vertexList[i] = currentVertex->vertexName;
            currentVertex = currentVertex->nextVertex;
        }
    }

    GRAPH* currentVertex = graph;
    while (currentVertex){
        printf("{%c}", currentVertex->vertexName);
        BOLD_TEXT;
        printf(" >> ");
        TEXT_RESET;

        GRAPH* currentEdge = currentVertex->nextEdge;
        while (currentEdge){
            printf("[%c <%d>] -> ", currentEdge->vertexName, currentEdge->edgeWeight);
            currentEdge = currentEdge->nextEdge;
        }
        currentVertex = currentVertex->nextVertex;
        printf("\b\b\b\b    \n");
    }
    printf("\n");
}

void ShowAdjMatrix(GRAPH* graph, int vertexCount){
    GREEN_TEXT;
    printf("Adjacency Matrix:\n");
    TEXT_RESET;

    char* vertexList = calloc(vertexCount + 1, sizeof(char));

    {
        printf("   ");
        GRAPH* currentVertex = graph;
        ROW_COLOR;
        for(int i = 0; i < vertexCount; i++){
            printf("%3c ", currentVertex->vertexName);
            vertexList[i] = currentVertex->vertexName;
            currentVertex = currentVertex->nextVertex;
        }
        TEXT_RESET;
        printf("\n");
    }

    GRAPH* currentVertex = graph;
    while (currentVertex){
        ROW_COLOR;
        printf("%2c ", currentVertex->vertexName);
        TEXT_RESET;

        GRAPH* currentEdge = currentVertex->nextEdge;
        for(int i = 0; i <= vertexCount; i++){
            if (currentEdge && currentEdge->vertexName == vertexList[i]){
                BOLD_TEXT;
                printf("%3d ", currentEdge->edgeWeight);
                TEXT_RESET;
                currentEdge = currentEdge->nextEdge;
            } else{
                CROSS_COLOR;
                printf("  * ");
                TEXT_RESET;
            }
        }
        currentVertex = currentVertex->nextVertex;
        printf("\b\b\b\b    \n");
    }
    printf("\n");
}

