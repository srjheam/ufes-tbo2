#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BLUE_PILL
#ifdef RED_PILL
#undef BLUE_PILL
#endif

#ifdef RED_PILL
#include "containerslib/triheap.h"
#endif
#ifdef BLUE_PILL
#include "rttlib/pq.h"
#endif

#include "rttlib/graph.h"

#ifdef RED_PILL
int __idselecter(int *id) {
	return *id;
}
#endif

void dijkstra_dists(Graph* graph, int src_id, double *out_dists) {
	size_t qtyV = graph_num_vertices(graph);

	for (size_t i = 0; i < qtyV; i++)
		out_dists[i] = INFINITY;

	out_dists[src_id] = 0;

	#ifdef BLUE_PILL
	PQ *pq = priority_queue_init(qtyV);
	#endif
	#ifdef RED_PILL
	TriHeap *pq = triheap_init(MIN_HEAP, qtyV, sizeof(int), NULL, (idselect_fn)__idselecter);
	#endif
	for (size_t i = 0; i < qtyV; i++)
		#ifdef BLUE_PILL
		priority_queue_insert(pq, (Vertex){i, out_dists[i]});
		#endif
		#ifdef RED_PILL
		triheap_push(pq, &i, out_dists[i]);
		#endif

	while (
		#ifdef BLUE_PILL
		!priority_queue_empty(pq)
		#endif
		#ifdef RED_PILL
		triheap_len(pq) > 0
		#endif
		) {
		#ifdef BLUE_PILL
		Vertex curr_v = priority_queue_delmin(pq);
		#endif
		#ifdef RED_PILL
		int curr_id;
		double dist = triheap_pop(pq, &curr_id);
		#endif

		Vector *adj_vect = graph_adj_vect(graph,
			#ifdef BLUE_PILL
			vertex_id(curr_v)
			#endif
			#ifdef RED_PILL
			curr_id
			#endif
		);

		void *save_ptr = vector_iterator_begin(adj_vect);
		Edge *curr_edge;
		while ((curr_edge = vector_iterator_forward(adj_vect, &save_ptr)) != NULL)
		{
			int v_id = edge_dest(curr_edge);

			double t_dist =
				#ifdef BLUE_PILL
				vertex_dist(curr_v)
				#endif
				#ifdef RED_PILL
				dist
				#endif
				+ edge_weight(curr_edge);
			if (out_dists[v_id] > t_dist) {
				out_dists[v_id] = t_dist;
				#ifdef BLUE_PILL
				priority_queue_decrease_key(pq, v_id, t_dist);
				#endif
				#ifdef RED_PILL
				triheap_update_by_id(pq, v_id, t_dist);
				#endif
			}
		}
	}

	#ifdef BLUE_PILL
	priority_queue_finish(pq);
	#endif
	#ifdef RED_PILL
	triheap_free(pq);
	#endif
}
