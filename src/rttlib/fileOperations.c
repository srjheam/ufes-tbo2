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
    if(fscanf(input_file, "%d %d", &qtyV, &qtyE)){};

    *graph = initializeGraph(qtyV);

    if(fscanf(input_file, "%d %d %d", qtyS, qtyC, qtyM)){};

    *arr_S_ids = malloc(sizeof(int) * *qtyS);
    *arr_C_ids = malloc(sizeof(int) * *qtyC);
    *arr_M_ids = malloc(sizeof(int) * *qtyM);

    for (int i = 0; i < *qtyS; i++) {
        int server_id;
        if(fscanf(input_file, "%d", &server_id)){};
        (*arr_S_ids)[i] = server_id;
    }

    for (int i = 0; i < *qtyC; i++) {
        int client_id;
        if(fscanf(input_file, "%d", &client_id)){};
        (*arr_C_ids)[i] = client_id;
    }

    for (int i = 0; i < *qtyM; i++) {
        int monitor_id;
        if(fscanf(input_file, "%d", &monitor_id)){};
        (*arr_M_ids)[i] = monitor_id;
    }

    for (int i = 0; i < qtyE; i++) {
        int src_id, src_dest;
        double weight;
        if(fscanf(input_file, "%d %d %lf", &src_id, &src_dest, &weight)){};
        addEdge(*graph, src_id, src_dest, weight);
    }

    fclose(input_file);
    return 0;
}

void printRttRatioToFile(FILE *output_file, Heap *rttInfos) {
    RttInfo rttInfo;
    while (heap_len(rttInfos) > 0)
    {
        double ratio = heap_pop(rttInfos, &rttInfo);
        fprintf(output_file, "%d %d %.16lf\n", rttInfo.s_id, rttInfo.c_id, ratio);
    }
}
