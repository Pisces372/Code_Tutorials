#ifndef __FILEOUTPUTS__
#define __FILEOUTPUTS__
#include <limits.h>

// Holds all the functions that are needed for binary grid and creating the text file
// Read the binary data from the input file
short** make_binary_grid(char *filename, short *m, short *n);

// Takes the binary grid and prints it to a file
bool make_text_grid(char *filename, short *m, short *n, short** grid);

// Creates the file that holds the fastest times from each input
bool make_fastest_time(char *filename, short *n, int *time);

// Creates the file that holds the fastest path 
bool make_fastest_path(char *filename, int *fastestTime, int **arr);

#endif