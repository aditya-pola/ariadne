// main.c
#include "maze.h"
#include <stdlib.h>

int main() {
    Grid* grid = create_grid(4, 4);

    // Select the maze generation algorithm
    // MazeGenerator algorithm = generate_maze_binary_tree;  // Change this line to switch algorithms
    MazeGenerator algorithm = generate_maze_sidewinder;

    // Generate and display the maze
    algorithm(grid);
    display_maze(grid);

    // Free allocated memory
    for (int r = 0; r < grid->rows; r++) {
        free(grid->cells[r]);
    }
    free(grid->cells);
    free(grid);

    return 0;
}
