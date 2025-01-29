#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define ALIVE 1
#define DEAD 0

void initialize_grid(int rows, int cols, int grid[rows][cols]);
void display_grid(int rows, int cols, int grid[rows][cols]);
int count_neighbors(int rows, int cols, int grid[rows][cols], int x, int y);
void next_generation(int rows, int cols, int current[rows][cols], int next[rows][cols]);
int grids_are_equal(int rows, int cols, int grid1[rows][cols], int grid2[rows][cols]);

#endif
