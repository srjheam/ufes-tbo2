#include "rttlib/rttInfo.h"

double __rtt(double **distances, int a, int b) {
    return distances[a][b] + distances[b][a];
}

Heap *rttinfo_calc(double **distances, int qtyS, int qtyC, int qtyM, int *arr_S_ids, int *arr_C_ids, int *arr_M_ids) {
    Heap *rttInfos = heap_init(MIN_HEAP, qtyS * qtyC, sizeof(RttInfo), NULL);

    for (int i = 0; i < qtyS; i++)
    {
        int server_id = arr_S_ids[i];
        for (int j = 0; j < qtyC; j++)
        {
            int client_id = arr_C_ids[j];

            double rtt = __rtt(distances, server_id, client_id);

            double rtt_star = __DBL_MAX__;
            for (int k = 0; k < qtyM; k++)
            {
                int monitor_id = arr_M_ids[k];

                double rtt_m = __rtt(distances, server_id, monitor_id) + __rtt(distances, monitor_id, client_id);
                if (rtt_m < rtt_star)
                    rtt_star = rtt_m;
            }

            RttInfo rttInfo = {.c_id = server_id, .s_id = client_id};

            heap_push(rttInfos, &rttInfo, (rtt_star / rtt));
        }
    }    

    return rttInfos;
}
