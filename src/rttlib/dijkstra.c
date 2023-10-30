#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "rttlib/graph.h"

#include "containerslib/triheap.h"

int __idselecter(int *id) {
	return *id;
}

void dijkstra_dists(Graph* graph, int src_id, double *out_dists) {
	size_t qtyV = graph_num_vertices(graph);

	TriHeap *pq = triheap_init(MIN_HEAP, qtyV, sizeof(int), NULL, (idselect_fn)__idselecter);
	for (size_t i = 0; i < qtyV; i++)
			triheap_push(pq, &i, i == src_id ? 0 : __DBL_MAX__); // TODO: trocar por INFINITY		

	while (!triheap_is_empty(pq)) {
		int curr_id;
		double dist = triheap_pop(pq, &curr_id);

		Vector *adj_vect = graph->adjacency_list[curr_id];

		vector_iterator_begin(adj_vect);

		for (int *i = vector_iterator_begin(adj_vect); i != NULL; i = vector_iterator_forward(adj_vect, (void **)&i)) {
			Edge *edge = vector_at(adj_vect, i);
			int v_id = edge->id_dest;

			if (out_dists[v_id] > out_dists[curr_id] + edge->weight) {
				out_dists[v_id] = out_dists[curr_id] + edge->weight;
				triheap_update_key(pq, &v_id);
			}
		}
	}

	triheap_destructor(pq);
}
