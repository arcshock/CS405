/*
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: Main function for managing the neural network.
 * CS 405 Intro to A.I.
 */
#include "neuralnet.h"
#include "board.h"
#include "timing.h"
#include <array>
#include <string>
#include <functional>

int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	Board firstBoard;
	firstBoard.BoardInit();
	firstBoard.makeMove(0,0);
	
	std::function<void()> functionToTime = std::bind(&Board::printBoard, &firstBoard);

	testFunction(functionToTime);

	return 0;
}
