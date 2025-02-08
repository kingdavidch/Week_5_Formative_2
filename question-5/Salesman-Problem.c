#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices in the graph

void BellmanFord(int graph[V][V], int src) {
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] != INT_MAX)
            printf("Distance from city %d to city %d is %d\n", src, i, dist[i]);
        else
            printf("Distance from city %d to city %d is INF\n", src, i);
    }
}

int main() {
    int graph[V][V] = { {0, 10, 0, 30, 100},
                        {10, 0, 50, 0, 0},
                        {0, 50, 0, 20, 10},
                        {30, 0, 20, 0, 60},
                        {100, 0, 10, 60, 0} };

    BellmanFord(graph, 0); // Starting from city A (index 0)

    return 0;
}
