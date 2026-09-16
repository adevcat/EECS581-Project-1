#include "logicHandler.h"
#include <utility>
#include <vector>


LogicHandler::LogicHandler(Board& board): board(board) {}

std::vector<std::pair<int, int>> LogicHandler::handleClick(int row, int col, ClickType clickType) {
	std::vector<std::pair<int, int>> changedCells;

	if( !board.isValidCoordinate(row, col) ) {
		return changedCells;
	}

	const Cell& cell = board.getCell(row, col);

	if( clickType == ClickType::Right ) {
		if( cell.isCovered() || cell.isFlagged() ) {
			board.toggleFlag(row, col);
			changedCells.emplace_back(row, col);
		}
		return changedCells;
	}

	if (!cell.isCovered()) {
		return changedCells;
	}

	if (board.uncoverCell(row, col)) {
		changedCells.emplace_back(row, col);
	}

	if (!cell.hasMine && cell.numOfAdjacentMines == 0) {
		revealConnectedCells(row, col, changedCells);
	}

	return changedCells;
}


"""
int LogicHandler::asignNum(int row, int col){
    count = 0;
	for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
		for (int colOffset = -1; colOffset <= 1; ++colOffset) {

			if (rowOffset == 0 && colOffset == 0) {
				continue;
			}


			const int neighborRow = row + rowOffset;
			const int neighborCol = col + colOffset;

			if (!board.isValidCoordinate(neighborRow, neighborCol)) {
				continue;
			}

			const Cell& neighbor = board.getCell(neighborRow, neighborCol);
            if (neighbor)
        }
    }
    reutrn count;
}
"""

void LogicHandler::revealConnectedCells(int row, int col, std::vector<std::pair<int, int>>& changedCells) {
	for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
		for (int colOffset = -1; colOffset <= 1; ++colOffset) {

			if (rowOffset == 0 && colOffset == 0) {
				continue;
			}

			const int neighborRow = row + rowOffset;
			const int neighborCol = col + colOffset;

			if (!board.isValidCoordinate(neighborRow, neighborCol)) {
				continue;
			}

			const Cell& neighbor = board.getCell(neighborRow, neighborCol);

			if (!board.uncoverCell(neighborRow, neighborCol)) {
				continue;
			}

			changedCells.emplace_back(neighborRow, neighborCol);

			if (neighbor.numOfAdjacentMines == 0) {
				revealConnectedCells(neighborRow, neighborCol, changedCells);
			}
		}
	}

}
