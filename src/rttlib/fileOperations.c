#include <stdio.h>

#include "containerslib/exceptions.h"
#include "containerslib/heap.h"

#include "rttlib/graph.h"
#include "rttlib/rttInfo.h"

int readGraphFromFile(char *filename, Graph **graph, int *qtyS, int *qtyC, int *qtyM, int **arr_S_ids, int **arr_C_ids, int **arr_M_ids) {
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    int qtyV, qtyE;
    fscanf(input_file, "%d %d", &qtyV, &qtyE);

    *graph = initializeGraph(qtyV);

    fscanf(input_file, "%d %d %d", qtyS, qtyC, qtyM);

    *arr_S_ids = malloc(sizeof(int) * *qtyS);
    *arr_C_ids = malloc(sizeof(int) * *qtyC);
    *arr_M_ids = malloc(sizeof(int) * *qtyM);

    for (int i = 0; i < *qtyS; i++) {
        int server_id;
        fscanf(input_file, "%d", &server_id);
        (*arr_S_ids)[i] = server_id;
    }

    for (int i = 0; i < *qtyC; i++) {
        int client_id;
        fscanf(input_file, "%d", &client_id);
        (*arr_C_ids)[i] = client_id;
    }

    for (int i = 0; i < *qtyM; i++) {
        int monitor_id;
        fscanf(input_file, "%d", &monitor_id);
        (*arr_M_ids)[i] = monitor_id;
    }

    for (int i = 0; i < qtyE; i++) {
        int src_id, src_dest;
        double weight;
        fscanf(input_file, "%d %d %lf", &src_id, &src_dest, &weight);
        addEdge(graph, src_id, src_dest, weight);
    }

    fclose(input_file);
    return 0;
}

void printRttRatioToFile(FILE *output_file, Heap *rttInfos) {
    RttInfo rttInfo;
    while (heap_len(rttInfos) > 0)
    {
        double ratio = heap_pop(rttInfos, &rttInfo);
        printf("%d %d %.16lf\n", rttInfo.c_id, rttInfo.s_id, ratio);
    }
}

void printGraphToFile(char *filename, Graph *graph) {
    exception_throw_failure("Not implemented - printGraphToFile");
    return;

    // TODO: Implementar isso depois das mudancas q fiz no grafo

    /* FILE *output_file = fopen(filename, "w");
    if (output_file == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    for (int i = 0; i < graph->qtyVertices; i++) {
        fprintf(output_file, "Nó %d (Tipo: %d): ", graph->nodes[i].id, graph->nodes[i].type);
        for (int j = 0; j < graph->qtyEdges[i]; j++) {
            fprintf(output_file, "(Destino: %d, Peso: %.2lf) ", graph->adjacency_list[i][j].dest, graph->adjacency_list[i][j].weight);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file); */
}
