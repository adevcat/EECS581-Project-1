#include "window.h"
#include "gridwidget.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

Window::~Window() = default;

void Window::setupUi()
{
    m_gridWidget = new GridWidget(this);
    setCentralWidget(m_gridWidget);
    setWindowTitle("Minesweeper");
}