#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "salsa.h"

int main() {
    // Création du graphe
    Graph* graph = createGraph();

    // Chargement du graphe à partir du fichier "wb-cs-stanford"
    if (!loadGraphFromFile(graph, "wb-cs-stanford")) {
        printf("Erreur lors du chargement du graphe.\n");
        return 1;
    }

    // Exécution de l'algorithme SALSA
    salsaAlgorithm(graph);

    // Écriture des scores des hubs dans un fichier
    if (!printScores(graph, "hubs.txt", HUB)) {
        printf("Erreur lors de l'écriture des scores des hubs.\n");
    }

    // Écriture des scores des autorités dans un fichier
    if (!printScores(graph, "autorites.txt", AUTORITE)) {
        printf("Erreur lors de l'écriture des scores des autorités.\n");
    }

    // Libération de la mémoire du graphe
    freeGraph(graph);

    return 0;
}

