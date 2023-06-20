#ifndef __HEAP__
#define __HEAP__

typedef struct MinHeap MinHeap;
struct MinHeap {
    int* edge;
    int* xCoor;
    int* yCoor;
    
    // Current Size of the Heap
    int size;
    // Maximum capacity of the heap
    int capacity;
};

#endif
