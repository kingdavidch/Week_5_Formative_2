#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* item;
    int bid;
} Bid;

// Function to swap two bids
void swapBids(Bid* a, Bid* b) {
    Bid temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapifyBids(Bid arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left].bid > arr[largest].bid)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right].bid > arr[largest].bid)
        largest = right;

    // If largest is not root
    if (largest != i) {
        swapBids(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapifyBids(arr, n, largest);
    }
}

// Function to build a Max-Heap from the given array
void buildMaxHeapBids(Bid arr[], int n) {
    // Index of last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal from last non-leaf node and heapify each node
    for (int i = startIdx; i >= 0; i--) {
        heapifyBids(arr, n, i);
    }
}

// Function to extract the maximum bid from the heap
Bid extractMaxBid(Bid arr[], int* n) {
    Bid root = arr[0];
    arr[0] = arr[*n - 1];
    *n = *n - 1;
    heapifyBids(arr, *n, 0);
    return root;
}

int main() {
    Bid bids[] = {
        {"table", 200},
        {"fridge", 300},
        {"kettle", 210},
        {"sofa sets", 400},
        {"office chairs", 150},
        {"TV", 500}
    };
    int n = sizeof(bids) / sizeof(bids[0]);

    // Build the Max-Heap
    buildMaxHeapBids(bids, n);

    printf("Highest bids:\n");
    while (n > 0) {
        Bid maxBid = extractMaxBid(bids, &n);
        printf("Item: %s, Bid: %d\n", maxBid.item, maxBid.bid);
    }

    return 0;
}
