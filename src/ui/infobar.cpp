// File: infobar.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of InfoBar, managing formatted display of remaining mine counts and elapsed game time using QLabel.
// Author: Jaydee Brown, Will Godderz
// Creation Date: 2026-09-17

/**
 * @file infobar.cpp
 * @brief Implementation of the InfoBar status readout.
 * @author Jaydee Brown (original label), Will Godderz (status wiring + documentation)
 * @date 2026-09-17
 *
 * Renders the remaining mine count and the game status on a single centred line,
 * recolouring the text on a win or loss so the outcome is obvious at a glance.
 *
 * Inputs:  setMineCount(int), setStatus(GameState).
 * Outputs: the rendered label text and colour.
 *
 * External sources: status text and colouring added with assistance from Claude
 * (Anthropic), a generative AI assistant, 2026-09-17.
 */
#include "infobar.h"

InfoBar::InfoBar(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    QFont font = this->font();
    font.setPointSize(24);
    font.setBold(true);
    setFont(font);

    updateText();
}

void InfoBar::setMineCount(int count)
{
    m_mineCount = count;
    updateText();
}

void InfoBar::setStatus(GameState state)
{
    m_state = state;
    updateText();
}

// Retained from the original InfoBar. No QTimer drives this yet, so the readout
// holds at 0; wiring a timer only requires calling this once per second.
void InfoBar::setTime(int seconds)
{
    m_time = seconds;
    updateText();
}

// Compose the single status line. Colour doubles as a second signal of the
// outcome for players who are scanning rather than reading.
void InfoBar::updateText()
{
    QString status;
    QString color;

    switch (m_state) {
        case GameState::Playing:
            status = "Playing";
            color = "blue";
            break;
        case GameState::Won:
            status = "Victory!";
            color = "green";
            break;
        case GameState::Lost:
            status = "Game Over: Loss";
            color = "red";
            break;
    }

    setStyleSheet(QString("color: %1;").arg(color));
    setText(QString("Mines: %1    %2").arg(m_mineCount).arg(status));
}
