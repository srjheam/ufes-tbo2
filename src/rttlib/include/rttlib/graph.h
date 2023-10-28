#ifndef _RTTLIB_GRAPH_H_
#define _RTTLIB_GRAPH_H_

#define MAX_NODES 100

typedef struct Node {
    int id;
    int type;
} Node;

typedef struct Edge {
    int dest;
    double weight;
} Edge;

typedef struct Graph {
    int V;
    Node nodes[MAX_NODES];
    Edge* adjacency_list[MAX_NODES];
    int num_edges[MAX_NODES];
} Graph;

void initializeGraph(Graph* graph, int V);
void addEdge(Graph* graph, int src, int dest, double weight);
void freeGraph(Graph* graph);

int edge_greater(Edge* p, Edge* q);
void edge_exchange(Edge** p, Edge** q);
int graph_num_edges(Graph* graph);

#endif