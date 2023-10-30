#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rttlib/graph.h"
#include "rttlib/pq.h"

double *dijkstra_dists(Graph* graph, int src_id) {
	//
	// eu não trabalhei com a implementacao do dijkstra, mas farei isso hoje
	// a noite porque é bem facil e também porque minhas mudancas no grafo e
	// e em outros trechos do programa quebraram totalmente essa implementacao
	//

	int amount_vertices = graph_vertices(graph);
	double* distance = malloc(sizeof(double) * amount_vertices);
	int* visited = malloc(sizeof(int) * amount_vertices);

	for (int i = 0; i < amount_vertices; i++) {
		distance[i] = 1000; //INFINITY;
		visited[i] = 0;
	}

	distance[src_id] = 0.0;
	PQ* pq = priority_queue_init(amount_vertices);
	Edge* new_node = vertex_new(src_id);
	new_node->weight = 0.0;

	priority_queue_insert(pq, new_node);

	while (!priority_queue_empty(pq)) {
		Edge* current = priority_queue_delmin(pq);
		int index = current->id;
		visited[index] = 1;

		double new_weight;
		Edge* temp = graph_get_vertex(graph, index);

		while (temp) {
			if (visited[temp->id] == 0) {
				new_weight = distance[index] + temp->weight;
				if (new_weight < distance[temp->id]) {
					distance[temp->id] = new_weight;
					if (priority_queue_contains(pq, temp->id)) {
						priority_queue_decrease_key(pq, temp->id, new_weight);
					}
					else {
						Edge* new_node = vertex_new(temp->id);
						new_node->weight = new_weight;
						priority_queue_insert(pq, new_node);
					}
				}
			}
			temp = temp->next;
		}
		if (current) {
			free(current);
		}
	}

	free(visited);
	priority_queue_finish(pq);
	return distance;
}
