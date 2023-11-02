#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rttlib/graph.h"
#include "rttlib/pq.h"

struct pq {
    Vertex *array;
    int* map;
    int n, size;
};

static int vertex_more(Vertex a, Vertex b) {
    return a.dist > b.dist;
}

static void vertex_exch(Vertex* a, Vertex* b) {
    Vertex t = *a;
    *a = *b;
    *b = t;
}

static int vertex_id(Vertex v) { return v.id; }

static void swap(PQ* p, int i, int j) {
    vertex_exch(&p->array[i], &p->array[j]);
    p->map[vertex_id(p->array[i])] = i;
    p->map[vertex_id(p->array[j])] = j;
}

static void fix_up(PQ* p, int k) {
    while (k > 1 && vertex_more(p->array[k / 2], p->array[k])) {
        swap(p, k, k / 2);
        k = k / 2;
    }
}

static void fix_down(PQ* p, int k) {
    while (2 * k <= p->n) {
        int j = 2 * k;
        if (j < p->n && vertex_more(p->array[j], p->array[j + 1])) {
            j++;
        }
        if (!vertex_more(p->array[k], p->array[j])) {
            break;
        }
        swap(p, k, j);
        k = j;
    }
}

PQ* priority_queue_init(int maxN) {
    PQ* pq = malloc(sizeof(PQ));
    pq->array = calloc((maxN + 1), sizeof(Vertex));
    pq->map = malloc((maxN + 1) * sizeof(int));
    pq->n = 0;
    pq->size = maxN;
    return pq;
}

void priority_queue_insert(PQ* p, Vertex v) {
    p->n++;
    p->array[p->n] = v;
    p->map[vertex_id(v)] = p->n;
    fix_up(p, p->n);
}

Vertex priority_queue_delmin(PQ* p) {
    Vertex min = p->array[1];
    swap(p, 1, p->n);
    p->n--;
    fix_down(p, 1);
    return min;
}

Vertex priority_queue_min(PQ* p) { return p->array[1]; }

void priority_queue_decrease_key(PQ* p, int id, double weight) {
    int i = p->map[id];
    p->array[i].dist = weight;
    fix_up(p, i);
}

bool priority_queue_empty(PQ* p) { return p->n == 0; }

int priority_queue_size(PQ* p) { return p->size; }

void priority_queue_finish(PQ* p) {
    free(p->array);
    free(p->map);
    free(p);
}
