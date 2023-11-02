#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "rttlib/graph.h"
#include "rttlib/pq.h"

int __idselecter(int *id) {
	return *id;
}

void dijkstra_dists(Graph* graph, int src_id, double *out_dists) {
	size_t qtyV = graph_num_vertices(graph);

	for (size_t i = 0; i < qtyV; i++)
		out_dists[i] = INFINITY;

	out_dists[src_id] = 0;

	PQ *pq = priority_queue_init(qtyV);
	for (size_t i = 0; i < qtyV; i++)
			priority_queue_insert(pq, (Vertex){i, out_dists[i]});

	while (!priority_queue_empty(pq)) {
		Vertex curr_v = priority_queue_delmin(pq);

		Vector *adj_vect = graph->adjacency_list[curr_v.id];

		void *save_ptr = vector_iterator_begin(adj_vect);
		Edge *curr_edge;
		while ((curr_edge = vector_iterator_forward(adj_vect, &save_ptr)) != NULL)
		{
			int v_id = curr_edge->id_dest;

			double t_dist = curr_v.dist + curr_edge->weight;
			if (out_dists[v_id] > t_dist) {
				out_dists[v_id] = t_dist;
				priority_queue_decrease_key(pq, v_id, t_dist);
			}
		}
	}

	priority_queue_finish(pq);
}
