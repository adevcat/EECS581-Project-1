#include "tile.h"

#include <QMouseEvent>


Tile::Tile(int row, int col, QWidget *parent)
    : QPushButton(parent), 
    m_row(row), 
    m_col(col),
    visual_state()
{
    updateAppearance();
    setIconSize(QSize(32, 32));
    setFixedSize(50, 50);

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
            setIcon(QIcon());
            setStyleSheet("background-color: gray;");
            break;
        case TileAppearance::Uncovered_empty:
            setIcon(QIcon());
            setStyleSheet("background-color: white;");
            break;
        case TileAppearance::Flagged:
            setStyleSheet("background-color: gray;");
            setIcon(QIcon(":/icons/flag.png"));
            break;
        case TileAppearance::Uncovered_mine:
            setStyleSheet("background-color: white;");
            setIcon(QIcon(":/icons/mine.png"));
            break;
    }

    QIcon icon(":/icons/flag.png");
    qDebug() << "Icon null?" << icon.isNull();
} 