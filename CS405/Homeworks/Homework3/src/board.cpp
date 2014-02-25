/*
 * Author: Bucky Frost
 * File: board.cpp
 * Purpose: Implementation file for checkers board representation.
 */

#include "board.h"
/* == Function printBoard ==================
 * 
 * Precondition: None.
 *
 * Post Condition: Prints out a checkers board rep to std out.
 * ========================================= */

void printCellTop()
{
	for (auto i = 0; i < 8; ++i) {
		std::cout << "+";

		for (auto j = 0; j < 5; ++j) {
			std::cout << "-";
		}
	}
	std::cout << "+" << std::endl;
}

void printCellSpace()
{
	for (auto i = 0; i < 8; ++i) {
		std::cout << "|";

		for (auto j = 0; j < 5; ++j) {
			std::cout << " ";
		}
	}
	std::cout << "|" << std::endl;
}

void printBoard()
{
	auto boardHeight = 8;

	for (auto i = 0; i < boardHeight; ++i) {
		printCellTop();
		printCellSpace();
	}
	printCellTop();
}
