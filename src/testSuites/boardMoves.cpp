/*
 * Author: Bucky Frost
 * File: boardMoves.cpp
 * Purpose: Main function for testing the moves of the board pieces.
 * CS 405 Intro to A.I.
 */
#include "board.h"
#include <iostream>
#include <utility>

int main()
{
	const int BOARD_SIZE = 8;
	Board testingBoard;
	testingBoard.BoardInit();
	
	for (int ii = 0; ii < BOARD_SIZE; ++ii) {
		for (int jj = 0; jj < BOARD_SIZE; ++jj) {
			std::pair<unsigned int, unsigned int> location(jj,ii);
			std::cout << "Testing location, (" << jj << "," << ii << ")." << std::endl;
			testingBoard.makeMove(location);
			testingBoard.printBoard();
		}
	}

	return 0;
}
