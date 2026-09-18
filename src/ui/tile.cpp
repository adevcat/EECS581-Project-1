// File: title.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of Title (QPushButton subclass), handling mouse press events (distinhuishing lieft-click uncover vs. right-click flag),
//              dyanmic stylesheet states, icon rendering, and responsive resizing. 
// Creation Date: 2026-09-11

/**
 * @file tile.cpp
 * @brief Implementation of the Tile cell button.
 * @author Jaydee Brown (original widget), Will Godderz (numbers + documentation)
 * @date 2026-09-17
 *
 * Handles tile styling, left/right click detection, and rendering of the four
 * tile appearances including the 1-8 adjacent-mine digits.
 *
 * Inputs:  setState() from GridWidget; Qt mouse and resize events.
 * Outputs: tileClick signal; the rendered button.
 *
 * External sources: number rendering, colour table and font scaling added with
 * assistance from Claude (Anthropic), a generative AI assistant, 2026-09-16.
 */
#include "tile.h"

#include <QMouseEvent>
#include <QFile>
#include <QStyle>

// Classic Minesweeper digit colours, indexed 1-8. Index 0 is unused because a
// zero-adjacency tile renders blank.
static const char *kNumberColors[9] = {
    "",        // 0 - never drawn
    "#0000ff", // 1 blue
    "#008000", // 2 green
    "#ff0000", // 3 red
    "#000080", // 4 navy
    "#800000", // 5 maroon
    "#008080", // 6 teal
    "#000000", // 7 black
    "#808080"  // 8 grey
};

Tile::Tile(int row, int col, QWidget *parent)
    : QPushButton(parent),
    m_row(row),
    m_col(col),
    mine_count(0),
    visual_state(TileAppearance::Covered)
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

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rescaleContents();
    updateAppearance();

    // add trigger functions
    connect(this, &QPushButton::clicked, this, &Tile::handleClick);
}

// handle right clicks using custom handler; QPushButton only handles left clicks by default
void Tile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit tileClick(this, Qt::RightButton);
        return;
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

// Record the new appearance plus its digit, then repaint.
void Tile::setState(TileAppearance state, int adjacentMines) {
    visual_state = state;
    mine_count = adjacentMines;
    updateAppearance();
}

void Tile::updateAppearance() {
    switch (visual_state) {
        case TileAppearance::Covered:
            setText(QString());
            updateTile("covered");
            break;

        case TileAppearance::Uncovered_empty:
            // 0 adjacent mines stays blank; 1-8 show a coloured digit.
            if (mine_count > 0 && mine_count <= 8) {
                setText(QString::number(mine_count));
            } else {
                setText(QString());
            }
            updateTile("uncovered");
            break;

        case TileAppearance::Flagged:
            setText(QString());
            updateTile("covered", QIcon(":/icons/flag.png"));
            break;

        case TileAppearance::Uncovered_mine:
            setText(QString());
            updateTile("uncovered", QIcon(":/icons/mine.png"));
            break;
    }
}

// Applies the icon and swaps the "state" style property so the stylesheet
// repaints the background. Colour for the digit is set here because a dynamic
// property cannot drive per-number text colour on its own.
void Tile::updateTile(const char *state, QIcon icon) {
    setIcon(icon);
    setProperty("state", state);

    if (!text().isEmpty() && mine_count > 0 && mine_count <= 8) {
        setStyleSheet(QString(
            "Tile { border: 2px solid black; margin: 0px; padding: 0px;"
            " background-color: white; color: %1; font-weight: bold; }")
            .arg(kNumberColors[mine_count]));
    } else {
        setStyleSheet(
            "Tile { "
            "   border: 2px solid black; "
            "   margin: 0px; "
            "   padding: 0px; "
            "} "
            "Tile[state=\"covered\"]    { background-color: gray; } "
            "Tile[state=\"uncovered\"]   { background-color: white; } "
        );
    }

    style()->unpolish(this);
    style()->polish(this);
}

// resize icons and digit font when resizing buttons
void Tile::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
    rescaleContents();
}

// Keep the icon at 80% of the button and the digit at roughly 55%, so both stay
// legible as the window is resized.
void Tile::rescaleContents() {
    const int side = qMin(width(), height());

    setIconSize(QSize(static_cast<int>(side * 0.8), static_cast<int>(side * 0.8)));

    QFont f = font();
    f.setPointSize(qMax(8, static_cast<int>(side * 0.45)));
    f.setBold(true);
    setFont(f);
}
