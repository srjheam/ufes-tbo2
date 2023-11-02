#ifndef _RTTLIB_GRAPH_H_
#define _RTTLIB_GRAPH_H_

#include "containerslib/vector.h"

typedef struct Vertex {
    int id;
    double dist;
} Vertex;

typedef struct Edge {
    int id_dest;
    double weight;
} Edge;

typedef struct Graph {
    Vector **adjacency_list; // Vector<Edge>* vector sorted by id_dest
    size_t qtyVertices;
    size_t qtyEdges;
} Graph;

Graph *initializeGraph(int qtyVertices);
void addEdge(Graph* graph, int src, int dest, double weight);

Vector* graph_adj_vect(Graph* graph, int id);

void freeGraph(Graph* graph);

size_t graph_num_edges(Graph* graph);
size_t graph_num_vertices(Graph* graph);

int edge_dest(Edge *e);
double edge_weight(Edge *e);

int vertex_more(Vertex a, Vertex b);
void vertex_exch(Vertex* a, Vertex* b);
int vertex_id(Vertex v);
double vertex_dist(Vertex v);
void vertex_set_dist(Vertex* v, double dist);

#endif
