/* File: title.h
Project: EECS 581 - Project 1: Minesweeper
Description: Header definition for Title (QPushButton subclass) and the TitleAppearance enum class, declaring title coordinates, visual state management, custom click signals, and Qt event override. 
Author: 
Creation Date: 2026-09-11*/

/**
 * @file tile.h
 * @brief Declares Tile, a single clickable cell button in the Minesweeper grid.
 * @author Chissl (original widget), Will Godderz (numbers + documentation)
 * @date 2026-09-17
 *
 * Tile is a QPushButton that knows its own (row, col) and renders one of four
 * appearances: covered, flagged, uncovered-empty (optionally showing a 1-8
 * adjacent-mine count) or uncovered-mine. It holds no game rules; it emits a
 * click signal upward and is told what to display.
 *
 * Inputs:  grid coordinates at construction; setState() calls from GridWidget;
 *          mouse press events from Qt.
 * Outputs: the tileClick(Tile*, Qt::MouseButton) signal, and its own rendering.
 *
 * External sources: adjacent-mine number rendering and colour table added with
 * assistance from Claude (Anthropic), a generative AI assistant, 2026-09-17.
 * The classic per-number colour scheme mirrors the original Microsoft
 * Minesweeper palette, reimplemented from observation, not copied.
 */
#ifndef TILE_H
#define TILE_H

#include <QPushButton>

// The four visual states a tile can present to the player.
enum class TileAppearance {
    Covered,
    Flagged,
    Uncovered_empty,
    Uncovered_mine
};

class Tile : public QPushButton
{
    Q_OBJECT

public:
    explicit Tile(int row, int col, QWidget *parent = nullptr);

    // Sets what the tile shows. adjacentMines is only read for Uncovered_empty,
    // where 0 renders blank and 1-8 renders a coloured digit.
    void setState(TileAppearance state, int adjacentMines = 0);
    TileAppearance getState() const { return visual_state; }

    int row() const { return m_row; }
    int col() const { return m_col; }
    QString toString() const;

signals:
    // Emitted on every press; GridWidget forwards this to the Game Logic.
    void tileClick(Tile *tile, Qt::MouseButton clickType);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void updateAppearance();
    void updateTile(const char *state, QIcon icon = QIcon());
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void handleClick();

private:
    int m_row;
    int m_col;
    int mine_count = 0;                                    // adjacent mine count, 0-8
    TileAppearance visual_state = TileAppearance::Covered; // sets init state to covered

    // Scales the icon and the digit font to the current button size.
    void rescaleContents();
};

#endif
