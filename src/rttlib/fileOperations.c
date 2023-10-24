#include <stdio.h>
#include "../include/rttlib/graph.h"

int readGraphFromFile(char *filename, Graph *graph, int *S, int *C, int *M) {
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    int V, E;
    fscanf(input_file, "%d %d", &V, &E);

    initializeGraph(graph, V);

    fscanf(input_file, "%d %d %d", S, C, M);

    for (int i = 0; i < *S; i++) {
        int server;
        fscanf(input_file, "%d", &server);
        graph->nodes[server].id = server;
        graph->nodes[server].type = 0;
    }

    for (int i = 0; i < *C; i++) {
        int client;
        fscanf(input_file, "%d", &client);
        graph->nodes[client].id = client;
        graph->nodes[client].type = 1;
    }

    for (int i = 0; i < *M; i++) {
        int monitor;
        fscanf(input_file, "%d", &monitor);
        graph->nodes[monitor].id = monitor;
        graph->nodes[monitor].type = 2;
    }

    for (int i = 0; i < E; i++) {
        int x, y;
        double weight;
        fscanf(input_file, "%d %d %lf", &x, &y, &weight);
        addEdge(graph, x, y, weight);
    }

    fclose(input_file);
    return 0;
}

void printGraphToFile(char *filename, Graph *graph) {
    FILE *output_file = fopen(filename, "w");
    if (output_file == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        fprintf(output_file, "Nó %d (Tipo: %d): ", graph->nodes[i].id, graph->nodes[i].type);
        for (int j = 0; j < graph->num_edges[i]; j++) {
            fprintf(output_file, "(Destino: %d, Peso: %.2lf) ", graph->adjacency_list[i][j].dest, graph->adjacency_list[i][j].weight);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
}
