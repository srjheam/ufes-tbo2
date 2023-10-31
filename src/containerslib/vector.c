#include <string.h>

#include "containerslib/exceptions.h"

#include "containerslib/vector.h"

#define VECTOR_INITIAL_SIZE 2
#define VECTOR_GROWTH_FACTOR 2

void __vector_resize(Vector *vector, size_t nsize) {
    vector->size = nsize;
    vector->arr = realloc(vector->arr, vector->size * vector->smemb);
}

void __vector_grow(Vector *vector) {
    if (vector->len + 1 >= vector->size) {
        __vector_resize(vector, vector->size << 1);
    }
}

void __vector_shrink(Vector *vector) {
    if (vector->size > VECTOR_INITIAL_SIZE &&
        vector->len <= 6 * (vector->size >> 4)) {
        __vector_resize(vector, vector->size >> 1);
    }
}

Vector *vector_constructor(size_t smemb, cmp_fn compar, free_fn destruct) {
    Vector *vector = malloc(sizeof *vector);

    vector->smemb = smemb;

    vector->compar = compar;
    vector->destruct = destruct;

    vector->size = VECTOR_INITIAL_SIZE;
    vector->len = 0;
    vector->arr = malloc(vector->size * smemb);

    return vector;
}

size_t vector_length(Vector *vector) { return vector->len; }

void *vector_index(Vector *vector, size_t idx) {
    return &vector->arr[idx * vector->smemb];
}

void vector_insert(Vector *vector, void *elem, size_t i) {
    if (i > vector->len)
        exception_throw_index("vector_insert");

    __vector_grow(vector);

    memmove(vector->arr + (i + 1) * vector->smemb,
            vector->arr + i * vector->smemb, (vector->len - i) * vector->smemb);
    memcpy(vector->arr + i * vector->smemb, elem, vector->smemb);

    vector->len++;
}

void vector_sorted_insert(Vector *vector, void *elem) {
    size_t i = vector_bsearch_nearest_i(vector, elem);
    vector_insert(vector, elem, i);
}

void vector_append(Vector *vector, void *elem) {
    vector_insert(vector, elem, vector->len);
}

void vector_remove(Vector *vector, size_t i) {
    if (i >= vector->len)
        exception_throw_index("vector_remove");

    //__vector_shrink(vector); TODO: add vector_shrink_to_fit function if necessary

    if (vector->destruct)
        vector->destruct(vector->arr + i * vector->smemb);

    memmove(vector->arr + i * vector->smemb,
            vector->arr + (i + 1) * vector->smemb,
            (vector->len - i - 1) * vector->smemb);

    vector->len--;
}

size_t vector_ptrtoindex(Vector *vector, void *ptr) {
    return ((byte *)ptr - vector->arr) / vector->smemb;
}

size_t vector_bsearch_nearest_i(Vector *v, void *key) {
    return ((byte *)vector_bsearch_nearest(v, key) -
            (byte *)vector_iterator_begin(v)) /
           v->smemb;
}

void *vector_bsearch_nearest(Vector *v, void *key) {
    if (v->len == 0)
        return v->arr;

    int l = 0;
    int r = v->len - 1;

    int cmp = 0;
    while (l <= r) {
        int m = l + (r - l) / 2;

        void *t = v->arr + m * v->smemb;

        cmp = v->compar(t, key);

        if (cmp < 0) {
            l = m + 1;
        } else if (cmp > 0) {
            r = m - 1;
        } else {
            return t;
        }
    }

    return v->arr + l * v->smemb;
}

void *vector_bsearch(Vector *vector, void *key) {
    return bsearch(key, vector->arr, vector->len, vector->smemb,
                   vector->compar);
}

void *vector_iterator_begin(Vector *vector) { return vector->arr; }

void *vector_iterator_forward(Vector *vector, void **saveptr) {
    if (vector->arr + vector->len * vector->smemb == *saveptr)
        return NULL;

    void *r = *saveptr;

    *saveptr = *(byte **)saveptr + vector->smemb;
    return r;
}

void vector_clear(Vector *vector) {
    for (void *it = vector_iterator_begin(vector); it;
         it = vector_iterator_forward(vector, &it))
        vector->destruct(it);

    vector->len = 0;
    __vector_resize(vector, VECTOR_INITIAL_SIZE);
}

void vector_destructor(Vector *vector) {
    if (vector->destruct != NULL)
        vector_clear(vector);

    free(vector->arr);

    free(vector);
}
