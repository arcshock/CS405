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


std::string timingManager(NeuralNet<4> & neuralNet, int iterations, int numOfBoardEval = 1);
double timingFunc(int iterations, NeuralNet<4> & neuralNet); // used for timing board evals
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples);


int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < hidden_layers.size() > test1 (hidden_layers);
	test1.loadInput();
	test1.setWeights();
	test1.forwardFeed();

	std::cout << timingManager(test1, 100, 60) << std::endl;

	for (int i = 0; i < 160; ++i) {
		std::cout << "#";
		if (i == 80)
			std::cout << std::endl << "Prining network" << std::endl;
	}
	std::cout << std::endl;

	test1.printNetwork();

	for (int i = 0; i < 160; ++i) {
		std::cout << "#";
		if (i == 80)
			std::cout << std::endl << "Mutating network" << std::endl;
	}
	std::cout << std::endl;
	
	test1.mutateNetwork();
	test1.printNetwork();

	return 0;
}


std::string timingManager(NeuralNet<4> & neuralNet, int iterations, int numOfBoardEval)
{

	for (int i = 0; i < 160; ++i){
		
		std::cout << "#";
		if (i == 80) {
			std::cout << std::endl << "TIMING" << std::endl;
		}
	}
	std::cout << std::endl;

	std::vector<double> times;

	for (int i = 0; i < iterations; ++i) {
		times.push_back(timingFunc(numOfBoardEval, neuralNet));
	}

	std::ostringstream timingMessage;
	timingMessage << "Completed " << iterations << " iteration(s) of ";
	timingMessage << numOfBoardEval << " board evaluation(s) in average time of ";
	timingMessage << timeavg(times.begin(), times.end(), iterations) << " second(s)." << std::endl;
	timingMessage << "Average time of board evaluation: " << numOfBoardEval/timeavg(times.begin(), times.end(), iterations) << " per second." << std::endl;

	return timingMessage.str();
}

double timingFunc(int iterations, NeuralNet<4> & neuralNet)
{
	// setup timing
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	for (int i = 0; i < iterations; ++i)
		neuralNet.forwardFeed();

	// end timer and find duration
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	return elapsed_seconds.count();
}

double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples)
{
	double runningTotal = 0;

	for (auto iter = begin; begin != end; ++begin)
		runningTotal += *iter;

	return runningTotal/samples;
}

