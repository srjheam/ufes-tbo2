#ifndef _RTTLIB_FILE_OPERATIONS_H_
#define _RTTLIB_FILE_OPERATIONS_H_

#include "graph.h"

int readGraphFromFile(char *filename, Graph *graph, int *S, int *C, int *M);
void printGraphToFile(char *filename, Graph *graph);


#endif