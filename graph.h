#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node Node;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Node {
    int id;
    double score_hub;
    double score_autorite;
    Edge* outgoing_edges;
    Edge* incoming_edges;
    struct Node* next;
};

struct Edge {
    Node* target;
    struct Edge* next;
};

struct Graph {
    int num_nodes;
    Node* nodes;
};

Graph* createGraph();
void freeGraph(Graph* graph);
Node* addNode(Graph* graph, int id);
Edge* addEdge(Node* source, Node* target);
void calculateOutDegrees(Graph* graph);
void calculateInDegrees(Graph* graph);
void calculateInitialScores(Graph* graph);
void normalizeScores(Graph* graph, int type);
void updateScores(Graph* graph, int type);

#endif

