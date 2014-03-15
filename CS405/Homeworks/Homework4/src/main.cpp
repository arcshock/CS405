/*
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: Main function for managing the neural network.
 * CS 405 Intro to A.I.
 */
#include "neuralnet.h"
#include "board.h"
#include "timing.h"
#include <iostream>
#include <array>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	Board firstBoard;
	firstBoard.BoardInit();
	firstBoard.printBoard();
	firstBoard.makeMove(0,0);
	firstBoard.printBoard();
	
	return 0;
}
