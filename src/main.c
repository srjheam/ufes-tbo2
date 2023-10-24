#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "containerslib/triheap.h"
#include "rttlib/fileOperations.h"
#include "rttlib/graph.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nome_arquivo_entrada> <nome_arquivo_saida>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    Graph graph;
    int S, C, M;

    if (readGraphFromFile(input_filename, &graph, &S, &C, &M) != 0) {
        return 1;
    }

    printf("S = %d | C = %d | M = %d \n", S, C, M);

    printGraphToFile(output_filename, &graph);

    freeGraph(&graph);

    return 0;
}
