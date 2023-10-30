#ifndef _RTTLIB_RTTINFO_H_
#define _RTTLIB_RTTINFO_H_

#include "containerslib/heap.h"

typedef struct RttInfo
{
    int s_id;
    int c_id;
} RttInfo;

Heap *rttinfo_calc(double **distances, int qtyS, int qtyC, int qtyM, int *arr_S_ids, int *arr_C_ids, int *arr_M_ids);

#endif
