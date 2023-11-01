#include <stdio.h>
#include <stdlib.h>

#include "rttlib/graph.h"
#include "containerslib/linked_list.h"

int __graph_adj_vect_edge_cmp(Edge* p, Edge* q) {
    return p->id_dest - q->id_dest;
}

Graph *initializeGraph(int qtyVertices) {
    Graph *graph = malloc(sizeof(Graph));

    graph->qtyEdges = 0;
    graph->qtyVertices = qtyVertices;
    
    graph->adjacency_list = malloc(__SIZEOF_POINTER__ * qtyVertices);
    for (int i = 0; i < qtyVertices; i++)
        graph->adjacency_list[i] = vector_constructor(sizeof(Edge), (cmp_fn)__graph_adj_vect_edge_cmp, NULL);

    return graph;
}

void addEdge(Graph* graph, int src, int dest, double weight) {
    Edge new_edge = { .id_dest = dest, .weight = weight };
    vector_append(graph->adjacency_list[src], &new_edge);
}

void freeGraph(Graph* graph) {
    for (size_t i = 0; i < graph->qtyVertices; i++)
        vector_destructor(graph->adjacency_list[i]);
    free(graph->adjacency_list);

    free(graph);
}

size_t graph_num_edges(Graph* graph) {
    return graph->qtyEdges;
}

size_t graph_num_vertices(Graph* graph) {
    return graph->qtyVertices;
}
