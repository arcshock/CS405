/*
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: Main function for managing the neural network.
 * CS 405 Intro to A.I.
 */
#include"neuralnet.h"
#include<iostream>
#include<array>
#include<chrono>
#include<ctime>
#include<string>
#include <sstream>


int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < hidden_layers.size() > test1 (hidden_layers);
	test1.loadInput();
	test1.setWeights();
	test1.forwardFeed();

	return 0;
}
