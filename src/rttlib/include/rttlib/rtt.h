#ifndef RTT_H
#define RTT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double rtt(double** distances, int a, int b);
double estimated_rtt_brute_force(double** distances, int qtdMonitors, int* idsM, int a, int b);
double** rtt_inflation_brute_force(double** distances, int qtdMonitors, int qtdClients, int qtdServers,
	int* idsM, int* idsC, int* idsS);

#endif // !RTT_H
