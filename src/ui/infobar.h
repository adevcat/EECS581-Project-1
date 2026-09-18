// File: infobar.h
// Project: EECS 581 - Project 1: Minesweeper
// Description: Header definition for InfoBar, declaring QLabel subclass used to track and display the mine counter and elapsed time. 
// Author: 
// Creation Date: 2026-09-11

#include <QLabel>

class InfoBar : public QLabel
{
    Q_OBJECT

public:
    explicit InfoBar(QWidget *parent = nullptr);

    void setMineCount(int count);
    void setTime(int seconds);

private:
    int m_mineCount = 0;
    int m_time = 0;

    void updateText();
};