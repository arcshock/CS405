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
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <array>

template<std::size_t SIZE>
class NeuralNet {
public:

//	NeuralNet(int input, SIZE begin, SIZE end, int output);
//	NeuralNet(SIZE begin, SIZE end, int size);
	NeuralNet(std::array<int, SIZE>& arr);
	void setWeights();
	void printNetwork();
	void loadInput();
	void forwardFeed();
	void mutateNetwork();
	double getEvalOutput();

private:
	double evalOutput_m;
	double squashFunc(double input);
	double evalFunc();
	std::vector< std::vector<Node> > network_m;
};

template<std::size_t SIZE>
double NeuralNet<SIZE>::evalFunc()
{
	evalOutput_m = (1 - network_m.back().back().getOutput()); // TODO multiply the sigmoid func
	return evalOutput_m;
}

template<std::size_t SIZE>
void NeuralNet<SIZE>::loadInput()
{
	for ( int j = 0; j < network_m[0].size(); ++j ) {
		network_m[0][j].setOutput(network_m[0][j].randomValue());
	}
}

template<std::size_t SIZE>
NeuralNet<SIZE>::NeuralNet (std::array<int, SIZE>& arr)
{
	auto numberOfLayers = arr.size();
	network_m.reserve(numberOfLayers);

	for (int i = 0; i < numberOfLayers; ++i){
		network_m.push_back(std::vector<Node>(arr[i]));
	}
}

template<std::size_t SIZE>
void NeuralNet<SIZE>::setWeights()
{
	for (int i = 0; i < network_m.size(); ++i) {
		for (int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].randomInit();
		}
	}
}

template<std::size_t SIZE>
void NeuralNet<SIZE>::mutateNetwork()
{
	for (int i = 1; i < network_m.size(); ++i) { // staring at hidden layer
		for ( int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].mutateWeight();
		}
	}
}

template<std::size_t SIZE>
void NeuralNet<SIZE>::printNetwork()
{
	for (int i = 1; i < network_m.size(); ++i) {
		std::cout << "Printing layer " << i << std::endl;
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			std::cout << network_m[i][j].getWeight() << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

template<std::size_t SIZE>
void NeuralNet<SIZE>::forwardFeed()
{
	for (int i = 1; i < network_m.size(); ++i) { //starting at the first hidden layer
		for ( int j = 0; j < network_m[i].size(); ++j ) { //chose node in hiddent layer and apply all of last layer to it
			network_m[i][j].setOutput(network_m[i][j].getOutput() +
			(network_m[i-1][j].getWeight()*network_m[i-1][j].getOutput()));
		}

		for ( int j = 0; j < network_m[i].size(); ++j ) {
			network_m[i][j].squashOutput();
		}
	}


}
#endif //NEURAL_NET_H
