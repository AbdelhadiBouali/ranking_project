#ifndef SALSA_H
#define SALSA_H

#include "graph.h"

void salsaAlgorithm(Graph* graph, int num_iterations);
void writeScoresToFile(Graph* graph, const char* filename_hub, const char* filename_autorite);

#endif

