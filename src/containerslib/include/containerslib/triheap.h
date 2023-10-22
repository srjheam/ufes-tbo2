#ifndef _CONTAINERSLIB_TRIHEAP_H_
#define _CONTAINERSLIB_TRIHEAP_H_


//
// Atenção
// ========
// 
// Este heap é um heap de três chaves (priority: double, id: int, data: any).
//
// Ele é pouco genérico e de propósito específico, mas até que eficiente.
//


#include <stdlib.h>
#include <stdbool.h>

#include "containerslib/types.h"

typedef struct TriHeap TriHeap;

typedef int (*idselect_fn)(void *);

enum HeapType {
    MIN_HEAP,
    MAX_HEAP
};

/***
 * @brief Initializes a new TriHeap.
 * 
 * @param type The type of the heap.
 * @param fixedCapacity The fixed capacity of the heap. If the heap is full and
 * a new element is pushed, an exception is thrown. Heap members' id must be in [0, fixedCapacity) range.
 * @param smemb The size of the members of the heap.
 * @param freer The function used to free the members of the heap.
 * @param idselecter The function used to select the id of the members of the heap.
 * 
 * @return TriHeap* The new TriHeap.
 */
TriHeap *triheap_init(enum HeapType type, size_t fixedCapacity, size_t smemb, free_fn freer, idselect_fn idselecter);

void triheap_push(TriHeap *self, void *data, double priority);

double triheap_pop(TriHeap *self, void *out);

double triheap_peek(TriHeap *self, void *out);

void triheap_update(TriHeap *self, void *data, double priority);

void triheap_update_by_id(TriHeap *self, int id, double priority);

size_t triheap_len(TriHeap *self);

void triheap_free(TriHeap *self);

#endif
