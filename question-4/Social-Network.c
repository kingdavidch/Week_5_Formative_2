#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum number of vertices in the graph

// Graph structure using an adjacency matrix
typedef struct {
    int vertices; // Number of vertices in the graph
    int adjMatrix[MAX][MAX]; // Adjacency matrix to store edge weights
} Graph;

// Function to create a new graph with a given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // Allocate memory for the graph
    graph->vertices = vertices; // Set the number of vertices

    // Initialize the adjacency matrix with 0s (no connections initially)
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;

    return graph;
}

// Function to add an edge between two vertices with a specified weight
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight; // Set weight for src to dest
    graph->adjMatrix[dest][src] = weight; // Set weight for dest to src (Undirected graph)
}

// Breadth-First Search (BFS) to traverse the graph and find the most at-risk person
void BFS(Graph* graph, int start, int contactTimes[]) {
    int visited[MAX] = {0}; // Array to track visited nodes (0 = unvisited, 1 = visited)
    int queue[MAX]; // Queue for BFS traversal
    int front = 0, rear = 0; // Queue pointers
    int maxContactTime = -1; // To track the person with the highest contact time
    int mostAtRisk = -1; // Stores the index of the most at-risk person

    visited[start] = 1; // Mark the start node as visited
    queue[rear++] = start; // Enqueue the start node

    // BFS traversal
    while (front < rear) {
        int current = queue[front++]; // Dequeue the current node
        printf("Visited %d\n", current); // Print the visited node

        // Check all possible connections
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[current][i] && !visited[i]) { // If connected and not visited
                visited[i] = 1; // Mark as visited
                queue[rear++] = i; // Enqueue the node
                
                // Track the most at-risk person based on contact time
                if (contactTimes[i] > maxContactTime) {
                    maxContactTime = contactTimes[i];
                    mostAtRisk = i;
                }
            }
        }
    }

    // Output the most at-risk person
    if (mostAtRisk != -1) {
        printf("Most at risk person: %d with contact time: %d\n", mostAtRisk, maxContactTime);
    } else {
        printf("No one is at risk.\n");
    }
}

// Main function
int main() {
    Graph* graph = createGraph(5); // Create a graph with 5 nodes

    // Add edges (connections) between people with a weight representing interaction strength
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 20);
    addEdge(graph, 1, 3, 30);
    addEdge(graph, 2, 4, 40);

    // Contact times for each individual (indexed by person ID)
    int contactTimes[] = {0, 15, 25, 35, 45};

    int start = 0; // The person suspected of spreading an infection
    BFS(graph, start, contactTimes); // Run BFS to analyze risk

    return 0;
}
