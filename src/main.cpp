/**
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <chrono>
#include "neural_network.hpp"
#include "minimax.hpp"

// Precondition - It doesn't make sense to have less than 32 as first layer
// for checkers evaluations. It doesn't make sense to have more than 1 as
// final layer. Thus, those will automatically be set for any non-default
// arg parameters passed into main.
vector<int> argparse(int argc, char* argv[])
{
	vector<int> layer_sizes{32, 40, 10, 1};
	if (argc > 1) {
		layer_sizes.resize(argc + 1);
		layer_sizes.push_back(32);
		for (unsigned int count = 1; count < argc; ++count) {
			layer_sizes[count] = std::stoi(argv[count]);
		}
		layer_sizes.push_back(1);
	}
	return layer_sizes;
}

int main(int argc, char* argv[])
{
        vector<int> neural_network_layers = argparse(argc, argv);
	vector<double> board_state;

	Neural_Network red_player(neural_network_layers);
	Checker_Board board;
	board_state = board.get_state();

	return 0;
}

void timing()
{
        // Timing
        auto start_cpu = std::chrono::high_resolution_clock::now();
	//red_player.network_evaluate(board_state);
        auto end_cpu = std::chrono::high_resolution_clock::now();
        cout << "Red Player: " <<
        std::chrono::duration<double, std::nano> (end_cpu - start_cpu).count() << "ns" << endl;
 
}
