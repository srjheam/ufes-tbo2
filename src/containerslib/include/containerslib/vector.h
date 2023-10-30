#ifndef _VECTOR_H_
#define _VECTOR_H_

// stolen from
// https://github.com/srjheam/ufes-csci/blob/dbc4c0b9e87dde27a2be233daf57db55fec9d9b4/csci/dsa/include/dsa/vector.h

#include "containerslib/types.h"

typedef struct Vector {
    byte *arr;

    size_t len;
    size_t size;

    cmp_fn compar;
    free_fn destruct;

    size_t smemb;
} Vector;

Vector *vector_constructor(size_t smemb, cmp_fn compar, free_fn destruct);

size_t vector_length(Vector *vector);

void *vector_index(Vector *vector, size_t idx);

void vector_insert(Vector *vector, void *elem, size_t i);

void vector_append(Vector *vector, void *elem);

void vector_remove(Vector *vector, size_t i);

size_t vector_ptrtoindex(Vector *vector, void *ptr);

size_t vector_bsearch_nearest_i(Vector *v, void *key);

void *vector_bsearch_nearest(Vector *vector, void *key);

void *vector_bsearch(Vector *vector, void *key);

void *vector_iterator_begin(Vector *vector);

void *vector_iterator_forward(Vector *vector, void **saveptr);

void vector_clear(Vector *vector);

void vector_destructor(Vector *vector);

#endif
