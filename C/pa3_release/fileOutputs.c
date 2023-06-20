#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Read the binary data from the input file
short** make_binary_grid(char* filename, short* m, short* n)
{
    // Open the file. We assume that the file is always correct when being passed into the argument.
    FILE *binaryData = fopen(filename, "rb");

    if (binaryData == NULL) {
        fprintf(stderr, "File error: no file named %s\n", filename);
        return NULL;
    }
    
    // Read the number of rows and columns from the file.
    fread(m, sizeof(*m), 1, binaryData);
    fread(n, sizeof(*n), 1, binaryData);

    (*m)++;

    //Allocate memory for the grid.
    short** grid = malloc((sizeof(*grid) + sizeof(**grid) * (*n)) * (*m));
    if (grid == NULL) {
        fprintf(stderr, "Memory error: alloc failed to allocate\n");
        fclose(binaryData);
        return NULL;
    }
    for (int i = 0; i < *m; i++)
    {
        grid[i] = &((short*) &grid[*m])[i*(*n)];
    }
    
    fread(&grid[*m], sizeof(**grid), (*n) * (*m), binaryData);

    for(int i = 0; i < *n; i++)
    {
        grid[*m - 1][i] = 0;
    }
    
    fclose(binaryData);

    return grid;
}

bool make_text_grid(char* filename, short* m, short* n, short** grid)
{
    // Open the file. We assume that the file is always correct when being passed into the argument.
    FILE *textData;
    textData = fopen(filename, "w");

    if (textData == NULL) {
        return false;
    }
    
    // Print the size of the grid first
    fprintf(textData, "%d %d", *m, *n);

    // Print the grid into the file
    for(int i = 0; i < *m; i++) //As long as i doesn't match the number of rows
    {
        fprintf(textData, "\n%hd", grid[i][0]);
        for(int j = 1; j < *n; j++)
        {
            fprintf(textData, " %hd", grid[i][j]); //As long as j doesn't match the number of columns
        }
    }
    fputc('\n', textData);
    
    return !fclose(textData);
}

bool make_fastest_time(char *filename, short *n, int *time)
{
    FILE *ft = fopen(filename, "wb+");
    if(ft == NULL)
    {
        return false;
    }

    // Write the number of columns
    fwrite(n, sizeof(short), 1, ft);

    // Write the fastest times by printing the array
    for(int i = 0; i < *n; i++)
    {
        fwrite(&time[i], sizeof(int), 1, ft);
    }

    return !fclose(ft);
}

bool make_fastest_path(char *filename, int *fastestTime, int **Path)
{
    FILE *fp = fopen(filename, "wb+");
    if(fp == NULL)
    {
        return false;
    }
    
    fwrite(fastestTime, sizeof(int), 1, fp);

    int *arr = *Path;
    int times = (arr[0] * 2) + 1;
    int breakLine = 0;

    fwrite(&((*Path)[0]), sizeof(short), 1, fp);
    fwrite(&breakLine, sizeof(short), 1, fp);

    for(int i = 1; i < times; i++)
    {
        fwrite(&((*Path)[i]), sizeof(short), 1, fp); 
    }
    
    return !fclose(fp);
}


