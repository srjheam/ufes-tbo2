#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "graph.h"

typedef struct pq PQ;


static void swap(PQ* p, int i, int j);
static void fix_up(PQ* p, int k);
static void fix_down(PQ* p, int k);
PQ* priority_queue_init(int maxN);
void priority_queue_insert(PQ* p, Edge* v);
Edge* priority_queue_delmin(PQ* p);
Edge* priority_queue_min(PQ* p);
void priority_queue_decrease_key(PQ* p, int id, double weight);
bool priority_queue_empty(PQ* p);
int priority_queue_size(PQ* p);
void priority_queue_finish(PQ* p);
int priority_queue_contains(PQ* pq, int key);



#endif // !PQ_H
