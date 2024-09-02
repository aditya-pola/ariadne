// main.c
#include "maze.h"
#include <stdlib.h>

int main() {
    Grid* grid = create_grid(4, 4);

    // Select the maze generation algorithm
    MazeGenerator algorithm;
    
#ifdef USE_BINARY_TREE
    algorithm = generate_maze_binary_tree;
#elif defined(USE_SIDEWINDER)
    algorithm = generate_maze_sidewinder;
#endif

    if (algorithm == NULL) {
        // Default to binary tree or some other algorithm
        printf("No specific algorithm defined. Using default: Binary Tree.\n");
        algorithm = generate_maze_binary_tree;
    }

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
