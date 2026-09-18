// File: Cgridwidget.h
// Project: EECS 581 - Project 1: Minesweeper
// Description: Header definition for GridWidget, declaring the 10x10board layout, title matrix storage, 
//              and Qt signals/slots for title click routing.
// Author: 
// Creation Date: 2026-09-11

#include <QWidget>
#include <QVector>

class Tile;

class GridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);

    static constexpr int kGridSize = 10;


signals:
    void tileClicked(Tile *tile, Qt::MouseButton clickType);
    
private slots:
    void handleTileClicked(Tile *tile, Qt::MouseButton clickType);

private:
    void setupUi();
    
    QVector<QVector<Tile*>> m_tiles;
};