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

double timingFunc(int iterations, NeuralNet<std::array<int, 4>::iterator> & neuralNet);


int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < std::array<int, 4>::iterator > test1 ( hidden_layers.begin(), hidden_layers.end(), hidden_layers.size() );

	test1.setWeights();

	std::vector<double> times;
	double totalTime = 0;

	for (int i = 0; i < 20; ++i) {
		times.push_back( timingFunc ( 11500, test1 ) );
		std::cout << "Evaluating new board " << i << std::endl; // debug
	}

	for ( auto i : times ) {
//		std::cout << i << std::endl; // debug
		totalTime += i;	
	}
//	std::cout << "totalTime:" << totalTime << std::endl; // debug

	std::cout << "Finished 11500 evalualuations for 20 boards in an average time of " << totalTime/20 << " seconds." << std::endl;
	std::cout << "There are  " << 11500/(totalTime/20) << " evauations per second." << std::endl;
//	timingFunc( 11500, test1 );
	return 0;
}

double timingFunc(int iterations, NeuralNet<std::array<int, 4>::iterator> & neuralNet)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	for ( int i = 0; i < iterations; ++i) {
		neuralNet.loadInput();
		neuralNet.activateNetwork();
	}
	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

//	std::cout << "Finished " << iterations << " evaluations in " << elapsed_seconds.count() << " seconds." << std::endl;
	return elapsed_seconds.count();
}
