#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "rttlib/rtt.h"

double rtt(double** distances, int a, int b) {
	double* distance_a = distances[a];
	double* distance_b = distances[b];
	return distance_a[b] + distance_b[a];
}

double estimated_rtt_brute_force(double** distances, int qtdMonitors, int* idsM, int a, int b) {
	double min = rtt(distances, a, idsM[0]) + rtt(distances, idsM[0], b);
	for (int i = 1; i < qtdMonitors; i++) {
		double rtt_temp = rtt(distances, a, idsM[i]) + rtt(distances, idsM[i], b);
		if (rtt_temp < min) {
			min = rtt_temp;
		}
	}
	return min;
}

/* double** rtt_inflation_brute_force(double** distances, int qtdMonitors, int qtdClients, int qtdServers,
	int* idsM, int* idsC, int* idsS) {
	int k = 0;

	for (int i = 0; i < qtdServers; i++) {
		for (int j = 0; j < qtdClients; j++) {
			const int s_id = idsS[i];
			const int c_id = idsC[j];
			const double original_rtt = rtt(distances, s_id, c_id);
			const double estimated_rtt = estimated_rtt_brute_force(distances, qtdMonitors, idsM, s_id, c_id);
			const double inflation = estimated_rtt / original_rtt;
		}
	}
} */