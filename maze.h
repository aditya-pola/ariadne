// maze.h
#ifndef MAZE_H // Include Guards
#define MAZE_H

// Define the Cell structure
typedef struct Cell {
    int row, col;
    struct Cell* links[4]; // Pointers to linked neighbors (N, S, E, W)
} Cell;

// Define the Grid structure
typedef struct Grid {
    int rows, cols;
    Cell** cells; // 2D array of cells
} Grid;

// Directions for easier linking and unlinking
enum { NORTH, SOUTH, EAST, WEST };

// Function declarations
Cell* create_cell(int row, int col);
Grid* create_grid(int rows, int cols);
int get_opposite_direction(int direction);
void link_cells(Cell* cell1, Cell* cell2, int direction);
void unlink_cells(Cell* cell1, Cell* cell2, int direction);
int are_linked(Cell* cell1, Cell* cell2);
Cell** neighbors(Grid* grid, Cell* cell, int* count);
void each_cell(Grid* grid, void (*f)(Cell*));
void each_row(Grid* grid, void (*f)(Cell*, int));
void display_maze(Grid* grid);

// Typedef for maze generation function pointer
typedef void (*MazeGenerator)(Grid* grid);

// Maze generation algorithms
void generate_maze_binary_tree(Grid* grid);
void generate_maze_sidewinder(Grid* grid);

#endif // MAZE_H
