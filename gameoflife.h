#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define ALIVE 1
#define DEAD 0
#define MAX_HISTORY 1000  // Memory generation limit
#define MAX_BOARDS 100
#define MAX_SIZE 100


void initialize_grid(int rows, int cols, int grid[rows][cols]);
void display_grid(int rows, int cols, int grid[rows][cols]);
int count_neighbors(int rows, int cols, int grid[rows][cols], int x, int y);
void next_generation(int rows, int cols, int current[rows][cols], int next[rows][cols]);

int is_perfect_square(int number);
int count_live_cells (int rows, int cols, int grid[rows][cols]);
int extract_boards(const char *filename, int boards[MAX_BOARDS][MAX_SIZE][MAX_SIZE], int *boards_sizes);
void write_array_to_file(const char *filename, int rep[MAX_BOARDS],int size);
int run_game_of_life(int rows, int cols, int generations,int history[MAX_HISTORY][rows][cols]);
#endif
