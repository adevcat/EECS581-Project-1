// File: gridwidget.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of GridWidget, responsible for generating and laying out the title grid in a QGridLayout, 
//              managing title resize stretching, and handling title click signal interactions.
// Author: 
// Creation Date: 2026-09-11


#include "gridwidget.h"
#include "tile.h"

#include <QGridLayout>

GridWidget::GridWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

// draws grid
void GridWidget::setupUi()
{
    auto *layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    m_tiles.resize(kGridSize);
    for (int row = 0; row < kGridSize; ++row) {
        m_tiles[row].resize(kGridSize);
        for (int col = 0; col < kGridSize; ++col) {
            auto *tile = new Tile(row, col, this);

            connect(tile, &Tile::tileClick, this, &GridWidget::handleTileClicked);

            layout->addWidget(tile, row, col);
            m_tiles[row][col] = tile;
        }
    }

    // resize grid evenly when changing window size
    for (int i = 0; i < kGridSize; ++i) {
        layout->setRowStretch(i, 1);
        layout->setColumnStretch(i, 1);
    }
}

// TODO create tileclicked signal to pass onto handler
// Current function is just to test UI
void GridWidget::handleTileClicked(Tile *tile, Qt::MouseButton clickType) {
    qDebug() << tile->toString() << "clicked with" << clickType;
    if (clickType == Qt::RightButton) {
        tile->setState(TileAppearance::Flagged);
    }
    if (clickType == Qt::LeftButton) {
        if (tile->col() == 1) {
            tile->setState(TileAppearance::Uncovered_mine);
        } else {
            tile->setState(TileAppearance::Uncovered_empty);
        }
    }
}