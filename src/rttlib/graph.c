#include <stdio.h>
#include <stdlib.h>

#include "rttlib/graph.h"
#include "containerslib/linked_list.h"

int __graph_adj_vect_edge_cmp(Edge* p, Edge* q) {
    return edge_dest(p) - edge_dest(q);
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

Vector* graph_adj_vect(Graph* graph, int id) {
    return graph->adjacency_list[id];
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

int edge_dest(Edge *e) { return e->id_dest; }
double edge_weight(Edge *e) { return e->weight; }

int vertex_more(Vertex a, Vertex b) {
    return a.dist > b.dist;
}

void vertex_exch(Vertex* a, Vertex* b) {
    Vertex t = *a;
    *a = *b;
    *b = t;
}

int vertex_id(Vertex v) { return v.id; }

double vertex_dist(Vertex v) { return v.dist; }

void vertex_set_dist(Vertex* v, double dist) { v->dist = dist; }
