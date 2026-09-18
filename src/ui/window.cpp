// File: window.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of Window (QMainWindow subclass), assembling the central widget layout containing InfoBar and GridWidget, setting window geometry, and handling aspect-ratio grid resizing.
// Author: 
// Creation Date: 2026-09-11

#include "window.h"
#include "gridwidget.h"
#include "infobar.h"

#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    /*
     force window dimension
     somewhat added support for dynamic resizing but a bit buggy
     dimension params were just a size that looked okay
    */ 
    setFixedSize(800, 870);

    // create ui
    setupUi();

}

Window::~Window() = default;

void Window::setupUi()
{
    // main widget for window
    auto *central = new QWidget(this);
    setCentralWidget(central);

    // create grid and scoreboard
    m_gridWidget = new GridWidget(central);
    m_infoBar = new InfoBar(central);

    // group infobar and grid together
    auto *gameLayout = new QVBoxLayout();
    gameLayout->setSpacing(5);              
    gameLayout->setContentsMargins(0, 0, 0, 0);
    gameLayout->addWidget(m_infoBar);
    gameLayout->addWidget(m_gridWidget);

    // nest group in outer layout
    auto *outerLayout = new QVBoxLayout(central);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setAlignment(Qt::AlignCenter);
    outerLayout->addLayout(gameLayout);

    setWindowTitle("Minesweeper");
}

void Window::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    //get min of window width/height and set grid to it
    int side = qMin(width(), height()); 
    side = qMax(side, 300); // prevent grid from becoming too small

    m_gridWidget->setFixedSize(side, side);
}