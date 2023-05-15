#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_nodes = 0;
    graph->nodes = NULL;
    return graph;
}

void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    Node* current = graph->nodes;
    while (current != NULL) {
        Node* next = current->next;
        Edge* edge = current->outgoing_edges;
        while (edge != NULL) {
            Edge* next_edge = edge->next;
            free(edge);
            edge = next_edge;
        }
        free(current);
        current = next;
    }

    free(graph);
}

Node* addNode(Graph* graph, int id) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->score_hub = 0.0;
    node->score_autorite = 0.0;
    node->outgoing_edges = NULL;
    node->incoming_edges = NULL;
    node->next = NULL;

    if (graph->nodes == NULL) {
        graph->nodes = node;
    } else {
        Node* current = graph->nodes;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    graph->num_nodes++;
    return node;
}

Edge* addEdge(Node* source, Node* target) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->target = target;
    edge->next = NULL;

    if (source->outgoing_edges == NULL) {
        source->outgoing_edges = edge;
    } else {
        Edge* current = source->outgoing_edges;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = edge;
    }

    if (target->incoming_edges == NULL) {
        target->incoming_edges = edge;
    } else {
        Edge* current = target->incoming_edges;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = edge;
    }

    return edge;
}

void calculateOutDegrees(Graph* graph) {
    Node* current = graph->nodes;
    while (current != NULL) {
        int out_degree = 0;
        Edge* edge = current->outgoing_edges;
        while (edge != NULL) {
            out_degree++;
            edge = edge->next;
        }
        current->out_degree = out_degree;
        current = current->next;
    }
}

void calculateInDegrees(Graph* graph) {
    Node* current = graph->nodes;
    while (current != NULL) {
        int in_degree = 0;
        Edge* edge = current->incoming_edges;
        while (edge != NULL) {
            in_degree++;
            edge = edge->next;
        }
        current->in_degree = in_degree;
        current = current->next;
    }
}

void calculateInitialScores(Graph* graph) {
    double initial_score = 1.0 / graph->num_nodes;
    Node* current = graph->nodes;
    while (current != NULL) {
        current->score_hub = initial_score;
        current->score_autorite = initial_score;
        current = current->next;
    }
}

void normalizeScores(Graph* graph, int type) {
    double sum = 0.0;
    Node* current = graph->nodes;
    while (current != NULL) {
        if (type == 1) {
            sum += current->score_hub * current->score_hub;
        } else if (type == 2) {
            sum += current->score_autorite * current->score_autorite;
        }
        current = current->next;
    }

    double norm = sqrt(sum);
    if (norm > 0.0) {
        current = graph->nodes;
        while (current != NULL) {
            if (type == 1) {
                current->score_hub /= norm;
            } else if (type == 2) {
                current->score_autorite /= norm;
            }
            current = current->next;
        }
    }
}

void updateScores(Graph* graph, int type) {
    Node* current = graph->nodes;
    while (current != NULL) {
        double score = 0.0;
        Edge* edge = (type == 1) ? current->incoming_edges : current->outgoing_edges;
        while (edge != NULL) {
            Node* neighbor = edge->target;
            score += (type == 1) ? neighbor->score_autorite : neighbor->score_hub;
            edge = edge->next;
        }

        if (type == 1) {
            current->score_hub = score;
        } else if (type == 2) {
            current->score_autorite = score;
        }

        current = current->next;
    }
}

