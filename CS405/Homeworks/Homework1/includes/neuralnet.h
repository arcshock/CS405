#ifndef NEURAL_NET_H
#define NEURAL_NET_H
/*
 * Author: Bucky Frost
 * File: neuralnet.h
 * CS 405 Intro to A.I.
 * Purpose: Header of neural network class.
 */

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
	NeuralNet();
	NeuralNet(int input, Iter begin, Iter end, int output);
	NeuralNet(Iter begin, Iter end, int size);
	void setWeights();
	void printNetwork();

private:
	std::vector< std::vector< double > > network_m;
	//TODO: pairs for bias and weight of each node
};

template<class Iter>
void NeuralNet<Iter>::printNetwork()
{
	for ( auto iter = network_m.begin(); iter != network_m.end(); ++iter ) {
		for ( auto iterr = iter->begin(); iterr != iter->end(); ++iterr ) {
			std::cout << &iterr << std::endl;
		}
	}

	for ( int i = 0; i < network_m.size(); ++i ) {
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			std::cout << network_m[i][j] << std::endl;
		}
	}
}

template<class Iter>
void NeuralNet<Iter>::setWeights()
{
	for ( auto iter = network_m.begin(); iter != network_m.end(); ++iter ) {
	
		for ( auto iterr = iter->begin(); iterr != iter->end(); ++iterr ) { 
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator (seed);
			*iterr = generator();
		}
	}

	for (int i = 0; i < network_m.size(); ++i)
	{
		for ( int j = 0; j < network_m[i].size(); ++j ) {
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator (seed);
			network_m[i][j] = generator();
			std::cout << generator() << std::endl; //debug
		}
	}
}	

template<class Iter>
NeuralNet<Iter>::NeuralNet (Iter begin, Iter end, int size )
{
	Iter it = begin;
	network_m.reserve( size );
	for (int i = 0; i < size; ++i )
	{
		network_m.push_back(std::vector<double>());
	}
	
	/*for (int i = 0; i < size; ++i) {
		network_m[i] = new std::vector<double>;
		++it;
	}*/
}

template<class Iter>
NeuralNet<Iter>::NeuralNet (int input, Iter begin, Iter end, int output)
{
	//TODO
}
#endif //NEURAL_NET_H
