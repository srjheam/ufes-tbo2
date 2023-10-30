#ifndef _RTTLIB_GRAPH_H_
#define _RTTLIB_GRAPH_H_

#include "containerslib/vector.h"

typedef struct Vertex {
    int id;
} Vertex;

typedef struct Edge {
    int id_src;
    int id_dest;
    double weight;
} Edge;

typedef struct Graph {
    Vector **adjacency_list; // Vector<Edge>*
    size_t qtyVertices;
    size_t qtyEdges;
} Graph;

Graph *initializeGraph(int qtyVertices);
void addEdge(Graph* graph, int src, int dest, double weight);
void freeGraph(Graph* graph);

int graph_edge_cmp(Edge* p, Edge* q);

size_t graph_num_edges(Graph* graph);
size_t graph_num_vertices(Graph* graph);

#endif