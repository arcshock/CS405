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
	for (int ii = boardRep_m.size() - 1; ii >= 0; --ii) {
		boardRep_m[0][ii] = CellInfo();
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

/* == Function printBoard ==================
 * 
 * Precondition: None.
 *
 * Post Condition: Prints out a checkers board rep to std out.
 * ========================================= */
void Board::printBoard() 
{
	for (int row = boardRep_m.size() - 1; row >= 0; --row) {
		for (auto column = 0; column < boardRep_m[0].size(); ++column) {
			if (boardRep_m[row][column].red) {
				isKing(coordinate(column,row)) ? std::cout << "R" : std::cout << "r";
			} else if (boardRep_m[row][column].black) {
				isKing(coordinate(column,row)) ? std::cout << "B" : std::cout << "b";
			} else {
				std::cout << " ";
			}

		}
		std::cout << std::endl;
	}
}

// TODO Move to the neuralNetwork
/* == Function evalBoard ================== 
 *
 * Returns a double that signifies how well the board is in 
 * favor of the specified color.
 *
 * Precondition: color must either be 1 or 2. 1 for red, 2 for black.
 *
 * Post Condition: Returns a double for the board standing in the color.
 * ======================================== */
double Board::evalBoard(int color) 
{
	auto numberOfPieces = 0;
	auto numberOfKings = 0;
	auto kingFavor = 1.42;

	for (auto i = 0; i < boardRep_m.size(); ++i) {
		for (auto j = 0; j < boardRep_m[0].size(); ++j) {
			if (color == 1) {
				if (boardRep_m[i][j].red)
					++numberOfPieces;
				if (boardRep_m[i][j].king)
					++numberOfKings;
			}

			if (color == 2) {
				if (boardRep_m[i][j].black)
					++numberOfPieces;
				if (boardRep_m[i][j].king)
					++numberOfKings;
			}	
		}
	}

	return numberOfPieces + numberOfKings*kingFavor;
}

void Board::makeMove(coordinate cellLocation)
{
	auto row = cellLocation.second;
	auto column = cellLocation.first;

	if (isKing(cellLocation)) {
		if (isEmpty(coordinate(column - 1, row - 1)))
			std::swap(boardRep_m[row][column], boardRep_m[row - 1][column - 1]);
		else if (isEmpty(coordinate(column - 1, row + 1)))
			std::swap(boardRep_m[row][column], boardRep_m[row - 1][column + 1]);
		else if (isEmpty(coordinate(column + 1, row - 1)))
			std::swap(boardRep_m[row][column], boardRep_m[row + 1][column - 1]);
		else if (isEmpty(coordinate(column + 1, row + 1)))
			std::swap(boardRep_m[row][column], boardRep_m[row + 1][column + 1]);
	}

		
}




bool Board::isEmpty(coordinate cellLocation)
{
	auto row = cellLocation.second;
	auto column = cellLocation.first;

	return boardRep_m[row][column].empty;
}

bool Board::isKing(coordinate cellLocation)
{
	auto row = cellLocation.second;
	auto column = cellLocation.first;

	return boardRep_m[row][column].king;
}
