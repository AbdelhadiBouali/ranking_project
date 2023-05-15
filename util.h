#ifndef UTIL_H
#define UTIL_H

#include "graph.h"

int readGraphFile(const char* filename, Graph* graph);
int parseInt(char* str);
void writeScoresToFile(const char* filename, double* scores, int num_nodes);

#endif  // UTIL_H

