/*
 * Author: Bucky Frost
 * File: neuralnet.h
 * CS 405 Intro to A.I.
 * Purpose: Header of neural network class.
 */

#ifndef NEURAL_NET_H
#define NEURAL_NET_H 

#include "node.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <array>

template<std::size_t SIZE>
class NeuralNet {
public:
	NeuralNet(std::array<int, SIZE>& arr);
	void setWeights();
	void printNetworkWeights();
	void loadInput();
	void forwardFeed();
	void mutateNetwork();
	double getEvalOutput();

private:
	double evalOutput_m;
	double squashFunc(double input);
	double evalFunc();
	std::vector< std::vector<Node> > network_m;
	std::array< std::array<int, SIZE>, SIZE > exp_network_m;
};

/*******************************
 * Function evalFunc
 *
 * Precondition: The output node of the neural network must must contain
 * 	the value that must be evaluated of the neural network.
 *
 * Post Condition: Sets the evalOutput_m member variable to the output 
 * 	of the neural net and returns that value.
 *
 *****************************/
template<std::size_t SIZE>
double NeuralNet<SIZE>::evalFunc()
{
	evalOutput_m = (1 - network_m.back().back().getOutput()); // TODO multiply the sigmoid func
	return evalOutput_m;
}

/******************************
 * Function loadInput
 * 
 * Precondition: The network_m member variable must be initialized to be a vector of a vector of nodes
 *
 * Post Condition: Leaves the input layer of the network with random values for their inputs.
 *
 *******************************/
template<std::size_t SIZE>
void NeuralNet<SIZE>::loadInput()
{
	for ( int j = 0; j < network_m[0].size(); ++j ) {
		network_m[0][j].setOutput(network_m[0][j].randomValue());
	}
}

/***************************
 * Class Constructor
 *
 * Precondition: Must be passed an std::array who elements are the length of the layer of the network.
 *
 * Post Condition: Initializes the network_m member variable to be a vector of vector of nodes.
 *
 ***************************/
template<std::size_t SIZE>
NeuralNet<SIZE>::NeuralNet (std::array<int, SIZE>& arr)
{
	auto i = 0;
	auto numberOfLayers = arr.size();
	network_m.reserve(numberOfLayers);

	for ( i = 0; i < numberOfLayers; ++i) {
		network_m[i].reserve(arr[i]);
	}

	for ( i = 0; i < numberOfLayers; ++i) {
		network_m.push_back(std::vector<Node>(arr[i]));
	}
}

/**************************
 * Function setWeights
 *
 * Precondition: None
 *
 * Post Condition: Calls randomInit on each node in the network.
 *
 **************************/
template<std::size_t SIZE>
void NeuralNet<SIZE>::setWeights()
{
	for (int i = 0; i < network_m.size(); ++i) {
		for (int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].randomInit();
		}
	}
}

/*************************
 * Function mutateNetwork
 *
 * Precondition: None.
 *
 * Post Condition: Calls the mutate function on all the nodes from the hidden layers on.
 *
 *************************/
template<std::size_t SIZE>
void NeuralNet<SIZE>::mutateNetwork()
{
	auto startOfHiddenLayers = 1; // should all the network be mutated?

	for (int i = startOfHiddenLayers; i < network_m.size(); ++i) { 
		for ( int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].mutateWeight();
		}
	}
}

/************************
 * Function printNetworkWeights
 *
 * Precondition: None.
 *
 * Post Condition: prints out the weights from the network to cout buffer.
 ************************/
template<std::size_t SIZE>
void NeuralNet<SIZE>::printNetworkWeights()
{
	auto startOfHiddenLayers = 1;

	for (int i = startOfHiddenLayers; i < network_m.size(); ++i) {
		std::cout << "Printing layer " << i << std::endl;
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			std::cout << network_m[i][j].getWeight() << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

/***********************
 * Function forwardFeed
 *
 * Precondition: None
 *
 * Post Condition: Takes all the nodes from the previous layer and multiplies 
 * 	their weights against their input, sums all of those values,
 * 	and sets that value to the input of the node.
 ***********************/
template<std::size_t SIZE>
void NeuralNet<SIZE>::forwardFeed()
{
	auto startOfHiddenLayers = 1;

	for (int i = startOfHiddenLayers; i < network_m.size(); ++i) { 
		for ( int j = 0; j < network_m[i].size(); ++j ) { // chose node in hiddent layer and apply all of last layer to it
			network_m[i][j].setOutput(network_m[i][j].getOutput() +
			(network_m[i-1][j].getWeight()*network_m[i-1][j].getOutput()));
		}

		for ( int j = 0; j < network_m[i].size(); ++j ) {
			network_m[i][j].squashOutput();
		}
	}


}
#endif //NEURAL_NET_H
