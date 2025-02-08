#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to build a Max-Heap from the given array
void buildMaxHeap(int arr[], int n) {
    // Index of last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal from last non-leaf node and heapify each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to insert a new node to the Max-Heap
void insertNode(int arr[], int* n, int Key) {
    // Increase the size of Heap by 1
    (*n)++;
    int i = *n - 1;

    // Insert the element at end of Heap
    arr[i] = Key;

    // Heapify the new node following a bottom-up approach
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to delete a node from Max-Heap
void deleteNode(int arr[], int* n, int key) {
    // Find the index of the key to be deleted
    int i;
    for (i = 0; i < *n; i++) {
        if (arr[i] == key)
            break;
    }

    // Replace key with last element
    arr[i] = arr[*n - 1];
    *n = *n - 1;

    // Heapify the root node
    heapify(arr, *n, i);
}

// Function to print the heap
void printHeap(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {21, 18, 85, 15, 36, 75, 63, 65, 90, 70, 89};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Build the Max-Heap
    buildMaxHeap(arr, n);

    printf("Max-Heap array: ");
    printHeap(arr, n);

    // Insert 96 into the heap
    insertNode(arr, &n, 96);
    printf("After inserting 96: ");
    printHeap(arr, n);

    // Delete 96 from the heap
    deleteNode(arr, &n, 96);
    printf("After deleting 96: ");
    printHeap(arr, n);

    return 0;
}
