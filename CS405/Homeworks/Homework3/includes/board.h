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
};

class Board {
public:
	Board();
	void BoardInit();
	void printBoard();
private:
	struct cellInfo {
		bool red;
		bool black;
		bool king;
		bool empty;
	};

	void printCellTop();
	void printCellSpace();
	std::array< std::array<CellInfo, 8>, 8> boardRep_m;
};

#endif //BOARD_H
