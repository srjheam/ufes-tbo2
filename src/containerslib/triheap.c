#include <string.h>

#include "containerslib/exceptions.h"
#include "containerslib/triheap.h"

struct TriHeap {
    int *map;
    byte *data;
    double *priorities;
    size_t capacity;
    size_t len;
    size_t smemb;
    free_fn freer;
    idselect_fn idselecter;

    enum HeapType type;
};

void __triheap_grow(TriHeap *heap) {
    if (heap->len + 1 == heap->capacity) {
        exception_throw_oom("triheap_grow - TriHeap is full and uninplemented to grow its capacity");
        /*
        heap->capacity <<= 1;
        heap->data = realloc(heap->data, heap->smemb * heap->capacity);
        heap->priorities =
            realloc(heap->priorities, sizeof(double) * heap->capacity);
        */
    }
}

double __triheap_cmp(TriHeap *heap, double a, double b) { return heap->type == MAX_HEAP ? a - b : b - a; }

void __triheap_swap(TriHeap *map, size_t i, size_t j) {
    if (i > map->len || j > map->len)
        exception_throw_index("triheap_swap - Index out of bounds");

    int id_i = map->idselecter(map->data + i * map->smemb);
    int id_j = map->idselecter(map->data + j * map->smemb);

    map->map[id_i] = j;
    map->map[id_j] = i;

    memcpy(map->data, map->data + i * map->smemb, map->smemb);
    memcpy(map->data + i * map->smemb, map->data + j * map->smemb, map->smemb);
    memcpy(map->data + j * map->smemb, map->data, map->smemb);

    map->priorities[0] = map->priorities[i];
    map->priorities[i] = map->priorities[j];
    map->priorities[j] = map->priorities[0];
}

/**
 * @brief Returns the diff priority of the child with the highest priority; if
 * the result is negative, the left child has the highest priority; if the
 * result is positive, the right child has the highest priority; if the result
 * is zero, the children have less priority than the parent.
 *
 * @param heap The heap.
 * @param i The index of the parent.
 * @return double
 */
double __triheap_heapify_high(TriHeap *heap, size_t i) {
    size_t lindx = 2 * i;
    size_t rindx = 2 * i + 1;

    // I love Linux file permissions.
    int bits = 0b01 * (lindx > heap->len) + 0b10 * (rindx > heap->len);
    switch (bits) {
    case 0b01:;
        double rdiff =
            __triheap_cmp(heap, heap->priorities[rindx], heap->priorities[i]);
        return rdiff > 0 ? rdiff : 0;

    case 0b10:;
        double ldiff =
            __triheap_cmp(heap, heap->priorities[lindx], heap->priorities[i]);
        return ldiff > 0 ? ldiff * -1 : 0;

    case 0b11:
        return 0;
    }

    double pp = heap->priorities[i];
    double pl = heap->priorities[lindx];
    double pr = heap->priorities[rindx];

    double ldiff = __triheap_cmp(heap, pl, pp);
    double rdiff = __triheap_cmp(heap, pr, pp);

    int bits2 = 0b01 * (ldiff <= 0) + 0b10 * (rdiff <= 0);
    switch (bits2) {
    case 0b01:
        return rdiff;

    case 0b10:
        return ldiff * -1;

    case 0b11:
        return 0;
    }

    return ldiff < rdiff ? rdiff : ldiff * -1;
}

void __triheap_heapify_up(TriHeap *heap, size_t i) {
    if (heap->len == 1 || i == 0)
        return;

    size_t icurr = i >> 1;
    while (__triheap_heapify_high(heap, icurr)) {
        size_t ichild =
            2 * icurr + (__triheap_heapify_high(heap, icurr) < 0 ? 0 : 1);

        __triheap_swap(heap, icurr, ichild);

        if (icurr == 1)
            break;
        icurr >>= 1;
    }
}

void __triheap_heapify_down(TriHeap *heap) {
    size_t icurr = 1;
    while (__triheap_heapify_high(heap, icurr)) {
        size_t ichild =
            2 * icurr + (__triheap_heapify_high(heap, icurr) < 0 ? 0 : 1);

        __triheap_swap(heap, icurr, ichild);

        icurr = ichild;
    }
}

void __triheap_push(TriHeap *heap, void *data, double priority) {
    __triheap_grow(heap);

    heap->priorities[heap->len + 1] = priority;
    memcpy(heap->data + (heap->len + 1) * heap->smemb, data, heap->smemb);
    heap->map[heap->idselecter(data)] = heap->len + 1;
    heap->len++;

    __triheap_heapify_up(heap, heap->len);
}

double __triheap_peek(TriHeap *heap, byte *out) {
    if (heap->len == 0)
        exception_throw_failure("triheap_peek - Heap is empty");

    memcpy(out, heap->data + heap->smemb, heap->smemb);

    return heap->priorities[1];
}

double __triheap_pop(TriHeap *heap, byte *out) {
    if (heap->len == 0)
        exception_throw_failure("triheap_pop - Heap is empty");

    double spriority = heap->priorities[1];

    memcpy(out, heap->data + heap->smemb, heap->smemb);

    if (heap->len == 1) {
        heap->len--;
        return spriority;
    }

    // place the last element in the root
    __triheap_swap(heap, 1, heap->len);
    heap->len--;

    __triheap_heapify_down(heap);

    return spriority;
}

void __triheap_update_by_id(TriHeap *heap, int id, double priority) {
    if (id < 0 || (size_t)id >= heap->capacity)
        exception_throw_index("triheap_update_by_id - Id out of bounds");

    int i = heap->map[id];
    if (i == 0)
        exception_throw_index("triheap_update_by_id - Id not found");

    double oldpriority = heap->priorities[i];
    if (oldpriority == priority)
        return;

    heap->priorities[i] = priority;

    if (__triheap_cmp(heap, priority, oldpriority) > 0)
        __triheap_heapify_up(heap, i);
    else
        __triheap_heapify_down(heap);
}

TriHeap *triheap_init(enum HeapType type, size_t fixedCapacity, size_t smemb, free_fn freer, idselect_fn idselecter) {
    TriHeap *heap = malloc(sizeof *heap);

    heap->smemb = smemb;
    heap->freer = freer;
    heap->idselecter = idselecter;
    heap->type = type;

    heap->capacity = fixedCapacity + 1;
    heap->len = 0;
    heap->data = malloc(heap->smemb * heap->capacity);
    heap->priorities = malloc(sizeof(double) * heap->capacity);
    heap->map = calloc(heap->capacity, sizeof(int));

    return heap;
}

void triheap_push(TriHeap *self, void *data, double priority) {
    __triheap_push(self, data, priority);
}

double triheap_pop(TriHeap *self, void *out) {
    return __triheap_pop(self, out);
}

double triheap_peek(TriHeap *self, void *out) {
    return __triheap_peek(self, out);
}

void triheap_update(TriHeap *self, void *data, double priority) {
    triheap_update_by_id(self, self->idselecter(data), priority);
}

void triheap_update_by_id(TriHeap *self, int id, double priority) {
    return __triheap_update_by_id(self, id, priority);
}

size_t triheap_len(TriHeap *self) {
    return self->len;
}

void triheap_free(TriHeap *self) {
    if (self->freer)
        for (size_t i = 1; i <= self->len; i++)
            self->freer(((byte **)self->data)[i * self->smemb]);

    free(self->map);
    free(self->data);
    free(self->priorities);
    free(self);
}
