/**
 * @file board.cpp
 * @brief Implementation of the Board class for grid logic and state synchronization.
 * @author Zackary Rhodes
 * @date 2026-09-16
 * 
 * Contains full implementations for grid initialization, flag tracking, 
 * boundary checks with exception handling, cell uncovering, and board resetting.
 */
#include "board.h"
#include <iostream>
#include <stdexcept>

// Default constructor initializes board counters to zero.
Board::Board(){
    totalMines = 0;
    flagCount = 0;
}

// Parameterized constructor sets total mines for the game.
Board::Board(int numMines){
    totalMines = numMines;
    flagCount = 0;
}

// Checks if the coordinates given are valid and within the bounds of the grid.
bool Board::isValidCoordinate(int r, int c) const{
    if(r >= 0 && r < ROWS){
        if(c >=0 && c < COLL){
            return true;
        }
    }
    return false;
}

// This Changes the 2d arrays hasMine to true as long as the input is valid.
void Board::placeMine(int r, int c){
    if(isValidCoordinate(r,c)){
        board[r][c].hasMine = true;
    }
}

// This changes the 2d arrays numOfAdjecentMines to whatever the parameter was given in adjMines.
void Board::setNumAdjMine(int r, int c, int adjMines){
    if(isValidCoordinate(r,c)){
        board[r][c].numOfAdjacentMines = adjMines;
    }    
}

// Returns the total number of mines on the board.
int Board::getTotalMines() const{
    return totalMines;
}

// Returns the total number of flags on the board.
int Board::getTotalFlags() const{
    return flagCount;
}

// Returns a read-only reference to a cell; throws std::out_of_range if out of bounds.
const Cell& Board::getCell(int r, int c) const{
    if (!isValidCoordinate(r, c)) {
        throw std::out_of_range("Board coordinates out of bounds!");
    }
    return board[r][c];
}

// Toggles the flag state also changing the flagCount.
void Board::toggleFlag(int r, int c){
    if(isValidCoordinate(r,c)){
        if (board[r][c].state == CellState::COVERED) {
            flagCount++;
        } else if (board[r][c].state == CellState::FLAGGED) {
            flagCount--;
        }
        board[r][c].toggleFlag();
    }

}

// Changes the board[r][c] to the uncovered state as long as the row and coll is valid and its state is covered.
 bool Board::uncoverCell(int r, int c){
    if(!isValidCoordinate(r,c)){
        return false;
    }
    // Checks to make sure the only state getting uncovered is the covered state.
    if(board[r][c].state != CellState::COVERED){
        return false;
    }

    board[r][c].state = CellState::UNCOVERED;

    return true;
 }
 
// Resets the board to the default values and sets flagCount to 0.
 void Board::resetBoard(){
    flagCount = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLL; j++){
            board[i][j] = Cell();
        }
    }
 }







