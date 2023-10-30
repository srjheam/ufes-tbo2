#include <stdio.h>
#include <stdlib.h>

#include "rttlib/graph.h"
#include "containerslib/linked_list.h"

Graph *initializeGraph(int qtyVertices) {
    Graph *graph = malloc(sizeof(Graph));

    graph->qtyEdges = 0;
    graph->qtyVertices = qtyVertices;
    
    graph->adjacency_list = malloc(sizeof(__SIZEOF_POINTER__) * qtyVertices);
    for (size_t i = 0; i < qtyVertices; i++)
        graph->adjacency_list[i] = vector_constructor(sizeof(Edge), graph_edge_cmp, NULL);

    return graph;
}

void addEdge(Graph* graph, int src, int dest, double weight) {
    Edge new_edge = { .id_src = src, .id_dest = dest, .weight = weight };
    vector_append(graph->adjacency_list[src], &new_edge);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->qtyVertices; i++) {
        vector_destructor(graph->adjacency_list[i]);
    }

    free(graph);
}

int graph_edge_cmp(Edge* p, Edge* q) {
    if (p->id_src == q->id_src && p->id_dest == q->id_dest)
        return 0;
    else return -1;
}

size_t graph_num_edges(Graph* graph) {
    return graph->qtyEdges;
}

size_t graph_num_vertices(Graph* graph) {
    return graph->qtyVertices;
}
