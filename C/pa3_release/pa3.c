#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "heap.h"
#include "fileOutputs.h"
#include "Dijkstra.h"

//gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g *.c -o pa3_test
// ./pa3_test examples/4_5.b testfolder/4_5.t testfolder/4_5.f testfolder/4_5.p

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        fprintf(stderr, "Not enough arguments were provided.\n");
        return EXIT_FAILURE;
    }
    // agrv[1] is an input file binary grid.
    // argv[2] is the first output file. Converts the binary grid to a text grid.
    // argv[3] is the second output file. Stores the fastest time to exit the grid from each entry location in binary.
    // argv[4] is the third output file. Stores the fastests path to exit the grid from each entry location in binary.
    else
    {
        short m, n; // m is row & n is column.
        int *fastestPath; // First element is the # of path visited, then coordinates in form of y, x.

        // Reads in the data from the file
        short** grid = make_binary_grid(argv[1], &m, &n); // Stores the grid values in an array.
        if (grid == NULL) {
            return EXIT_FAILURE;
        }
        
        // Finds the fastest times from each entry position and returns an array of these times.
        int* fastestTimes = dijkstra(grid, &m, &n, &fastestPath);

        // for(int i = 0; i < (fastestPath[0] * 2) + 1; i++)
        // {
        //     fprintf(stderr, "%d ", fastestPath[i]);
        // }
        // fprintf(stderr, "\n");


        int quickestTime = fastestTimes[0];
        for(int i = 0; i < n; i++)
        {
            //fprintf(stderr, "%d\n", fastestTimes[i]);
            if(fastestTimes[i] < quickestTime)
            {
                quickestTime = fastestTimes[i];
            }
        }

        m--;

        // Writes the text output file
        if (!make_text_grid(argv[2], &m, &n, grid)) {
            fprintf(stderr, "File Error: Unable to create text grid file.\n");
        }

        // Writes a file that holds all the fastest times
        if (!make_fastest_time(argv[3], &n, fastestTimes)) {
            fprintf(stderr, "File Error: Unable to create fastest times file.\n");
        }

        // Writes a file that holds the fastest path
        if (!make_fastest_path(argv[4], &quickestTime, &fastestPath)) {
            fprintf(stderr, "File Error: Unable to create fastest path file.\n");
        }

        free(grid);
        free(fastestPath);
        free(fastestTimes);

        return 0;
    }
}