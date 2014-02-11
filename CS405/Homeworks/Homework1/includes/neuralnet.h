#ifndef NEURAL_NET_H
#define NEURAL_NET_H
/*
 * Author: Bucky Frost
 * File: neuralnet.h
 * CS 405 Intro to A.I.
 * Purpose: Header of neural network class.
 */

#include"node.h"
#include<vector>
#include<array>
#include<iterator>
#include<cstdlib>
#include<iostream>
#include<random>
//#include<chrono>
#include<random>

template<class Iter>
class NeuralNet {
public:
	NeuralNet(int input, Iter begin, Iter end, int output);
	NeuralNet(Iter begin, Iter end, int size);
	void setWeights();
	void printNetwork();
	void loadInput();
	void forwardFeed();
	void mutateNetwork();
	double getEvalOutput();

private:
	double evalOutput_m;
	double squashFunc(double input);
	std::vector< std::vector<Node> > network_m;
};

template<class Iter>
void NeuralNet<Iter>::loadInput()
{
	for ( int j = 0; j < network_m[0].size(); ++j ) {
		network_m[0][j].setOutput(network_m[0][j].randomValue());
	}
}

template<class Iter>
NeuralNet<Iter>::NeuralNet (Iter begin, Iter end, int numOfLayers)
{
	Iter layerSize = begin;
	network_m.reserve(numOfLayers);

	for (int i = 0; i < numOfLayers; ++i) {     //creates each layer
		network_m.push_back(std::vector<Node>(*layerSize));
		++layerSize;
	}
}

template<class Iter>
void NeuralNet<Iter>::setWeights()
{
	for (int i = 0; i < network_m.size(); ++i) {
		for (int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].randomInit();
		}
	}
}

template<class Iter>
void NeuralNet<Iter>::mutateNetwork()
{
	for (int i = 1; i < network_m.size(); ++i) { // staring at hidden layer
		for ( int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].mutateWeight();
		}
	}
}

template<class Iter>
void NeuralNet<Iter>::printNetwork()
{
	for (int i = 1; i < network_m.size(); ++i) {
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			std::cout << "On layer " << i << " accessing element " << j << " = ";
			std::cout << network_m[i][j].getWeight() << std::endl;
		}
	}
}

template<class Iter>
void NeuralNet<Iter>::forwardFeed()
{
	for (int i = 1; i < network_m.size(); ++i) { //starting at the first hidden layer
		for ( int j = 0; j < network_m[i].size(); ++j ) { //chose node in hiddent layer and apply all of last layer to it
			network_m[i][j].setOutput(network_m[i][j].getOutput() +
			(network_m[i-1][j].getWeight()*network_m[i-1][j].getOutput()));
		}

		for ( int j = 0; j < network_m[i].size(); ++j )
			network_m[i][j].squashOutput();
	}
}
#endif //NEURAL_NET_H
