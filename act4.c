#include <stdlib.h>
#include <string.h>
#include "gameoflife.h"

#define MAX_HISTORY 1000  // Memory generation limit

// Function to check if two grids are equal (for static/loop detection)
int grids_are_equal(int rows, int cols, int grid1[rows][cols], int grid2[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid1[i][j] != grid2[i][j]) {
                return 0;  // Grids are not equal
            }
        }
    }
    return 1;  // Grids are identical
}

// Function to detect if the current grid matches any previous grid (loop detection)
int detect_loop(int rows, int cols, int grid[rows][cols], int history[][rows][cols], int history_count) {
    for (int h = 0; h < history_count; h++) {
        if (grids_are_equal(rows, cols, grid, history[h])) {
            return 1;  // Loop detected
        }
    }
    return 0;  // No loop detected
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s NumRows NumCols NumGenerations\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int generations = atoi(argv[3]);

    int grid[rows][cols], next[rows][cols];
    int history[MAX_HISTORY][rows][cols];  // Array to store previous generations
    int history_count = 0;                // Number of stored generations

    initialize_grid(rows, cols, grid);

    for (int gen = 0; gen < generations; gen++) {
        system("clear");
        printf("====================\n");
        printf("Generation %d:\n", gen + 1);
        display_grid(rows, cols, grid);

        // Check for static pattern
        if (gen > 0 && grids_are_equal(rows, cols, grid, history[history_count - 1])) {
            printf("Static pattern detected at generation %d, stopping...\n", gen + 1);
            break;
        }



// Check for loop pattern
        if (detect_loop(rows, cols, grid, history, history_count)) {
            printf("Loop pattern detected at generation %d, stopping...\n", gen + 1);
            break;
        }

        // Store current grid in history
        if (history_count < MAX_HISTORY) {
            memcpy(history[history_count], grid, sizeof(grid));
            history_count++;
        }

        // Compute the next generation
        next_generation(rows, cols, grid, next);
        memcpy(grid, next, sizeof(grid));  // Update the grid for the next generation

        usleep(200000);  // Pause for 200 milliseconds
    }

    printf("\nFinal Generation:\n");
    display_grid(rows, cols, grid);
    printf("Simulation complete.\n");

    return 0;
}
