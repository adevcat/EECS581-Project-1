/**
 * @file logicHandler.h
 * @brief Declares LogicHandler, the Game Logic component of the Minesweeper system.
 * @author Will Godderz
 * @date 2026-09-17
 *
 * LogicHandler sits between the Input Handler (GridWidget) and the Board Manager
 * (Board). It owns every gameplay rule: random mine placement, first-click safety,
 * adjacent-mine computation, recursive reveal of zero-adjacency regions, flag
 * toggling, and win/loss detection. It never touches Qt, so the rules can be unit
 * tested or reused behind a different interface.
 *
 * Inputs:  a Board reference (grid state), plus (row, col, ClickType) per click.
 * Outputs: a vector of {row, col} pairs naming every cell whose state changed,
 *          which the UI uses to repaint only what moved; plus queryable game
 *          state and remaining-flag count.
 *
 */
#ifndef LOGIC_HANDLER_H
#define LOGIC_HANDLER_H

#include "board.h"

#include <random>
#include <utility>
#include <vector>

// which mouse button the player used. Left uncovers, Right toggles a flag.
enum class ClickType {
    Left,
    Right
};

// overall progress of the current game, surfaced to the UI status indicator.
enum class GameState {
    Playing,
    Won,
    Lost
};

// a list of grid coordinates the UI needs to repaint.
using CellList = std::vector<std::pair<int, int>>;

class LogicHandler {
public:
    // binds the handler to an existing Board. The board is not owned or copied.
    explicit LogicHandler(Board& board);

    // a click at (row, col). Returns every cell whose state changed.
    CellList handleClick(int row, int col, ClickType clickType);

    // starts a fresh game on the same board with the given mine count (10-20).
    void reset(int numMines);

    // current game progress, for the status indicator.
    GameState state() const { return m_state; }

    // total mines minus flags placed. May go negative if the player over-flags.
    int flagsRemaining() const;

    // true until the first left click has placed the mines.
    bool minesPlaced() const { return m_minesPlaced; }

private:
    Board& board;          // board manager this handler drives.
    GameState m_state;     // Playing / Won / Lost.
    bool m_minesPlaced;    // =first-click-safe placement.
    std::mt19937 m_rng;    // seeded once per handler for random mine layout.

    // randomly places board.getTotalMines() mines, never on (safeRow, safeCol)
    // none any of its eight neighbours, guaranteeing a safe opening click.
    void placeMines(int safeRow, int safeCol);

    // fills every cell's numOfAdjacentMines after placement is complete.
    void computeAdjacency();

    // counts mines in the eight cells surrounding (row, col).
    int countAdjacentMines(int row, int col) const;

    // recursively uncovers the region connected to a zero-adjacency cell.
    void revealConnectedCells(int row, int col, CellList& changedCells);

    // on a loss, uncovers every mine so the player can see the full layout.
    void revealAllMines(CellList& changedCells);

    // true when every non-mine cell has been uncovered.
    bool allSafeCellsUncovered() const;
};

#endif
