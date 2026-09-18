// File: title.h
// Project: EECS 581 - Project 1: Minesweeper
// Description: Header definition for Title (QPushButton subclass) and the TitleAppearance enum class, declaring title coordinates, visual state management, custom click signals, and Qt event override. 
// Author: 
// Creation Date: 2026-09-11

#include <QPushButton>

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

    void setState(TileAppearance state);
    TileAppearance getState() const { return visual_state; }

    int row() const { return m_row; }
    int col() const { return m_col; }
    QString toString() const;

signals:
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
    TileAppearance visual_state = TileAppearance::Covered; // sets init state to covered

};