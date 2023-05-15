#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readGraphFile(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    char line[256];
    int num_nodes = 0;
    int num_edges = 0;

    // Read the number of nodes and edges
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d %d", &num_nodes, &num_edges);
    }

    *graph = createGraph(num_nodes);

    // Read the edges
    while (fgets(line, sizeof(line), file) != NULL) {
        int from_node = -1;
        int to_node = -1;
        sscanf(line, "%d %d", &from_node, &to_node);
        addEdge(graph, from_node, to_node);
    }

    fclose(file);
    return 1;
}

int parseInt(char* str) {
    return atoi(str);
}

void writeScoresToFile(const char* filename, double* scores, int num_nodes) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    for (int i = 0; i < num_nodes; i++) {
        fprintf(file, "%d %.6lf\n", i, scores[i]);
    }

    fclose(file);
}

