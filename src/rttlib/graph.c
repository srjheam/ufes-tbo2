#include <stdio.h>
#include <stdlib.h>
#include "../include/rttlib/graph.h"

void initializeGraph(Graph* graph, int V) {
    graph->V = V;
    for (int i = 0; i < V; i++) {
        graph->adjacency_list[i] = (Edge*)malloc(V * sizeof(Edge));
        graph->num_edges[i] = 0;
        graph->nodes[i].id = i;
        graph->nodes[i].type = -1; // -1 para nós "Outros"
    }
}

void addEdge(Graph* graph, int src, int dest, double weight) {
    Edge new_edge = {dest, weight};
    graph->adjacency_list[src][graph->num_edges[src]++] = new_edge;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->adjacency_list[i]);
    }
}

int edge_greater(Edge* p, Edge* q) {
    return p->weight > q->weight;
}

void edge_exchange(Edge** p, Edge** q) {
    Edge* temp = *p;
    *p = *q;
    *q = temp;
}

int graph_num_edges(Graph* graph) {
    return graph->num_edges;
}