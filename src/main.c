#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "containerslib/triheap.h"
#include "rttlib/graph.h"

// PODE APAGAR

typedef struct DummyVertex DummyVertex;

struct DummyVertex
{
    int id;
    int *adj_ids;
};

DummyVertex dummyvertex_create(int id, int *adj_ids)
{
    DummyVertex v;
    v.id = id;
    v.adj_ids = adj_ids;
    return v;
}

DummyVertex *dummyvertex_init(int id, int *adj_ids)
{
    DummyVertex *v = malloc(sizeof(DummyVertex));
    *v = dummyvertex_create(id, adj_ids);
    return v;
}

void dummyvertex_dispose(DummyVertex *data)
{
    free(data->adj_ids);
}

void dummyvertex_free(DummyVertex *data)
{
    dummyvertex_dispose(data);
    free(data);
}

int dummyvertex_idselecter(DummyVertex *data)
{
    return data->id;
}

// PODE APAGAR


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nome_arquivo_entrada> <nome_arquivo_saida>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // PODE APAGAR

    TriHeap *heap = triheap_init(MIN_HEAP, 10, sizeof(DummyVertex), (free_fn)dummyvertex_dispose, (idselect_fn)dummyvertex_idselecter);

    for (size_t i = 0; i < 10; i++)
    {
        int *adj_ids = malloc(sizeof(int) * 2);
        adj_ids[0] = (10 + i - 1) % 10;
        adj_ids[1] = (i + 1) % 10;
        DummyVertex v = dummyvertex_create(i, adj_ids);
        triheap_push(heap, &v, 10 - i - 1);
    }

    triheap_update_by_id(heap, 5, __DBL_MAX__);
    
    // o correto seria passar o dado real para assegurar o funcionamento da função,
    // mas nesse snippet tudo ocorrerá bem porque sabemos o conteúdo do dado e como
    // a função de idselecter funciona
    DummyVertex fst = dummyvertex_create(0, NULL);
    triheap_update(heap, &fst, 0);
    
    printf("id: p\n");
    for (size_t i = 0; i < 10; i++)
    {
        DummyVertex v;
        double p = triheap_pop(heap, &v);
        printf("%d: %lf\n", v.id, p);
        dummyvertex_dispose(&v);
    }

    triheap_free(heap);

    // PODE APAGAR

    return EXIT_SUCCESS;
}
