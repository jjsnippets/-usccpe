#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

void addVertex(GRAPH** graph, char vertex, int* vertexCount){

    GRAPH* newNode = calloc(1, sizeof(GRAPH));
    newNode->vertexName = vertex;

    if (!*graph){
        *graph = newNode;
        (*vertexCount)++;
        return;
    }

    GRAPH** currentVertex = graph;
    while (*currentVertex && (*currentVertex)->vertexName <= vertex){
        if((*currentVertex)->vertexName == vertex) return;
        currentVertex = &(*currentVertex)->nextVertex;
    }

    if(!*currentVertex){
        *currentVertex = newNode;

    } else {
        GRAPH* temp = *currentVertex;
        *currentVertex = newNode;
        newNode->nextVertex = temp;
    }

    (*vertexCount)++;
}


void addEdge(GRAPH** graph, char outbound, char inbound, int weight){
    GRAPH* currentVertex = *graph;
    while (currentVertex->vertexName != outbound){
        currentVertex = currentVertex->nextVertex;
    }

    GRAPH* nodeTo = *graph;
    while (nodeTo->vertexName != inbound){
        nodeTo = nodeTo->nextVertex;
    }

    GRAPH* newNode = calloc(1, sizeof(GRAPH));
    newNode->vertexName = inbound;
    newNode->edgeWeight = weight;
    newNode->nextVertex = nodeTo;


    GRAPH** currentEdge = &(currentVertex->nextEdge);
    if (!*currentEdge){
        *currentEdge = newNode;
        return;
    }

    while (*currentEdge && (*currentEdge)->vertexName <= inbound){
        if((*currentEdge)->vertexName == inbound) return;
        currentEdge = &((*currentEdge)->nextEdge);
    }

    if(!*currentEdge){
        *currentEdge = newNode;

    } else {
        GRAPH* temp = *currentEdge;
        *currentEdge = newNode;
        newNode->nextEdge = temp;
    }

}
