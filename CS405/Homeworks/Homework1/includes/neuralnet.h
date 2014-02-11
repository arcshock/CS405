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
#include<chrono>
#include<random>

template<class Iter>
class NeuralNet {
public:
	NeuralNet(int input, Iter begin, Iter end, int output);
	NeuralNet(Iter begin, Iter end, int size);
	void setWeights();
	void printNetwork();
	void loadInput(); //TODO - add input to func
	void activateNetwork(); //process input - TODO rename
	void forwardFeed();
	void mutateNetwork();
	double getEvalOutput();

private:
/*	int size_m;
	Iter begin_m;
	Iter end_m; */
	double evalOutput_m;
	double squashFunc(double input);
	std::vector< std::vector<Node> > network_m;
	//TODO: pairs for bias and weight of each node (class or struct for node?)
};

template<class Iter>
NeuralNet<Iter>::NeuralNet (Iter begin, Iter end, int numOfLayers)
{
	Iter layerSize = begin;
	network_m.reserve(numOfLayers);
	for (int i = 0; i < numOfLayers; ++i) {     //creates each layer
		network_m.push_back(std::vector<Node>(*layerSize));   //
		++layerSize;
	}
}

template<class Iter>
void NeuralNet<Iter>::setWeights()
{
    for (int i = 1; i < network_m.size(); ++i) {
		for ( int j = 0; j < network_m[i].size(); ++j) {
			network_m[i][j].randomInit();
        }
    }
}

template<class Iter>
void NeuralNet<Iter>::mutateNetwork()
{
    for (int i = 1; i < network_m.size(); ++i) {
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
/*
template<class Iter>
double NeuralNet<Iter>::getEvalOutput()
{
	return evalOutput_m;
}

template<class Iter>
void NeuralNet<Iter>::activateNetwork()
{
	std::vector< double > tempValues;
	for (int i = 1; i < network_m.size(); ++i){ //starting at the first hidden layer
		for ( int j = 0; j < network_m[i].size(); ++j ) { //chose node in hiddent layer and apply all of last layer to it
			tempValues.push_back(squashFunc(network_m[i][j]));
		}
	}

	for (int i = 0; i < tempValues.size(); ++i ){
		evalOutput_m =+ tempValues[i];
	}

	evalOutput_m = squashFunc(evalOutput_m);
}

template<class Iter>
void NeuralNet<Iter>::loadInput()
{
	for ( int j = 0; j < network_m[0].size(); ++j ) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator (seed);
		network_m[0][j] = generator();
	}
}

template<class Iter>
double NeuralNet<Iter>::squashFunc(double input)
{
	return input/( 1 + abs(input) );
}


template<class Iter>
void NeuralNet<Iter>::printNetwork()
{
	for ( int i = 0; i < network_m.size(); ++i ) {
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			std::cout << "Layer: " << i << " Element: " << j << " " << network_m[i][j] << std::endl;
		}
	}
}


template<class Iter>
void NeuralNet<Iter>::setWeights()
{
	for (int i = 1; i < network_m.size(); ++i){
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator (seed);
			network_m[i][j] = generator();
		}
	}
}

template<class Iter>
NeuralNet<Iter>::NeuralNet (Iter begin, Iter end, int size )
{
	Iter it = begin;
	network_m.reserve(size);
	for (int i = 0; i < size; ++i){
		network_m.push_back(std::vector<Node>(*it));
		++it;
	}
}
*/

#endif //NEURAL_NET_H
