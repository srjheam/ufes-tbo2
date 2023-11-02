#ifndef _CONTAINERSLIB_TRIHEAP_H_
#define _CONTAINERSLIB_TRIHEAP_H_


//
// Atenção
// ========
// 
// Este heap é um heap de três chaves (priority: double, id: int, data: any).
//
// Ele é pouco genérico e de propósito quase que totalmente específico, mas até que eficiente.
//

//
// ATENÇÃO #2
//
// ESTE TRIHEAP POSSUE UM BUG INDIAGNOSTICAVEL
// ISSO MESMO MEU BEBE ESTA DOENTE E NAO CONSIGO CURA-LO
//
// esse fato me forcou a usar o heap nao generico e chato que o professor deu
//
// make CFLAGS='-DRED_PILL'
//
// liberte-se da matrix, neo
// use esse meu heap trilegal
// os resultados podem parecer um pouco errados
// mas o que importa é a experiencia, a viagem
// e também de se gabar de ter uma super estrutura
// de dados, com bytes, totalmente generica
// e, o mais importante: completamente ilegivel :D
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
