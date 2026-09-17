/**
 * @file cell.h
 * @brief Defines the Cell struct and CellState enum for the Minesweeper game.
 * @author Zackary Rhodes
 * @date 2026-09-16
 * 
 * Defines the core state tracking variables (COVERED, UNCOVERED, FLAGGED) 
 * and inline helper methods for individual board cells.
 */
#ifndef CELL_H
#define CELL_H
#include <string>

enum CellState{
    COVERED,
    UNCOVERED,
    FLAGGED,
    
};
struct Cell
{
    CellState state = CellState::COVERED;
    bool hasMine = false;
    int numOfAdjacentMines = 0;

    //Returns true if the state of the cell is "Flagged".
    bool isFlagged() const{
        return state == CellState::FLAGGED;
    }

    //Returns true if the state of the cell is "Uncovered".
    bool isUncovered() const{
        return state == CellState::UNCOVERED;
    }

    //Returns true if the state of the cell is "Covered".
    bool isCovered() const{
        return state == CellState::COVERED;
    }

    //Toggles the flag feature changing states from "Flagged" to "Covered" and vise versa
    void toggleFlag(){
        if(state == COVERED){
            state = CellState::FLAGGED;
            
        }
        else if(state == CellState::FLAGGED){
            state = CellState::COVERED;
        }
    }

    //Changes the "Hidden" state to "Uncovered"
    void Uncover(){
        if(state == CellState::COVERED){
            state = CellState::UNCOVERED;
        }
    }
};
#endif 