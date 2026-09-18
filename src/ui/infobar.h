// File: infobar.h
// Project: EECS 581 - Project 1: Minesweeper
// Description: Header definition for InfoBar, declaring QLabel subclass used to track and display the mine counter and elapsed time. 
// Author: 
// Creation Date: 2026-09-11

/**
 * @file infobar.h
 * @brief Declares InfoBar, the status readout above the Minesweeper grid.
 * @author Chissl (original label), Will Godderz (status wiring + documentation)
 * @date 2026-09-17
 *
 * InfoBar shows the two readouts the specification requires: the remaining mine
 * count (total mines minus flags placed) and a plain-language status indicator
 * reading "Playing", "Victory!" or "Game Over: Loss".
 *
 * Inputs:  setMineCount(int) and setStatus(GameState), driven by GridWidget.
 * Outputs: the rendered label text.
 *
 * External sources: status indicator added with assistance from Claude
 * (Anthropic), a generative AI assistant, 2026-09-17.
 */
#ifndef INFOBAR_H
#define INFOBAR_H

#include "logicHandler.h"

#include <QLabel>

class InfoBar : public QLabel
{
    Q_OBJECT

public:
    explicit InfoBar(QWidget *parent = nullptr);

    // Remaining mines to find: total mines minus flags currently placed.
    void setMineCount(int count);

    // Current game progress, rendered as the status indicator.
    void setStatus(GameState state);

    // Elapsed game time in seconds. Retained from the original InfoBar for the
    // timer feature; not yet driven by a QTimer.
    void setTime(int seconds);

private:
    int m_mineCount = 0;
    int m_time = 0;
    GameState m_state = GameState::Playing;

    void updateText();
};

#endif
