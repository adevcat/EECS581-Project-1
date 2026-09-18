// File: title.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of Title (QPushButton subclass), handling mouse press events (distinhuishing lieft-click uncover vs. right-click flag),
//              dyanmic stylesheet states, icon rendering, and responsive resizing. 
// Creation Date: 2026-09-11

#include "tile.h"

#include <QMouseEvent>
#include <QFile>
#include <QStyle>


Tile::Tile(int row, int col, QWidget *parent)
    : QPushButton(parent), 
    m_row(row), 
    m_col(col),
    visual_state()
{
    // set button style
    setStyleSheet(
        "Tile { "
        "   border: 2px solid black; "
        "   margin: 0px; "
        "   padding: 0px; "
        "} "
        "Tile[state=\"covered\"]    { background-color: gray; } "
        "Tile[state=\"uncovered\"]   { background-color: white; } "
    );

    int iconDim = static_cast<int>(qMin(width(), height()) * 0.8);
    setIconSize(QSize(iconDim, iconDim));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    updateAppearance();

    // add trigger functions
    connect(this, &QPushButton::clicked, this, &Tile::handleClick);
}

// handle right clicks using custom handler; QPushButton only handles right clicks by default
void Tile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit tileClick(this, Qt::RightButton);
        return;
        // TODO add tile marker
    }

    QPushButton::mousePressEvent(event);
}

// handle left clicks using default handler
void Tile::handleClick() {
    emit tileClick(this, Qt::LeftButton);
}

// debug function to resolve coords
QString Tile::toString() const {
    return QString("(%1, %2)").arg(m_row).arg(m_col);
}

void Tile::setState(TileAppearance state) {
    visual_state = state;
    updateAppearance();
}

void Tile::updateAppearance() {
    switch (visual_state) {
        case TileAppearance::Covered:
            updateTile("covered");
            break;
        case TileAppearance::Uncovered_empty:
            updateTile("uncovered");
            break;
        case TileAppearance::Flagged:
            updateTile("covered", QIcon(":/icons/flag.png"));
            break;
        case TileAppearance::Uncovered_mine:
            updateTile("uncovered", QIcon(":/icons/mine.png"));
            break;
    }
} 

void Tile::updateTile(const char *state, QIcon icon) {
    setIcon(icon);
    setProperty("state", state);
    style()->unpolish(this);
    style()->polish(this);
}

// resize icons when resizing buttons
void Tile::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
    int iconDim = static_cast<int>(qMin(width(), height()) * 0.8);
    setIconSize(QSize(iconDim, iconDim));
}