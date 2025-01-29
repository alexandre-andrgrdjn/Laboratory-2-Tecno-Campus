#include "gameoflife.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s NumRows NumCols NumGenerations\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int generations = atoi(argv[3]);

    int grid[rows][cols], next[rows][cols];
    initialize_grid(rows, cols, grid);

    for (int gen = 0; gen < generations; gen++) {
        printf("\n====================\n");
        printf("Generation %d:\n", gen + 1);
        display_grid(rows, cols, grid);
        next_generation(rows, cols, grid, next);
        
        memcpy(grid, next, sizeof(grid));  // Copy next generation to current grid

        usleep(200000);  // Pause for 200 milliseconds
    }


    return 0;
}
