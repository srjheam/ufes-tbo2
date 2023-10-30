#ifndef _RTTLIB_FILE_OPERATIONS_H_
#define _RTTLIB_FILE_OPERATIONS_H_

#include <stdlib.h>

#include "rttlib/graph.h"

int readGraphFromFile(char *filename, Graph **graph, int *qtyS, int *qtyC, int *qtyM, int **arr_S_ids, int **arr_C_ids, int **arr_M_ids);
void printGraphToFile(char *filename, Graph *graph);

void printRttRatioToFile(FILE *output_file, Heap *rttInfos);

#endif