#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent an edge in the graph
typedef struct {
    int src;    // Source vertex of the edge
    int dest;   // Destination vertex of the edge
    int weight; // Weight of the edge
} Edge;

// Define a structure to represent the graph
typedef struct {
    int V;      // Number of vertices in the graph
    int E;      // Number of edges in the graph
    Edge* edge; // Array of edges in the graph
} Graph;

// Function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph)); // Allocate memory for the graph
    graph->V = V; // Set the number of vertices
    graph->E = E; // Set the number of edges
    graph->edge = (Edge*)malloc(graph->E * sizeof(Edge)); // Allocate memory for the edges
    return graph; // Return the created graph
}

// Define a structure to represent a subset for union-find operations
typedef struct {
    int parent; // Parent of the subset
    int rank;   // Rank of the subset (used for union by rank)
} Subset;

// Function to find the root of a subset (with path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) // If the current node is not the root
        subsets[i].parent = find(subsets, subsets[i].parent); // Recursively find the root and apply path compression
    return subsets[i].parent; // Return the root of the subset
}

// Function to perform union of two subsets (with union by rank)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x); // Find the root of the subset containing x
    int yroot = find(subsets, y); // Find the root of the subset containing y

    // Attach the smaller rank tree under the root of the higher rank tree
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot; // Make yroot the parent of xroot
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot; // Make xroot the parent of yroot
    else {
        subsets[yroot].parent = xroot; // If ranks are the same, make one the parent of the other
        subsets[xroot].rank++;         // Increment the rank of the new root
    }
}

// Comparator function to sort edges by weight (used by qsort)
int compare(const void* a, const void* b) {
    Edge* a1 = (Edge*)a; // Cast the first edge
    Edge* b1 = (Edge*)b; // Cast the second edge
    return a1->weight > b1->weight; // Compare the weights of the edges
}

// Function to construct and print the MST using Kruskal's algorithm
void KruskalMST(Graph* graph) {
    int V = graph->V; // Number of vertices in the graph
    Edge result[V];   // Array to store the edges of the MST
    int e = 0;        // Index variable for the result array
    int i = 0;        // Index variable for the sorted edges array

    // Step 1: Sort all edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    // Allocate memory for subsets (one for each vertex)
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));

    // Initialize subsets (each vertex is its own parent and has rank 0)
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v; // Set the parent of each vertex to itself
        subsets[v].rank = 0;   // Set the rank of each vertex to 0
    }

    // Step 2: Iterate through all sorted edges and add them to the MST if they don't form a cycle
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++]; // Pick the smallest edge

        int x = find(subsets, next_edge.src);  // Find the root of the subset containing src
        int y = find(subsets, next_edge.dest); // Find the root of the subset containing dest

        if (x != y) { // If src and dest are in different subsets, no cycle is formed
            result[e++] = next_edge; // Add the edge to the MST
            Union(subsets, x, y);    // Union the subsets
        }
    }

    // Print the edges of the MST and calculate the total weight
    printf("Following are the edges in the constructed MST\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost Spanning Tree: %d\n", minimumCost);

    free(subsets); // Free the allocated memory for subsets
}

// Function to print the adjacency matrix of the graph
void printAdjacencyMatrix(Graph* graph) {
    int V = graph->V; // Number of vertices in the graph
    int adjMatrix[V][V]; // Create a 2D array for the adjacency matrix

    // Initialize the adjacency matrix with 0
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Fill the adjacency matrix with edge weights
    for (int i = 0; i < graph->E; i++) {
        int u = graph->edge[i].src;  // Source vertex of the edge
        int v = graph->edge[i].dest; // Destination vertex of the edge
        int weight = graph->edge[i].weight; // Weight of the edge
        adjMatrix[u][v] = weight; // Set the weight in the matrix
        adjMatrix[v][u] = weight; // Since the graph is undirected, set the reverse edge
    }

    // Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Main function
int main() {
    int V = 4; // Number of vertices in the graph
    int E = 5; // Number of edges in the graph
    Graph* graph = createGraph(V, E); // Create the graph

    // Add edges to the graph
    graph->edge[0].src = 0; // Edge 0-1
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    graph->edge[1].src = 0; // Edge 0-2
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    graph->edge[2].src = 0; // Edge 0-3
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    graph->edge[3].src = 1; // Edge 1-3
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    graph->edge[4].src = 2; // Edge 2-3
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    // Run Kruskal's algorithm to find the MST
    KruskalMST(graph);

    // Print the adjacency matrix of the graph
    printAdjacencyMatrix(graph);

    // Free the allocated memory for the graph
    free(graph->edge);
    free(graph);

    return 0;
}
