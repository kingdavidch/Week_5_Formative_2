
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int vertices;
    int adjMatrix[MAX][MAX];
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

void BFS(Graph* graph, int start, int contactTimes[]) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int maxContactTime = -1;
    int mostAtRisk = -1;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("Visited %d\n", current);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
                if (contactTimes[i] > maxContactTime) {
                    maxContactTime = contactTimes[i];
                    mostAtRisk = i;
                }
            }
        }
    }

    if (mostAtRisk != -1) {
        printf("Most at risk person: %d with contact time: %d\n", mostAtRisk, maxContactTime);
    } else {
        printf("No one is at risk.\n");
    }
}

int main() {
    Graph* graph = createGraph(5);

    // Add edges
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 20);
    addEdge(graph, 1, 3, 30);
    addEdge(graph, 2, 4, 40);

    int contactTimes[] = {0, 15, 25, 35, 45};

    int start = 0; // Suspected person
    BFS(graph, start, contactTimes);

    return 0;
}
