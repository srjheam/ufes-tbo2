#ifndef _RTTLIB_DIJKSTRA_H_
#define _RTTLIB_DIJKSTRA_H_

#include "rttlib/graph.h"

/// @brief Algoritmo de dijskstra com resultado em vetor de distâncias; um resultado completo teria mais atributos, como a arvore de caminhos mínimos, mas não é necessário para o RTT
/// @param graph
/// @param src
/// @return Um vetor com dimensao |V| com as distâncias de src_id para cada vértice
double *dijkstra_dists(Graph *graph, int src_id);

#endif