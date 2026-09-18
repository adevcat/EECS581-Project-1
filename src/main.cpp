// File: main.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Application entry point, initializing QApplication, loading the embedded Qt resource binary for icons, and launching main Window.
// Author: 
// Creation Date: 2026-09-11

#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(resources); // loads icons

    Window window;
    window.show();

    return app.exec();
}