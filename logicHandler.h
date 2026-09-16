#ifndef LOGIC_HANDLER_H
#define LOGIC_HANDLER_H

#include "board.h"
#include <utility>
#include <vector>

class LogicHandler {
public:
    enum class ClickType {
        Left,
        Right
    };

    LogicHandler(Board& board);

    std::vector<std::pair<int, int>> handleClick(int row, int col, ClickType clickType);
    // int assignNum(int row, int col)
private:
    Board& board;

    void revealConnectedCells(
        int row,
        int col,
        std::vector<std::pair<int, int>>& changedCells);
};

#endif