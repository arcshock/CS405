#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/*
 * Author: Bucky Frost
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>

class Neural_Network
{
public:
	/*Using compiler generated silent 4*/

	// Feed forward the network to evaluate the checker board.
	double network_evaluate(std::vector<double> & board_input)
	{
		double evaluation_value = 0.0;

		for ( auto iter : board_input ) {
			evaluation_value += iter;
		}

		return sigmoid(evaluation_value);
	}
private:
	double sigmoid(double input)
	{
		return input/(1.0 + abs(input));
	}
};
#endif /*NEURAL_NETWORK_HPP*/
