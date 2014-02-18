/*
 * Author: Bucky Frost
 * File: feedforward.cpp
 * Purpose: Just calling init on the network and feedforward function
 * 	for profiling purposes.
 * CS 405 Intro to A.I.
 */
#include "neuralnet.h"
#include "node.h"
#include <array>

int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < std::array<int, 4>::iterator > test1 ( hidden_layers.begin(), hidden_layers.end(), hidden_layers.size());
	test1.loadInput();
	test1.setWeights();
	test1.forwardFeed();

	return 0;
}
