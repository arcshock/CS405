/**
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <vector>
#include <chrono>
#include "neural_network.hpp"
#include "g_neural_network.hpp"
#include "minimax.hpp"
using std::cout;
using std::endl;

std::vector<int> standard_network = {32, 40, 10, 1};

void create_NN();
void timing();
void load_NN();

int main(int argc, char* argv[])
{
	create_NN();
	load_NN();

	return 0;
}

void load_NN()
{
	G_Neural_Network * test_case_network = new G_Neural_Network(standard_network);
	
	try {
		ifstream ifs("base_network_save.txt");
		int state = ifs.rdstate();
		cout << "FILE STATE: " << state << endl;
		boost::archive::text_iarchive ia(ifs);
		//ia >> test_case_network;
		ifs.close();
	} catch (const boost::archive::archive_exception& e) {
		cout << e.what();
	}
}

void create_NN()
{
        G_Neural_Network * base_case_network = new G_Neural_Network(standard_network);

	std::ofstream ofs("base_network_save.txt");

	boost::archive::text_oarchive oa(ofs);

	oa << base_case_network;
	ofs.close();

}

void timing()
{
        int n=32*40*8; // size of network... total number of floats
        G_Neural_Network * whitey = new G_Neural_Network(standard_network);

        // Run gpu stuff on shared space
        int nBlocks = 1;    // GPU thread blocks to run
        int blockDim = n;   // threads per block, should be 256 for best performance
	for (int ii = 0; ii < 100; ++ii) {
        	auto start_gpu = std::chrono::high_resolution_clock::now();
		evaluate<<<nBlocks, blockDim>>>(whitey);    // evaluate on gpu
		cudaDeviceSynchronize();    // wait to finish evaluation
        	auto end_gpu = std::chrono::high_resolution_clock::now();
        	cout << std::chrono::duration<double, std::nano> (end_gpu - start_gpu).count() << endl;
	}


}
