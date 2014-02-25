/*
 * Author: Bucky Frost
 * File: board.cpp
 * Purpose: Implementation file for checkers board representation.
 */

#include "board.h"

/* == Function printCellTop ===============
 *
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
	auto boardHeight = 8;

	for (auto i = 0; i < boardHeight; ++i) {
		printCellTop();
		for (auto j = 0; j < 2; ++j) {
			printCellSpace();
		}
	}
	printCellTop();
}
