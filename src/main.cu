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

// Precondition - It doesn't make sense to have less than 32 as first layer
// for checkers evaluations. It doesn't make sense to have more than 1 as
// final layer. Thus, those will automatically be set for any non-default
// arg parameters passed into main.
std::vector<int> argparse(int argc, char* argv[])
{
    std::vector<int> layer_sizes{32, 40, 10, 1};
    if (argc > 1)
    {
        layer_sizes.resize(argc + 1);
        layer_sizes.push_back(32);
        for (unsigned int count = 1; count < argc; ++count)
        {
            layer_sizes[count] = std::stoi(argv[count]);
        }
        layer_sizes.push_back(1);

    }
    return layer_sizes;
}


void create_NN(std::vector<int>);
void timing(std::vector<int>);

int main(int argc, char* argv[])
{
        std::vector<int> neural_network_layers = argparse(argc, argv);
        timing(neural_network_layers);
	return 0;
}

void create_NN(std::vector<int> layers)
{
        G_Neural_Network * base_case_network = new G_Neural_Network(layers);

	std::ofstream ofs("test_network_save.txt");

	boost::archive::text_oarchive oa(ofs);

	oa << base_case_network;
	ofs.close();

}

void timing(std::vector<int> layers)
{
        G_Neural_Network * player = new G_Neural_Network(layers);
        int n = 0;
        for (auto i : layers) { n += i; } // sum of NN nodes.

        // Run gpu stuff on shared space
        int nBlocks = 1;    // GPU thread blocks to run
        int blockDim = n;   // threads per block, should be 256 for best performance
	for (int ii = 0; ii < 100; ++ii) {
        	auto start_gpu = std::chrono::high_resolution_clock::now();
		evaluate<<<nBlocks, blockDim>>>(player);    // evaluate on gpu
		cudaDeviceSynchronize();    // wait to finish evaluation
        	auto end_gpu = std::chrono::high_resolution_clock::now();
        	cout << std::chrono::duration<double, std::nano> (end_gpu - start_gpu).count() << endl;
	}


}
