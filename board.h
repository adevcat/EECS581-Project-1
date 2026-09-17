/**
 * @file board.h
 * @brief Class declaration for managing the 10x10 Minesweeper grid.
 * @author Zackary Rhodes
 * @date 2026-09-16
 * 
 * Declares the Board class interface, tracking mine totals, active flag counts,
 * grid dimensions, bounds validation, and cell state mutators.
 */
#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <iostream>
#include <string>

class Board {

public:
    // Fixed Board Dimensions
    inline static const int ROWS = 10;
    inline static const int COLL = 10;

    // Constructors
    Board();              // Default constructor initializes a board with empty mines.
    Board(int numMines);  // initializes the board setting total mines to the given number of mines.

    // Getter functions
    int getTotalMines() const; // Gets the total mine count of the current game.
    int getTotalFlags() const; // Gets the current total flag count.

    // Boundry verification helper function to validate coordinates
    bool isValidCoordinate(int r, int c) const;

    // Mutator Functions to populate the grid
    void placeMine(int r, int c);                    // Places mine at the coordinates given.
    void setNumAdjMine(int r, int c, int adjMines);  // Sets the number of adjacent mines at the spesified cell.

    // Returns a read-only reference to a cell; throws std::out_of_range if out of bounds.
    const Cell& getCell(int r, int c) const; 

    // Gameplay interactions
    void toggleFlag(int r, int c);  // Toggles the flag state also changing the flagCount.
    bool uncoverCell(int r, int c); // Changes to the uncovered state.

    // Resets the board for a new game setting everything to default values.
    void resetBoard();



private:
    int flagCount;          // Stores the flagCount.
    int totalMines;         // Stores total mines on the board.
    Cell board[ROWS][COLL]; // The 2d array that stores the board.

};

#endif 