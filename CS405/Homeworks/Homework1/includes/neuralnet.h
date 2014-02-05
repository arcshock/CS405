#ifndef NEURAL_NET_H
#define NEURAL_NET_H
/*
 * Author: Bucky Frost
 * File: neuralnet.h
 * CS 405 Intro to A.I.
 * Purpose: Header of neural network class.
 */

#include<array>
#include<ostream>
#include<iterator>
#include<cstdlib>

//template<typename T>
template<class Iter>
class NeuralNet {
public:
	NeuralNet();
	NeuralNet(int input, Iter begin, Iter end, int output);
	NeuralNet(Iter begin, Iter end);
//	NeuralNet(int input, int* begin, int* end, int output);

private:
	
	
};

template<class Iter>
NeuralNet<Iter>::NeuralNet (Iter begin, Iter output)
{
	//TODO
}
template<class Iter>
NeuralNet<Iter>::NeuralNet(int input, Iter begin, Iter end, int output)
{
	//TODO
}
#endif //NEURAL_NET_H
