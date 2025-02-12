# Max-Heap Implementation in C

This program implements a Max-Heap data structure using an array. It includes functions to build a Max-Heap, insert a new element into the heap, delete an element from the heap, and print the heap.

---

## Table of Contents

1. [Overview](#overview)
2. [Functions](#functions)
   - [`swap`](#swap)
   - [`heapify`](#heapify)
   - [`buildMaxHeap`](#buildmaxheap)
   - [`insertNode`](#insertnode)
   - [`deleteNode`](#deletenode)
   - [`printHeap`](#printheap)
3. [Example Usage](#example-usage)
4. [How It Works](#how-it-works)

---

## Overview

A **Max-Heap** is a complete binary tree where the value of each node is greater than or equal to the values of its children. This implementation uses an array to represent the heap, where:
- The root is at index `0`.
- For a node at index `i`, its left child is at `2*i + 1` and its right child is at `2*i + 2`.
- The parent of a node at index `i` is at `(i - 1) / 2`.

The program demonstrates building a Max-Heap, inserting a new element, deleting an element from the heap, and printing the heap.

---

## Functions

### `swap`

Swaps two elements in the array.

- **Parameters**:
  - `int *a`: Pointer to the first element.
  - `int *b`: Pointer to the second element.

---

### `heapify`

Ensures the subtree rooted at index `i` satisfies the Max-Heap property.

- **Parameters**:
  - `int arr[]`: The array representing the heap.
  - `int n`: The size of the heap.
  - `int i`: The index of the root of the subtree.

---

### `buildMaxHeap`

Converts an unordered array into a Max-Heap.

- **Parameters**:
  - `int arr[]`: The array to be converted into a Max-Heap.
  - `int n`: The size of the array.

---

### `insertNode`

Inserts a new element into the Max-Heap while maintaining the heap property.

- **Parameters**:
  - `int arr[]`: The array representing the heap.
  - `int *n`: Pointer to the size of the heap.
  - `int Key`: The value to be inserted.

---

### `deleteNode`

Deletes a specified element from the Max-Heap while maintaining the heap property.

- **Parameters**:
  - `int arr[]`: The array representing the heap.
  - `int *n`: Pointer to the size of the heap.
  - `int key`: The value to be deleted.

---

### `printHeap`

Prints the elements of the heap.

- **Parameters**:
  - `int arr[]`: The array representing the heap.
  - `int n`: The size of the heap.

---

## Example Usage

The program initializes an array, builds a Max-Heap, inserts a new element, deletes an element, and prints the heap at each step.

### Output Example:

```plaintext
Max-Heap array: 90 75 89 15 36 85 63 65 21 70 18 
After inserting 96: 96 75 90 15 36 85 63 65 21 70 18 89 
After deleting 96: 90 75 89 15 36 85 63 65 21 70 18 
