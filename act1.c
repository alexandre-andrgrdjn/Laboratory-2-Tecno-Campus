#include "gameoflife.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s NumRows NumCols\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int grid[rows][cols];

    initialize_grid(rows, cols, grid);
    display_grid(rows, cols, grid);

    return 0;
}
