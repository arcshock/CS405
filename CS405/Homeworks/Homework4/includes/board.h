/*
 * Author: Bucky Frost
 * File: board.cpp
 * Purpose: Header file for checkers board representation.
 */

#ifndef BOARD_H
#define BOARD_H 

#include <iostream>
#include <array>
#include <utility>


class Board {
public:
	typedef std::pair<unsigned int, unsigned int> coordinate;

	Board();
	void BoardInit();
	void printBoard();
	double evalBoard(int color);
	void makeMove(coordinate cellLocation);

private:
	const static int BOARD_LENGTH = 8;
	
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

	bool isEmpty(coordinate cellLocation);
	bool isKing(coordinate cellLocation);
	void printCellTop() const;
	void printCellSpace() const;
	std::array< std::array<CellInfo, BOARD_LENGTH>, BOARD_LENGTH> boardRep_m;

	
};

#endif /* BOARD_H */
