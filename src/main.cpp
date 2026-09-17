/**
 * @file main.cpp
 * @brief Application entry point for the Minesweeper game.
 * @author Chissl
 * @date 2026-09-17
 *
 * Creates the QApplication, loads the compiled icon resources, and shows the
 * main Window, which in turn prompts for a mine count and starts the game.
 *
 * Inputs:  standard argc/argv command line arguments (unused by the game).
 * Outputs: process exit code from the Qt event loop.
 *
 * External sources: none. Original code.
 */
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
