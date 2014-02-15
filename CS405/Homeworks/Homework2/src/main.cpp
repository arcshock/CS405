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

std::string timingManager(int iterations, int numOfBoardEval, NeuralNet<std::array<int, 4>::iterator> & neuralNet);
double timingFunc(int iterations, NeuralNet<std::array<int, 4>::iterator> & neuralNet); // used for timing board evals
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples);


int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < std::array<int, 4>::iterator > test1 ( hidden_layers.begin(), hidden_layers.end(), hidden_layers.size());
	test1.loadInput();
	test1.setWeights();
	test1.forwardFeed();

	std::cout << timingManager(5, 2000, test1) << std::endl;
	return 0;
}


double timingFunc(int iterations, NeuralNet<std::array<int, 4>::iterator> & neuralNet)
{
	// setup timing
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	for (int i = 0; i < iterations; ++i)
		neuralNet.forwardFeed();

	// end timer and find duration
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	return elapsed_seconds.count();
}


std::string timingManager(int iterations, int numOfBoardEval, NeuralNet<std::array<int, 4>::iterator> & neuralNet)
{
	std::vector<double> times;

	for (int i = 0; i < iterations; ++i) {
		times.push_back(timingFunc(numOfBoardEval, neuralNet));
		std::cout << "Evaluating new board " << i << std::endl;
	}

	std::ostringstream timingMessage;
	timingMessage << "Completed " << iterations << " iterations of ";
	timingMessage << numOfBoardEval << " board evaluations in average time of ";
	timingMessage << timeavg(times.begin(), times.end(), iterations) << " seconds." << std::endl;
	timingMessage << "Boards generated on average is " << numOfBoardEval/timeavg(times.begin(), times.end(), iterations) << std::endl;

	return timingMessage.str();
}

double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples)
{
	double runningTotal = 0;

	for (auto iter = begin; begin != end; ++begin)
		runningTotal += *iter;

	return runningTotal/samples;
}
