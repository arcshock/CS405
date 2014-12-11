/**
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */


#include <iostream>
#include <vector>
#include <chrono>
#include "neural_network.hpp"
#include "g_neural_network.cu"
#include "minimax.hpp"
using std::cout;
using std::endl;
extern evaluate;

std::vector<int> argparse(int argc, char* argv[])
{
    std::vector<int> node_size{32, 40, 10, 1};
    if (argc > 1)
    {
        node_size.resize(argc + 1);
        node_size.push_back(32);
        for (unsigned int count = 1; count < argc; ++count)
        {
            node_size[count] = std::stoi(argv[count]);
        }
        node_size.push_back(1);

    }
    return node_size;
}



int main(int argc, char* argv[])
{

    argparse(argc, argv);

	std::vector<int> standard_network = {32, 40, 10, 1};
	std::vector<float> board_state;

	Neural_Network red_player(standard_network);
	Neural_Network white_player(standard_network);

	Checker_Board board;

	board_state = board.get_state();

        // Timing
        auto start_cpu = std::chrono::high_resolution_clock::now();
	red_player.network_evaluate(board_state);
        auto end_cpu = std::chrono::high_resolution_clock::now();
        cout << "Red Player: " <<
        std::chrono::duration<double, std::nano> (end_cpu - start_cpu).count() << "ns" << endl;
        // end timing

        // GPU Timing
        auto start_gpu = std::chrono::high_resolution_clock::now();

        // Allocate Space shared between cpu and gpu
        int n=32*40*8; // size of network... total number of floats
        G_Neural_Network * whitey = new G_Neural_Network[n];

        // Run gpu stuff on shared space
        int nBlocks = 1;    // GPU thread blocks to run
        int blockDim = n;   // threads per block, should be 256 for best performance
        evaluate<<<nBlocks, blockDim>>>(whitey);    // evaluate on gpu

        cudaDeviceSynchronize();    // wait to finish evaluation
        //white_player.network_evaluate(board_state);

        auto end_gpu = std::chrono::high_resolution_clock::now();
        cout << "White Player: " <<
        std::chrono::duration<double, std::nano> (end_gpu - start_gpu).count() << "ns" << endl;
        // end GPU timing

        /*
	board.print_board(std::cout);

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
