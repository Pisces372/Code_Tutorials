#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "heap.h"
#include "Dijkstra.h"

// Recieves a grid, # of rows, # of columns
// Finds the fastest times and the fastest path.
// Returns the fastest times as an array.
int* dijkstra(short **grid, short *m, short *n, int **coordinatesPathArray)
{
    // The edgeVal holds the quickest time needed to reach the node we are currently at. We initialize it to 0.
    int edgeVal;

    // Allocate space for holding the fastest times from each entry location.
    int *ftArr = (int *)malloc(sizeof(int) * (*n));

    // Malloc memory for tracking the total time for visiting each square.
    int** time = malloc((sizeof(*time) + sizeof(**time) * (*n)) * (*m));
    if (time == NULL) {
        fprintf(stderr, "Memory error: alloc failed to allocate\n");
        return NULL;
    }
    for (int i = 0; i < *m; i++)
    {
        time[i] = &((int*) &time[*m])[i*(*n)];
    }

    //Malloc memory to track if all squares have been visited.
    int** visited = malloc((sizeof(*visited) + sizeof(**visited) * (*n)) * (*m));
    if (visited == NULL) {
        fprintf(stderr, "Memory error: alloc failed to allocate\n");
        return NULL;
    }
    for (int i = 0; i < *m; i++)
    {
        visited[i] = &((int*) &visited[*m])[i*(*n)];
    }

    // Create a min heap to hold the times
    MinHeap *previousTimes = init_minheap((*m) * (*n));

    // Before we enact dijkstra's algorithm from the lowest left node, we to initialize several variables.

    // Instead of NULL, we initialize all the times to 0 so we can start with a blank slate. 
    reset(m, n, time);
    reset(m, n, visited);

    // We set the starting position to the lowest and the leftmost node.
    // X -> set the the leftmost column
    // Y -> set the the lowest row, which is (# of rows - 1)
    int x = 0;
    int y = *m - 1;

    // Set the edgeVal to the grid entry position, which should always be 0.
    edgeVal = grid[y][x];
    time[y][x] = edgeVal;
    visited[y][x] = 1;

    // We populate the minheap with the first entry node.
    previousTimes = insert_minheap(previousTimes, edgeVal, x, y);

    // Keep calculating the times to reach every square until the min heap is fully emptied
    while(previousTimes->size != 0)
    {
        // Sets the edgeValue to the minimum node and its coordinates
        edgeVal = previousTimes->edge[0];
        x = previousTimes->xCoor[0];
        y = previousTimes->yCoor[0];
        // Deletes the minimum node after we get all the values.
        previousTimes = delete_minimum(previousTimes);

        // Visit top of current location
        if( (isValid(m, n, x, y - 1)) && (visited[y - 1][x] == 0) )
        {
            time[y - 1][x] = edgeVal + grid[y - 1][x];
            visited[y - 1][x] = 1;
            previousTimes = insert_minheap(previousTimes, time[y - 1][x], x, y - 1);
        }
        // Visit right of current location
        if( (isValid(m, n, x + 1, y)) && (visited[y][x + 1] == 0) )
        {
            time[y][x + 1] = edgeVal + grid[y][x + 1];
            visited[y][x + 1] = 2;
            previousTimes = insert_minheap(previousTimes, time[y][x + 1], x + 1, y);
        }  
        // Visit left of current 
        if( (isValid(m, n, x - 1, y)) && (visited[y][x - 1] == 0) )
        {
            time[y][x - 1] = edgeVal + grid[y][x - 1];
            visited[y][x - 1] = 3;
            previousTimes = insert_minheap(previousTimes, time[y][x - 1], x - 1, y);
        }
        // Visit bottom of current location
        if( (isValid(m, n, x, y + 1)) && (visited[y + 1][x] == 0) )
        {
            time[y + 1][x] = edgeVal + grid[y + 1][x];
            visited[y + 1][x] = 4;
            previousTimes = insert_minheap(previousTimes, time[y + 1][x], x, y + 1);
        }
    }

    // Reads all the values into the ftArr
    int lowestTime = time[0][0];
   
    for(int i = 0; i < *n; i++)
    {
        ftArr[i] = time[0][i];
        if(lowestTime > time[0][i])
        {
            lowestTime = time[0][i];
            x = i;
            y = 0;
        }
    }

    *coordinatesPathArray = recordfastestPath(&x, &y, m, visited);

    free_minheap(previousTimes);
    free(time);
    free(visited);
    return ftArr;
}

void reset(short *m, short *n, int **array)
{
    for(int i = 0; i < *m; i++)
    {
        for(int j = 0; j < *n; j++)
        {
            array[i][j] = 0;
        }
    }

    return;
}

bool isValid(short* m, short *n, int i, int j)
{
    if((i < 0) || (i >= *n))
    {
        //fprintf(stderr, "return false\n");
        return false;
    }

    if((j < 0) || (j >= *m))
    {
        //fprintf(stderr, "return false\n");
        return false;
    }

    //fprintf(stderr, "return true\n");
    return true;
}

int* recordfastestPath(int *xVal, int *yVal, short *m, int **array)
{
    int placesVisited = 0;
    int x = *xVal;
    int y = *yVal;

    while(y < (*m - 1))
    {
        if(array[y][x] == 1)
        {
            placesVisited++;
            y++;
        }
        else if (array[y][x] == 2)
        {
            placesVisited++;
            x--;
        }
        else if (array[y][x] == 3)
        {
            placesVisited++;
            x++;
        }
        else if (array[y][x] == 4)
        {
            placesVisited++;
            y--;
        }
    } 
    x = *xVal;
    y = *yVal;

    int *fastestPath = (int *)malloc(sizeof(int) + (sizeof(int) * placesVisited * 2));

    int index = 1;
    while(y < (*m - 1))
    {
        if(array[y][x] == 1)
        {
            fastestPath[index] = y;
            fastestPath[index + 1] = x;
            y++;
        }
        else if (array[y][x] == 2)
        {
            fastestPath[index] = y;
            fastestPath[index + 1] = x;
            x--;
        }
        else if (array[y][x] == 3)
        {
            fastestPath[index] = y;
            fastestPath[index + 1] = x;
            x++;
        }
        else if (array[y][x] == 4)
        {
            fastestPath[index] = y;
            fastestPath[index + 1] = x;
            y--;
        }

        index = index + 2;
    }

    fastestPath[0] = placesVisited;

   return fastestPath;
}

int parent(int i) 
{
    return (i - 1) / 2;
}

int left_child(int i) 
{
    return (2*i + 1);
}

int right_child(int i) 
{
    return (2*i + 2);
}

int get_min(MinHeap* heap, int *x, int *y) 
{
    *x = heap -> xCoor[0];
    *y = heap -> yCoor[0];
    return heap -> edge[0];
}

MinHeap* init_minheap(int capacity) 
{
    MinHeap* minheap = (MinHeap*) calloc (1, sizeof(MinHeap));
    minheap->edge = (int*) calloc (capacity, sizeof(int));
    minheap->xCoor = (int*) calloc (capacity, sizeof(int)); 
    minheap->yCoor = (int*) calloc (capacity, sizeof(int));
    minheap->size = 0;
    minheap->capacity = capacity;
    return minheap;
}

void free_minheap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->edge);
    free(heap->xCoor);
    free(heap->yCoor);
    free(heap);
}

MinHeap* insert_minheap(MinHeap* heap, int value, int xValue, int yValue) 
{

    // Checks if heap is @ max capacity or not
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Cannot insert %d. Heap is already full!\n", value);
        return heap;
    }

    // Inserts the edgeValue and its coordinates into the appropriate array.
    heap -> size++;
    heap -> edge[heap->size - 1] = value;
    heap -> xCoor[heap->size - 1] = xValue;
    heap -> yCoor[heap->size - 1] = yValue;

    // Keep swapping until we reach the root
    int curr = heap -> size - 1;
    // As long as you aren't in the root node, and while the parent of the last element is greater than it
    while (curr > 0 && heap->edge[parent(curr)] > heap->edge[curr]) 
    {
        // Hold edgeValues into temp variables
        int temp = heap -> edge[parent(curr)];

        // Hold x and y values into temp variables
        int xTemp = heap -> xCoor[parent(curr)];
        int yTemp = heap -> yCoor[parent(curr)];

        //Swap the values
        heap -> edge[parent(curr)] = heap -> edge[curr];
        heap -> edge[curr] = temp;

        // Swap the x & y coords
        heap -> xCoor[parent(curr)] = heap -> xCoor[curr];
        heap -> xCoor[curr] = xTemp;
        heap -> yCoor[parent(curr)] = heap -> yCoor[curr];
        heap -> yCoor[curr] = yTemp;  

        // Update the current index of element
        curr = parent(curr);
    }

    return heap; 
}

MinHeap* heapify(MinHeap* heap, int index) {
    if (heap->size <= 1)
    {
        return heap;
    }

    int left = left_child(index); 
    int right = right_child(index); 

    // Variable to get the smallest element of the subtree of an element an index
    int smallest = index; 
    
    // If the left child is smaller than this element, it is the smallest
    if (left < heap->size && heap->edge[left] < heap->edge[index])
    {
        smallest = left; 
    }
       
    if (right < heap->size && heap->edge[right] < heap->edge[smallest])
    {
        smallest = right; 
    }
        
    // Now if the current element is not the smallest,
    // swap with the current element. The min heap property
    // is now satisfied for this subtree. We now need to
    // recursively keep doing this until we reach the root node,
    // the point at which there will be no change!
    if (smallest != index) 
    { 
        int temp = heap->edge[index];
        heap->edge[index] = heap->edge[smallest];
        heap->edge[smallest] = temp;

        int xTemp = heap->xCoor[index];
        heap->xCoor[index] = heap->xCoor[smallest];
        heap->xCoor[smallest] = xTemp;

        int yTemp = heap->yCoor[index];
        heap->yCoor[index] = heap->yCoor[smallest];
        heap->yCoor[smallest] = yTemp;

        heap = heapify(heap, smallest); 
    }

    return heap;
}

MinHeap* delete_minimum(MinHeap* heap) 
{
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    int size = heap->size;
    int last_element = heap->edge[size-1];
    int last_xCoor = heap->xCoor[size-1];
    int last_yCoor = heap->yCoor[size-1];
    
    // Update root value with the last element
    heap->edge[0] = last_element;
    heap->xCoor[0] = last_xCoor;
    heap->yCoor[0] = last_yCoor;

    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;

    // We need to call heapify(), to maintain the min-heap property
    heap = heapify(heap, 0);
    return heap;
}

void print_heap(MinHeap* heap) {
    printf("Min Heap:\n");
    for (int i=0; i<heap->size; i++) {
        printf("(%d, %d): %d -> ", heap->xCoor[i], heap->yCoor[i], heap->edge[i]);
    }
    printf("\n");
}
