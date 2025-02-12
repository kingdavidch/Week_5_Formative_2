#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices (cities) in the graph

// Function to implement the Bellman-Ford Algorithm for finding the shortest paths
void BellmanFord(int graph[V][V], int src) {
    int dist[V]; // Array to store the shortest distance from the source to all cities

    // Step 1: Initialize distances from source to all other vertices as INFINITY
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX; // Set all distances to a very high value (infinity)
    dist[src] = 0; // Distance from source city to itself is 0

    // Step 2: Relax all edges V-1 times (Bellman-Ford property)
    for (int i = 1; i <= V - 1; i++) { // Loop runs V-1 times
        for (int u = 0; u < V; u++) { // Iterate over all cities (vertices)
            for (int v = 0; v < V; v++) { // Check connections with other cities
                // If there is a path from u to v and updating dist[v] gives a shorter path
                if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v]; // Update shortest distance to city v
            }
        }
    }

    // Step 3: Print the shortest path from the source to all other cities
    for (int i = 0; i < V; i++) {
        if (dist[i] != INT_MAX)
            printf("Shortest distance from city %d to city %d is %d\n", src, i, dist[i]);
        else
            printf("Shortest distance from city %d to city %d is INF (No path exists)\n", src, i);
    }
}

// Main function
int main() {
    // Graph represented as an adjacency matrix
    // If there is no direct path between two cities, the value is 0
    int graph[V][V] = { {0, 10, 0, 30, 100},  // City 0 connections
                        {10, 0, 50, 0, 0},    // City 1 connections
                        {0, 50, 0, 20, 10},   // City 2 connections
                        {30, 0, 20, 0, 60},   // City 3 connections
                        {100, 0, 10, 60, 0} }; // City 4 connections

    BellmanFord(graph, 0); // Run Bellman-Ford starting from city 0

    return 0;
}
