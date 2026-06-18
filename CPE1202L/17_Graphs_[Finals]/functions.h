#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    #define TEXT_RESET printf("\e[m")
    #define BOLD_TEXT printf("\e[1m")

    #define RED_TEXT printf("\e[31m")
    #define GREEN_TEXT printf("\e[32m")
    #define YELLOW_TEXT printf("\e[33m")
    #define BLUE_TEXT printf("\e[34m")

    #define CROSS_COLOR printf("\e[91m")
    #define ROW_COLOR printf("\e[46m")
    #define COL_COLOR printf("\e[48m")


    typedef struct graph {
        char vertexName;
        int edgeWeight;
        int visited;
        struct graph* nextVertex;
        struct graph* nextEdge;
    } GRAPH;

    typedef struct list {
        GRAPH* data;
        int priority;
        struct list* next;
    } LIST;

    // in add.c
    void addVertex(GRAPH** graph, char vertex, int* vertexCount);
    void addEdge(GRAPH** graph, char outbound, char inbound, int weight);

    // in display.c
    void ShowAdjList(GRAPH* graph, int vertexCount);
    void ShowAdjMatrix(GRAPH* graph, int vertexCount);

    // in traversal.c
    void zeroVisits(GRAPH* graph);
    void ShowCritPath(GRAPH* graph, int vertexCount);
    void ShowAllPath(GRAPH* graph, int vertexCount);



#endif // FUNCTIONS_H
