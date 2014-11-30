/**
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */

#include <iostream>
#include <vector>
#include "neural_network.hpp"
#include "minimax.hpp"

int main(int argc, char* argv[])
{
		
	std::vector<int> standard_network = {32, 40, 10, 1};
	std::vector<double> board_state;

	Neural_Network red_player(standard_network);
	Neural_Network white_player(standard_network);

	Checker_Board board;

	board_state = board.get_state();

	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			std::make_pair(row, col);
	red_player.network_evaluate(board_state);

	board.print_board(std::cout);

	while (1) {
		board = minimax(red_player, board, 6, 'r');

		std::cout << std::endl;
		board.print_board(std::cout);

		board = minimax(white_player, board, 6, 'w');
		std::cout << std::endl;
		board.print_board(std::cout);
	}
	return 0;
}
