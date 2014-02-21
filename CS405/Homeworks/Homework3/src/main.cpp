/*
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: Main function for managing the neural network.
 * CS 405 Intro to A.I.
 */
#include "neuralnet.h"
#include <iostream>
#include <array>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>


std::string timingManager(NeuralNet<4> & neuralNet, int iterations);
double timingFunc(int iterations, NeuralNet<4> & neuralNet); // used for timing board evals
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples);
void messaging(std::string message);

int main()
{
	std::array<int, 4> hidden_layers = {{ 32, 40, 10, 1 }};

	NeuralNet < hidden_layers.size() > test1 (hidden_layers);
	test1.loadInput();
	test1.setWeights();
	test1.forwardFeed();

	messaging("Timing");
	std::cout << timingManager(test1, 5000) << std::endl; 

	messaging("Printing Network");
	test1.printNetworkWeights();

	messaging("Mutating Network");
	test1.mutateNetwork();
	test1.printNetworkWeights();

	return 0;
}

// Precondition:
// Message is a string value to inform the user.
// 
// Post Condition:
// Prints the messege between stings of '#' characters.
void messaging(std::string message)
{
	for (int i = 0; i < 120; ++i) {
		std::cout << "#";
		if ( i == 60 )
			std::cout << std::endl << message << std::endl;
	}
	std::cout << std::endl;
}

// Precondition:
// iterations are the number of times to call the feedforward function from class NeuralNet
// numOfBoardEval 
std::string timingManager(NeuralNet<4> & neuralNet, int iterations)
{
	std::vector<double> times;

	for (int i = 0; i < iterations; ++i) {
		times.push_back(timingFunc(iterations*20, neuralNet));
	}
	
	// Report string construction.
	std::ostringstream timingMessage;
	timingMessage << "Completed " << iterations << " iteration(s) of ";
	timingMessage << iterations << " board evaluation(s) in average time of ";
	timingMessage << timeavg(times.begin(), times.end(), iterations) << " second(s)." << std::endl;
	timingMessage << "Average time of board evaluation: " << iterations/timeavg(times.begin(), times.end(), iterations) << " per second." << std::endl;

	return timingMessage.str();
}

// Precondition:
// iterations are the number of times to call the feedforward function from class NeuralNet
// 
// Post Condition:
// Returns the total time to execute the number of iterations of the feedforward function.
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

// Precondition: 
// The begin and end iterators are for a vector that contain times for a feedforward call.
// Samples are the number of iterations for that time. <- Need to rething this.
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples)
{
	double runningTotal = 0;

	for (auto iter = begin; begin != end; ++begin)
		runningTotal += *iter;

	return runningTotal/samples;
}

