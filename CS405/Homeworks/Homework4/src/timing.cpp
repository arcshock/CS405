/*
 * Author: Bucky Frost
 * File: timing.cpp
 * Purpose: Implementation file for the timing functionalilty
 * CS 405 Intro to A.I.
 */
#include "neuralnet.h"
#include "timing.h"
#include <iostream>
#include <chrono>
#include <string>
#include <future>
#include <functional> 

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
//
// Post Conditions:
// Returns a string with relevent timing of the feedForward function.
std::string timingManager(NeuralNet<4> & neuralNet, int iterations)
{
	std::vector<double> times;

	for (int i = 0; i < iterations; ++i) {
		auto timingIteration1 = std::async(std::launch::async, timingFunc, iterations, std::ref(neuralNet));
		auto timingIteration2 = std::async(std::launch::async, timingFunc, iterations, std::ref(neuralNet));
		times.push_back(timingIteration1.get());
		times.push_back(timingIteration2.get());
	}

	// Report string construction.
	auto timeMessage = "Completed " + std::to_string(iterations) + " iterations of feed forward function in average time of " + 
	std::to_string(timeavg(times.begin(), times.end(), times.size())) + " ms.";
	return timeMessage;
}

// Precondition:
// iterations are the number of times to call the feedforward function from class NeuralNet
// 
// Post Condition:
// Returns the total time to execute the number of iterations of the feedforward function in ms.
double timingFunc(int iterations, NeuralNet<4> & neuralNet)
{
	auto startTime = std::chrono::steady_clock::now();

	for (auto i = 0; i < iterations; ++i)
		neuralNet.forwardFeed();

	auto endTime = std::chrono::steady_clock::now();
	auto elapsedTime = endTime - startTime;

	return std::chrono::duration <double, std::milli> (elapsedTime).count();
}

// Precondition: 
// The begin and end iterators are for a vector that contain times for a feedforward call.
// Samples are the number of iterations for that time. <- Need to rething this.
//
// Post Condition:
// Return the average to the times.
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples)
{
	auto runningTotal = 0.0;

	for (auto iter = begin; begin != end; ++begin) {
		runningTotal += *iter;
	}

	auto average = runningTotal/samples;
	
	return average;
}

// Precondition:
// Takes a function pointer.
//
// Post Condition:
// Executes the function 5 times.
void testFunction(std::function<void()> functionReference)
{
	for (auto ii = 0; ii < 5; ++ii) {
		functionReference();
	}
}
