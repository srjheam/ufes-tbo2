#ifndef PQ_H
#define PQ_H

#include <stdbool.h>

#include "graph.h"

typedef struct pq PQ;

PQ* priority_queue_init(int maxN);
void priority_queue_insert(PQ* p, Vertex v);
Vertex priority_queue_delmin(PQ* p);
Vertex priority_queue_min(PQ* p);
void priority_queue_decrease_key(PQ* p, int id, double weight);
bool priority_queue_empty(PQ* p);
int priority_queue_size(PQ* p);
void priority_queue_finish(PQ* p);

#endif // !PQ_H
