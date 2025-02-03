#include "gameoflife.h"


void display_grid3D(int board_count,int board_sizes[board_count], int grid[board_count][MAX_SIZE][MAX_SIZE]) {
    for (int k = 0; k < board_count; k++) {
        printf(" grid %dx%d: \n" , board_sizes[k] , board_sizes[k]);
             for (int i = 0; i < board_sizes[k]; i++) {
                for (int j = 0; j < board_sizes[k]; j++) {
                    printf("%c", grid[k][i][j] ? '#' : '.');
                    printf(" ");
        }
        printf("\n");

    }
    printf("\n");
 }
printf("\n"); 
}


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

    while(fgets(line,sizeof(line),file)) {

        line[strcspn(line, "\n")] = '\0';  //remove newline character (strcspn(line, "\n")) return the position of the first "\n"
        int len = strlen(line);

        if (is_perfect_square(len) == 0){
            printf("the line '%s' is not a perfect square, next line.\n",line);
            continue;
            }
        int size = is_perfect_square(len);
        boards_sizes[board_count] = size;

        int k=0;
        printf("Extrating grid of size %d from line : %s\n",size,line);
        for (int i =0; i < size; i++){
            for (int j =0; j < size; j++){
                boards[board_count][i][j] = line[k++] - '0'; //convert to integer by passing to ASCII code
                printf("line[%d]='%c' -> %d stored at boards [%d][%d][%d]\n",k-1 ,line[k-1],boards[board_count][i][j],board_count,i ,j);
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
void run_game_of_life(int generations, int board_count, int *boards_sizes,int boards[MAX_BOARDS][MAX_SIZE][MAX_SIZE],int live_cells[board_count]){
for (int k =0 ; k < board_count; k++){
    int size = boards_sizes[k];
    int grid[MAX_SIZE][MAX_SIZE], next[MAX_SIZE][MAX_SIZE];
    int history[MAX_HISTORY][MAX_SIZE][MAX_SIZE];
    int history_count = 0;

    memcpy(grid,boards[k],sizeof(int)*size*size);

    for (int gen = 0; gen < generations; gen++){
        printf("====================\n");
        printf("Generation %d:\n", gen + 1);
        display_grid(size, size, grid);

         if (gen > 0 && grids_are_equal(size, size, grid, history[history_count - 1])) {
            printf("Static pattern detected at generation %d, stopping...\n", gen + 1);
            live_cells[k]=count_live_cells(size,size,grid);
            break;
        }

         if (detect_loop(size, size, grid, history, history_count)) {
            printf("Loop pattern detected at generation %d, stopping...\n", gen + 1);
            live_cells[k]=count_live_cells(size,size,grid);
            break;
        }
        if (history_count < MAX_HISTORY) {
            memcpy(history[history_count], grid, sizeof(grid));
            history_count++;
        }

        next_generation(size, size, grid, next);
        memcpy(grid, next, sizeof(grid));  // Update the grid for the next generation
        live_cells[k]=count_live_cells(size,size,grid);

    }
    printf("\nFinal Generation:\n");
    display_grid(size, size, grid);
    printf("Simulation complete.\n");

}
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

    if (argc != 4) {
        printf("Usage: %s <input_file> <generations> <output_file> \n", argv[0]);
        return 1;
    }
const char *input_file = argv[1];
int generations = atoi(argv[2]);
const char *output_file = argv[3];

//check if input_txt exist

FILE *fp = fopen(input_file,"r");
if (!fp){
    perror("Error opening imput.txt file");
    return 1;
}
fclose(fp);

if (generations <= 0){
    printf("Error : generations must be a positive integer.\n");
    return 1;
}

//variable creation

int boards[MAX_BOARDS][MAX_SIZE][MAX_SIZE]; //each boards will be stock here
int boards_sizes[MAX_BOARDS];
int board_count = extract_boards(input_file,boards,boards_sizes);

if (board_count==0) {
    printf("Error, no valid boards found in file %s.\n",input_file);
    return 1;
}

int live_cells_output[MAX_BOARDS]={0};
run_game_of_life(generations,board_count,boards_sizes,boards,live_cells_output);
write_array_to_file(output_file,live_cells_output,board_count);
printf("program successfully executed\n");
return 0;
}