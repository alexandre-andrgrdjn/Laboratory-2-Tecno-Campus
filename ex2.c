#include "gameoflife.h"


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
FILE *file = fopen(filename, "r");
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

int run_game_of_life(int rows, int cols, int generations,int history[MAX_HISTORY][rows][cols]){

    int grid[rows][cols], next[rows][cols];

    int history_count = 0;                // Number of stored generations

    initialize_grid(rows, cols, grid);

    for (int gen = 0; gen < generations; gen++) {
        printf("====================\n");
        printf("Generation %d:\n", gen + 1);
        display_grid(rows, cols, grid);

        // Check for static pattern
        if (gen > 0 && grids_are_equal(rows, cols, grid, history[history_count - 1])) {
            printf("Static pattern detected at generation %d, stopping...\n", gen + 1);
            return gen;
        }

// Check for loop pattern
        if (detect_loop(rows, cols, grid, history, history_count)) {
            printf("Loop pattern detected at generation %d, stopping...\n", gen + 1);
            return gen;
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
    return generations-1;

}   

void write_array_to_file(const char *filename, int rep[MAX_BOARDS],int size){
    FILE *file = fopen(filename, "w");
if (!file) {
    perror("Error during opening file");
}

for (int i = 0; i < size; i++)
{
    fprintf(file,"%d\n", rep[i]);
}

fclose(file);

}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s imput.txt generations nameImput nameOutput\n", argv[0]);
        return 1;
    }
const char *imput_txt = argv[1];
const char *generations_str = argv[2];
const char *nameImput = argv[3];
const char *nameOutput = argv[4]; //extract arguments

//check if imput_txt exist

FILE *fp = fopen(imput_txt,"r");
if (!fp){
    perror("Error opening imput.txt file");
    return 1;
}
fclose(fp);
int generations = atoi(generations_str); //convert str to int
if (generations <= 0){
    printf("Error : generations must be a positive integer.\n");
    return 1;
}

//variable creation
int boards[MAX_BOARDS][MAX_SIZE][MAX_SIZE]; //each boards will be stock here
int boards_sizes[MAX_BOARDS] = {0};
int board_count = extract_boards(nameImput,boards,boards_sizes);

if (board_count==0) {
    printf("Error, no valid boards found in file %s.\n",nameImput);
    return 1;
}

int live_counts[MAX_BOARDS]={0};

for(int b= 0; b<board_count; b++){
    int size = boards_sizes[b];
    int history[MAX_HISTORY][size][size]; // prepare history for game simulation
    int final_index = run_game_of_life(size,size,generations,history);
    live_counts[b] = count_live_cells(size,size,history[final_index]);  
}
write_array_to_file(nameOutput,live_counts,board_count);
printf("program successfully executed\n");
}