// File: window.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of Window (QMainWindow subclass), assembling the central widget layout containing InfoBar and GridWidget, setting window geometry, and handling aspect-ratio grid resizing.
// Author: 
// Creation Date: 2026-09-11

/**
 * @file window.cpp
 * @brief Implementation of the top-level application window.
 * @author Jaydee Brown (original window), Will Godderz (game setup + documentation)
 * @date 2026-09-17
 *
 * Builds the window layout, prompts for the mine count at startup and on each
 * New Game, and connects GridWidget's status signals to the InfoBar.
 *
 * Inputs:  player mine-count selection; Qt events.
 * Outputs: the rendered window; new-game commands to GridWidget.
 *
 * External sources: mine-count prompt and signal wiring added with assistance
 * from Claude (Anthropic), a generative AI assistant, 2026-09-17.
 */
#include "window.h"
#include "gridwidget.h"
#include "infobar.h"

#include <QInputDialog>
#include <QPushButton>
#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(300, 400);
    resize(600,700);

    // create ui
    setupUi();

    // Ask for the mine count and deal the first board.
    m_gridWidget->startNewGame(askMineCount());
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

    m_newGameButton = new QPushButton("New Game", central);
    m_newGameButton->setFixedHeight(40);

    // Grid reports state changes; the info bar simply displays them.
    connect(m_gridWidget, &GridWidget::flagsRemainingChanged,
            m_infoBar, &InfoBar::setMineCount);
    connect(m_gridWidget, &GridWidget::statusChanged,
            m_infoBar, &InfoBar::setStatus);
    connect(m_newGameButton, &QPushButton::clicked,
            this, &Window::promptNewGame);

    // group infobar, grid and button together
    auto *gameLayout = new QVBoxLayout();
    gameLayout->setSpacing(5);
    gameLayout->setContentsMargins(0, 0, 0, 0);
    gameLayout->addWidget(m_infoBar);
    gameLayout->addWidget(m_gridWidget);
    gameLayout->addWidget(m_newGameButton);

    // nest group in outer layout
    auto *outerLayout = new QVBoxLayout(central);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setAlignment(Qt::AlignCenter);
    outerLayout->addLayout(gameLayout);

    setWindowTitle("Minesweeper");
}

// Modal prompt constrained to the 10-20 range the specification requires, so an
// out-of-range mine count cannot reach the Game Logic at all.
int Window::askMineCount()
{
    bool ok = false;
    const int mines = QInputDialog::getInt(
        this,
        "New Game",
        "Number of mines (10 - 20):",
        10,   // default
        10,   // minimum
        20,   // maximum
        1,    // step
        &ok);

    // Cancelling still starts a playable game rather than an empty window.
    return ok ? mines : 10;
}

void Window::promptNewGame()
{
    m_gridWidget->startNewGame(askMineCount());
}

void Window::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    //get min of window width/height and set grid to it
    int side = qMin(width(), height());
    side = qMax(side, 300); // prevent grid from becoming too small

    m_gridWidget->setFixedSize(side, side);
}
