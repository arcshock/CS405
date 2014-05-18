#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/*
 * Author: Bucky Frost
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
#include <random>

static std::random_device randomDevice;
static std::mt19937 random_value(randomDevice());
static std::uniform_real_distribution<> uniform_distribution(-1, 1);


class Neural_Network
{
public:
	Neural_Network() = default;


	Neural_Network(std::vector<int> network_specifications)
	{
		int network_layers = network_specifications.size();

		for (int ii = 0; ii < network_layers; ++ii) {
			network_.emplace_back(std::vector<double>(network_specifications[ii], uniform_distribution(random_value)));
		}
	}


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


	std::vector<std::vector<double>> network_;
};
#endif /*NEURAL_NETWORK_HPP*/
