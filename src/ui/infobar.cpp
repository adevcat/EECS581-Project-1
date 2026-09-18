// File: infobar.cpp
// Project: EECS 581 - Project 1: Minesweeper
// Description: Implementation of InfoBar, managing formatted display of remaining mine counts and elapsed game time using QLabel.
// Author: 
// Creation Date: 2026-09-11

#include "infobar.h"
InfoBar::InfoBar(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    QFont font = this->font();
    font.setPointSize(32);
    font.setBold(true);
    setFont(font);

    updateText();
}

void InfoBar::setMineCount(int count)
{
    m_mineCount = count;
    updateText();
}

void InfoBar::setTime(int seconds)
{
    m_time = seconds;
    updateText();
}

void InfoBar::updateText()
{
    setText(QString("Mines: %1\tTime: %2").arg(m_mineCount).arg(m_time));
}