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
#include<cstdlib>

template<typename BidirectionalIterator>

class NeuralNet {
public:
//	NeuralNet(int input, std::array<int, SIZE>& layers, int output);
	NeuralNet(int input, BidirectionalIterator begin, BidirectionalIterator end, int output);

private:
//	friend std::ostream& operator<< <SIZE>(std::ostream&, const NeuralNet<SIZE> &);
	int j = 6;
	
};

/*
template<std::size_t SIZE>
std::ostream& operator<<(std::ostream &stream, const NeuralNet<SIZE> & net) {
	return stream << "Test(" << net.j << ")";
}*/
#endif //NEURAL_NET_H
