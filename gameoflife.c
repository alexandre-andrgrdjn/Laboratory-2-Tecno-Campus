#include "gameoflife.h"

void initialize_grid(int rows, int cols, int grid[rows][cols]) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;  // Random 0 or 1 (dead or alive)
        }
    }
}

void display_grid(int rows, int cols, int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j] ? '#' : '.');
        }
        printf("\n");
    }
}

int count_neighbors(int rows, int cols, int grid[rows][cols], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = (x + i + rows) % rows;
            int nj = (y + j + cols) % cols;
            count += grid[ni][nj];
        }
    }
    return count;
}

void next_generation(int rows, int cols, int current[rows][cols], int next[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = count_neighbors(rows, cols, current, i, j);
            if (current[i][j] == ALIVE) {
                next[i][j] = (neighbors == 2 || neighbors == 3) ? ALIVE : DEAD;
            } else {
                next[i][j] = (neighbors == 3) ? ALIVE : DEAD;
            }
        }
    }
}
