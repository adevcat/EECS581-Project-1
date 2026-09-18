// File: gridwidget.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of GridWidget, responsible for generating and laying out the title grid in a QGridLayout, 
//              managing title resize stretching, and handling title click signal interactions.
// Author: 
// Creation Date: 2026-09-11


/**
 * @file gridwidget.cpp
 * @brief Implementation of the Input Handler and grid renderer.
 * @author Jaydee Brown (original grid), Will Godderz (game wiring + documentation)
 * @date 2026-09-16
 *
 * Builds the labelled grid, routes clicks into LogicHandler, and repaints the
 * cells the logic reports as changed.
 *
 * Inputs:  tile clicks; startNewGame(numMines).
 * Outputs: tile repaints; flagsRemainingChanged and statusChanged signals.
 *
 * External sources: click routing, label headers and repaint logic added with
 * assistance from Claude (Anthropic), a generative AI assistant, 2026-09-16.
 */
#include "gridwidget.h"
#include "tile.h"

#include <QGridLayout>
#include <QLabel>

GridWidget::GridWidget(QWidget *parent)
    : QWidget(parent),
      m_board(),          // constructed first, then bound by reference below
      m_logic(m_board)
{
    setupUi();
}

// draws the grid: column letters A-J across the top, row numbers 1-10 down the
// left, and the 10x10 tile buttons offset by one row/column from those headers.
void GridWidget::setupUi()
{
    auto *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    // column headers A-J, placed in row 0 starting at column 1.
    for (int col = 0; col < kGridSize; ++col) {
        auto *label = new QLabel(QString(QChar('A' + col)), this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-weight: bold;");
        layout->addWidget(label, 0, col + 1);
    }

    // row headers 1-10, placed in column 0 starting at row 1.
    for (int row = 0; row < kGridSize; ++row) {
        auto *label = new QLabel(QString::number(row + 1), this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-weight: bold;");
        layout->addWidget(label, row + 1, 0);
    }

    // the tiles themselves, offset by the header row and column.
    m_tiles.resize(kGridSize);
    for (int row = 0; row < kGridSize; ++row) {
        m_tiles[row].resize(kGridSize);
        for (int col = 0; col < kGridSize; ++col) {
            auto *tile = new Tile(row, col, this);

            connect(tile, &Tile::tileClick, this, &GridWidget::handleTileClicked);

            layout->addWidget(tile, row + 1, col + 1);
            m_tiles[row][col] = tile;
        }
    }

    // headers stay compact; the tile rows and columns share the space evenly.
    layout->setRowStretch(0, 0);
    layout->setColumnStretch(0, 0);
    for (int i = 1; i <= kGridSize; ++i) {
        layout->setRowStretch(i, 1);
        layout->setColumnStretch(i, 1);
    }
}

// begin a new game: rebuild the board, clear every tile, and republish counters.
void GridWidget::startNewGame(int numMines)
{
    m_logic.reset(numMines);
    refreshAllTiles();

    emit flagsRemainingChanged(m_logic.flagsRemaining());
    emit statusChanged(m_logic.state());
}

// Input Handler entry point. validates nothing itself: it converts the Qt button
// into a ClickType, hands the coordinates to the Game Logic, then repaints only
// the cells the logic reports as changed.
void GridWidget::handleTileClicked(Tile *tile, Qt::MouseButton clickType)
{
    if (!tile) {
        return;
    }

    const ClickType click =
        (clickType == Qt::RightButton) ? ClickType::Right : ClickType::Left;

    const GameState before = m_logic.state();
    const CellList changed = m_logic.handleClick(tile->row(), tile->col(), click);

    for (const auto &coord : changed) {
        refreshTile(coord.first, coord.second);
    }

    // flag count only moves on right clicks, but republishing is cheap and keeps the info bar correct after a loss reveals (and unflags) every mine.
    emit flagsRemainingChanged(m_logic.flagsRemaining());

    if (m_logic.state() != before) {
        emit statusChanged(m_logic.state());
    }
}

// translate one Board cell into its Tile appearance.
void GridWidget::refreshTile(int row, int col)
{
    if (row < 0 || row >= kGridSize || col < 0 || col >= kGridSize) {
        return;
    }

    const Cell &cell = m_board.getCell(row, col);
    Tile *tile = m_tiles[row][col];

    if (cell.isFlagged()) {
        tile->setState(TileAppearance::Flagged);
    } else if (cell.isCovered()) {
        tile->setState(TileAppearance::Covered);
    } else if (cell.hasMine) {
        tile->setState(TileAppearance::Uncovered_mine);
    } else {
        tile->setState(TileAppearance::Uncovered_empty, cell.numOfAdjacentMines);
    }
}

// repaint the whole grid, used when a new game resets every cell at once.
void GridWidget::refreshAllTiles()
{
    for (int row = 0; row < kGridSize; ++row) {
        for (int col = 0; col < kGridSize; ++col) {
            refreshTile(row, col);
        }
    }
}
