#include "gameoflife.h"



int is_perfect_square(int number){ // chech if it's a real square
    int root =sqrt(number);
    if (root*root == number){
        return root;
    }
    return 0;
}

int count_live_cells (int rows, int cols, int grid[rows][cols]){
    int live_cells=0;
    for (int i =0; i< rows;i++){
         for (int j =0; j< cols;j++){
            live_cells+=grid[i][j];
         }
    }
    return live_cells; //total of alive cells
}

int extract_boards(const char *filename, int boards[MAX_BOARDS][MAX_SIZE][MAX_SIZE], int *boards_sizes){
FILE *file = fopen(filename,"r");
if (!file) {
    perror("Error during opening file");
    return -1;
}
char line[1024];
int board_count = 0;

while( fgets(line,sizeof(line),file)) {

line[strcspn(line, "\n")] = '\0';  //remove newline character (strcspn(line, "\n")) return the position of the first "\n"
int len = strlen(line);

if (is_perfect_square(len) == 0){
    printf("the line '%s' is not a perfect square, next line.\n",line);
    continue;
}
int size = is_perfect_square(len);
boards_sizes[board_count] = size;

int k=0;
for (int i =0; i < size; i++){
    for (int j =0; j < size; j++){
        boards[board_count][i][j] = line[k++]- '0'; //convert to integer by passing to ASCII code
    }
}
board_count++;

if (board_count >= MAX_BOARDS){
    printf("Maximum number of grids reached\n"); //check with MAX_BOARDS number
    break;
}
}
fclose(file);
return board_count;
}

void run_game_of_life(int rows, int cols, int generations,int history[MAX_HISTORY][rows][cols]){

    int grid[rows][cols], next[rows][cols];

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

}   


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s NumRows NumCols NumGenerations\n", argv[0]);
        return 1;
    }
