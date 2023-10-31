#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "containerslib/triheap.h"

#include "rttlib/graph.h"

int __idselecter(int *id) {
	return *id;
}

void dijkstra_dists(Graph* graph, int src_id, double *out_dists) {
	size_t qtyV = graph_num_vertices(graph);

	for (size_t i = 0; i < qtyV; i++)
		out_dists[i] = INFINITY;

	out_dists[src_id] = 0;

	TriHeap *pq = triheap_init(MIN_HEAP, qtyV, sizeof(int), NULL, (idselect_fn)__idselecter);
	for (size_t i = 0; i < qtyV; i++)
			triheap_push(pq, &i, out_dists[i]);

	while (triheap_len(pq) > 0) {
		int curr_id;
		double dist = triheap_pop(pq, &curr_id);

		Vector *adj_vect = graph->adjacency_list[curr_id];

		void *save_ptr = vector_iterator_begin(adj_vect);
		Edge *curr_edge;
		while ((curr_edge = vector_iterator_forward(adj_vect, &save_ptr)) != NULL)
		{
			int v_id = curr_edge->id_dest;

			double t_dist = dist + curr_edge->weight;
			if (out_dists[v_id] > t_dist) {
				out_dists[v_id] = t_dist;
				triheap_update_by_id(pq, v_id, t_dist);
			}
		}
	}

	triheap_free(pq);
}
