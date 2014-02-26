/*
 * Author: Bucky Frost
 * File: board.cpp
 * Purpose: Implementation file for checkers board representation.
 */

#include "board.h"

/* == Class Board Default CTR =============
 *
 * ======================================== */
Board::Board()
{
	for (auto i = 0; i < boardRep_m.size(); ++i) {
		boardRep_m[0][i] = CellInfo();
	}
}


/* == Class Board Initilizer CTR ==========
 *
 * ======================================== */
void Board::BoardInit()
{
	for (auto i = 0; i < boardRep_m.size(); ++i) {
		for (auto j = 0; j < boardRep_m[i].size(); ++j) {
			boardRep_m[i][j] = CellInfo();
		}
	}

	for (auto i = 0; i <= 2; ++i) {
		for (auto j = i%2; j <= 6; j+=2) {
			boardRep_m[i][j].red = true;
			boardRep_m[i][j].empty = false;
		}
	}

	for (auto i = 5; i <= 7; ++i) {
		for (auto j = i%2; j <= 6; j+=2) {
			boardRep_m[i][j].black = true;
			boardRep_m[i][j].empty = false;
		}
	}
		
}

/* == Function printCellTop ===============
 * Helper function for printBoard.
 * Precondition: None.
 *
 * Post Condition: prints out string of '+---+---+'
 * ======================================== */
void Board::printCellTop()
{
	for (auto i = 0; i < 8; ++i) {
		std::cout << "+";

		for (auto j = 0; j < 5; ++j) {
			std::cout << "-";
		}
	}
	std::cout << "+" << std::endl;
}

/* == Function printCellSpace =============
 * Helper function for printBoard.
 *
 * Precondition: None.
 *
 * Post Condition: prints out string of '|   |   |'
 * ======================================== */
void Board::printCellSpace()
{
	for (auto i = 0; i < 8; ++i) {
		std::cout << "|";

		for (auto j = 0; j < 5; ++j) {
			std::cout << " ";
		}
	}
	std::cout << "|" << std::endl;
}

/* == Function printBoard ==================
 * 
 * Precondition: None.
 *
 * Post Condition: Prints out a checkers board rep to std out.
 * ========================================= */
void Board::printBoard()
{
	for (auto i = 0; i < boardRep_m.size(); ++i) {
		for (auto j = 0; j < boardRep_m[0].size(); ++j) {
			if (boardRep_m[i][j].red) {
				std::cout << "r";
			} else if (boardRep_m[i][j].black) {
				std::cout << "b";
			} else {
				std::cout << " ";
			}

		}
		std::cout << std::endl;
	}
}
