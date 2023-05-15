#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "salsa.h"

void salsaAlgorithm(Graph* graph, int num_iterations) {
    calculateOutDegrees(graph);
    calculateInDegrees(graph);
    calculateInitialScores(graph);

    for (int i = 0; i < num_iterations; i++) {
        updateScores(graph, 1);  // Update hub scores
        updateScores(graph, 2);  // Update authority scores
        normalizeScores(graph, 1);  // Normalize hub scores
        normalizeScores(graph, 2);  // Normalize authority scores
    }
}

void writeScoresToFile(Graph* graph, const char* filename_hub, const char* filename_authority) {
    FILE* file_hub = fopen(filename_hub, "w");
    FILE* file_authority = fopen(filename_authority, "w");

    if (file_hub == NULL || file_authority == NULL) {
        printf("Error opening output files.\n");
        return;
    }

    Node* current = graph->nodes;

    // Write hub scores to file
    fprintf(file_hub, "Node ID\tHub Score\n");
    while (current != NULL) {
        fprintf(file_hub, "%d\t%f\n", current->id, current->score_hub);
        current = current->next;
    }
    fclose(file_hub);

    current = graph->nodes;

    // Write authority scores to file
    fprintf(file_authority, "Node ID\tAuthority Score\n");
    while (current != NULL) {
        fprintf(file_authority, "%d\t%f\n", current->id, current->score_authority);
        current = current->next;
    }
    fclose(file_authority);
}


