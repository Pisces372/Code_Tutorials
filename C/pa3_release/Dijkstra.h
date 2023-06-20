#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include "heap.h"

// Finds the fastest path given a grid
// Returns a 1D array that 
int* dijkstra(short **grid, short *m, short *n, int **coordinatesPathArray);

// Resets a 2D array to 0
void reset(short *m, short *n, int **array);

// Checks if the index of the array is out of bounds
// Prevents a seg fault
bool isValid(short *m, short *n, int i, int j);

int* recordfastestPath(int *xVal, int *yVal, short *m, int **array);

// Functions used for min heap stuff. 
int parent(int i);
int left_child(int i);
int right_child(int i);
int get_min(MinHeap* heap, int *x, int *y);

// Capacity is the max size so it should be the number of elements in the array.
MinHeap* init_minheap(int capacity);

// Free the damn space
void free_minheap(MinHeap* heap);

// Insert an element into the heap
MinHeap* insert_minheap(MinHeap* heap, int value, int xValue, int yValue);

// Rearranges the heap as to maintain the min-heap property
MinHeap* heapify(MinHeap* heap, int index);

// Delete the minimum node in the heap
MinHeap* delete_minimum(MinHeap* heap);

// Simply print the array. This is an inorder traversal of the tree
void print_heap(MinHeap* heap);

#endif