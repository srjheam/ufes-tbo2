#include "rttlib/rttInfo.h"

Heap *rttinfo_calc(double **distances, int qtyS, int qtyC, int qtyM, int *arr_S_ids, int *arr_C_ids, int *arr_M_ids) {
    Heap *rttInfos = heap_init(MIN_HEAP, qtyS * qtyC, sizeof(RttInfo), NULL);

    RttInfo rttInfo;
    for (size_t i = 0; i < qtyS; i++)
    {
        int src_id = arr_S_ids[i];
        for (size_t j = 0; j < qtyC; j++)
        {
            int dest_id = arr_C_ids[j];

            double rtt = distances[src_id][dest_id];

            double rtt_star = __DBL_MAX__;
            for (size_t k = 0; k < qtyM; k++)
            {
                int monitor_id = arr_M_ids[k];

                double rtt_m = distances[src_id][monitor_id] + distances[monitor_id][dest_id];
                if (rtt_m < rtt_star)
                    rtt_star = rtt_m;
            }

            RttInfo rttInfo = {.c_id = src_id, .s_id = dest_id};

            heap_push(rttInfos, &rttInfo, rtt_star / rtt);
        }
    }    

    return rttInfos;
}
