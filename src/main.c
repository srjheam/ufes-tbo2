#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "containerslib/heap.h"

#include "rttlib/fileOperations.h"
#include "rttlib/graph.h"
#include "rttlib/dijkstra.h"
#include "rttlib/rttInfo.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nome_arquivo_entrada> <nome_arquivo_saida>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    Graph *graph;
    int qtyS, qtyC, qtyM;
    int *arr_S_ids, *arr_C_ids, *arr_M_ids;

    if (readGraphFromFile(input_filename, &graph, &qtyS, &qtyC, &qtyM, &arr_S_ids, &arr_C_ids, &arr_M_ids) != 0) {
        perror("Erro ao ler o arquivo de entrada");
        return 1;
    }

    int qtyV = graph_num_vertices(graph);

    // contem todas as distancias a partir de todos os vertices S, C, M
    // matriz de dimensão |V| x |V|, onde distances[V] | V não pertence a S, C, M = NULL
    double **distances = calloc(qtyV, __SIZEOF_POINTER__);

    // para cada vertice S, C, M, calcula as distancias a partir dele
    for (int i = 0; i < qtyS; i++) {
        int src_id = arr_S_ids[i];
        distances[src_id] = malloc(qtyV * sizeof(double));
        dijkstra_dists(graph, src_id, distances[src_id]);
    }

    for (int i = 0; i < qtyC; i++) {
        int src_id = arr_C_ids[i];
        distances[src_id] = malloc(qtyV * sizeof(double));
        dijkstra_dists(graph, src_id, distances[src_id]);
    }

    for (int i = 0; i < qtyM; i++) {
        int src_id = arr_M_ids[i];
        distances[src_id] = malloc(qtyV * sizeof(double));
        dijkstra_dists(graph, src_id, distances[src_id]);
    }

    // TODO:
    //       um mesmo monitor será consultado/comparado várias vezes ao calcular o rtt star,
    //       então, precisamos pensar no jeito mais inteligente, tanto em complexidade de tempo,
    //       quanto de espaço para transformar essas dijkstra distances recebidas em outra estrutura
    //       que otimize as consultas para calcular a rtt star
    //
    //       a principio essa abordagem da matriz já funciona, mas é muito ineficiente em
    //       complexidade de tempo e eu também sindo que há margem para melhorias em complexidade
    //       de espaço
    //
    // TL;DR 
    //       1 - definir agora uma nova estrutura (RttInfo ?????) para armazenar as rtt que será passada
    //       como argumento para printRttRatioToFile; printRttRatioToFile será responsável APENAS por ler
    //       e imprimir essa estrutura sem jamais conter qualquer lógica de cálculo de rtt star
    //       2 - definir a camada que transpoem nossos dados crus em dijkstra distances e edges para
    //       essa nova estrutura RttInfo
    //
    freeGraph(graph);

    Heap *rttInfos = rttinfo_calc(distances, qtyS, qtyC, qtyM, arr_S_ids, arr_C_ids, arr_M_ids);

    free(arr_S_ids);
    free(arr_C_ids);
    free(arr_M_ids);
    for (int i = 0; i < qtyV; i++)
        if (distances[i])
            free(distances[i]);
    free(distances);

    FILE *output = fopen(output_filename, "w");
    printRttRatioToFile(output, rttInfos);
    fclose(output);

    heap_free(rttInfos);

    return 0;
}
