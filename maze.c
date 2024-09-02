// maze.c
#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new cell
Cell* create_cell(int row, int col) {
    Cell* cell = malloc(sizeof(Cell));
    cell->row = row;
    cell->col = col;
    for (int i = 0; i < 4; i++) {
        cell->links[i] = NULL;
    }
    return cell;
}

// Function to create a grid of cells
Grid* create_grid(int rows, int cols) {
    Grid* grid = malloc(sizeof(Grid));
    grid->rows = rows;
    grid->cols = cols;

    grid->cells = malloc(rows * sizeof(Cell*));
    for (int r = 0; r < rows; r++) {
        grid->cells[r] = malloc(cols * sizeof(Cell));
        for (int c = 0; c < cols; c++) {
            grid->cells[r][c] = *create_cell(r, c);
        }
    }
    return grid;
}

// Function to link two cells
void link_cells(Cell* cell1, Cell* cell2, int direction) {
    cell1->links[direction] = cell2;
    cell2->links[(direction + 2) % 4] = cell1; // Opposite direction
}

// Function to unlink two cells
void unlink_cells(Cell* cell1, Cell* cell2, int direction) {
    cell1->links[direction] = NULL;
    cell2->links[(direction + 2) % 4] = NULL;
}

// Function to check if two cells are linked
int are_linked(Cell* cell1, Cell* cell2) {
    for (int i = 0; i < 4; i++) {
        if (cell1->links[i] == cell2) return 1;
    }
    return 0;
}

// Function to get neighbors of a cell
Cell** neighbors(Grid* grid, Cell* cell, int* count) {
    int row = cell->row;
    int col = cell->col;
    Cell** neighbor_list = malloc(4 * sizeof(Cell*));
    *count = 0;

    if (row > 0) neighbor_list[(*count)++] = &grid->cells[row - 1][col]; // North
    if (row < grid->rows - 1) neighbor_list[(*count)++] = &grid->cells[row + 1][col]; // South
    if (col > 0) neighbor_list[(*count)++] = &grid->cells[row][col - 1]; // West
    if (col < grid->cols - 1) neighbor_list[(*count)++] = &grid->cells[row][col + 1]; // East

    return neighbor_list;
}

// Function to apply an operation to each cell in the grid
void each_cell(Grid* grid, void (*f)(Cell*)) {
    for (int r = 0; r < grid->rows; r++) {
        for (int c = 0; c < grid->cols; c++) {
            f(&grid->cells[r][c]);
        }
    }
}

// Function to apply an operation to each row in the grid
void each_row(Grid* grid, void (*f)(Cell*, int)) {
    for (int r = 0; r < grid->rows; r++) {
        for (int c = 0; c < grid->cols; c++) {
            f(&grid->cells[r][c], r);
        }
    }
}

// Function to display the maze using ASCII art
void display_maze(Grid* grid) {
    printf("+"); // Top border
    for (int c = 0; c < grid->cols; c++) {
        printf("---+");
    }
    printf("\n");

    for (int r = 0; r < grid->rows; r++) {
        printf("|"); // Left border
        for (int c = 0; c < grid->cols; c++) {
            Cell* cell = &grid->cells[r][c];
            printf("   "); // Cell space
            printf("%s", (cell->links[EAST] != NULL) ? " " : "|"); // Right wall
        }
        printf("\n+"); // Bottom border or row separator
        for (int c = 0; c < grid->cols; c++) {
            Cell* cell = &grid->cells[r][c];
            printf("%s", (cell->links[SOUTH] != NULL) ? "   " : "---"); // Bottom wall
            printf("+");
        }
        printf("\n");
    }
}
