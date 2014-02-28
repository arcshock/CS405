/*
 * Author: Bucky Frost
 * File: board.cpp
 * Purpose: Header file for checkers board representation.
 */

#ifndef BOARD_H
#define BOARD_H 

#include <iostream>
#include <array>

struct CellInfo {
	bool red;
	bool black;
	bool king;
	bool empty;

	CellInfo() {
		red = false;
		black = false;
		king = false;
		empty = true;
	}

	void emptyCell() {
		red = false;
		black = false;
		king = false;
		empty = true;
	}
};

class Board {
public:
	Board();
	void BoardInit();
	void printBoard();
	double evalBoard(int color);
	void makeMove(unsigned int row, unsigned int column);
private:
	void printCellTop();
	void printCellSpace();
	std::array< std::array<CellInfo, 8>, 8> boardRep_m;
};

#endif //BOARD_H
