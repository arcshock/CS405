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
};

class Board {
public:
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
	std::array<std::array<cellInfo, 8>, 8> boardRep_m;
};

#endif //BOARD_H
