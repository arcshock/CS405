/**
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include "neural_network.hpp"
#include "g_neural_network.hpp"
#include "minimax.hpp"
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	std::vector<int> standard_network = {32, 40, 10, 1};
	std::vector<float> board_state;

	Neural_Network red_player(standard_network);
	Neural_Network white_player(standard_network);

	Checker_Board board;

	board_state = board.get_state();

	for (int row = 0; row < 8; ++row)
		for (int col = 0; col < 8; ++col)
			std::make_pair(row, col);
        // Timing
        auto start_cpu = std::chrono::high_resolution_clock::now();
	red_player.network_evaluate(board_state);
        auto end_cpu = std::chrono::high_resolution_clock::now();
        cout << "Red Player: " <<
        std::chrono::duration<double, std::nano> (end_cpu - start_cpu).count() << "ns" << endl;
        // end timing

        // GPU Timing
        auto start_gpu = std::chrono::high_resolution_clock::now();
        auto end_gpu = std::chrono::high_resolution_clock::now();
        white_player.network_evaluate(board_state);
        cout << "White Player: " <<
        std::chrono::duration<double, std::nano> (end_gpu - start_gpu).count() << "ns" << endl;
        // end GPU timing

	//board.print_board(std::cout);


        /*
	while (1) {
		board = minimax(red_player, board, 6, 'r');

		std::cout << std::endl;
		board.print_board(std::cout);

		board = minimax(white_player, board, 6, 'w');
		std::cout << std::endl;
		board.print_board(std::cout);
	}
        */
	return 0;
}
