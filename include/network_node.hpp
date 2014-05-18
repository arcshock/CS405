#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

/*
 * Author: Bucky Frost
 * File: network_node.hpp
 * Purpose: Define the struct that is used in interal of the neural network.
 */

#include <random>

static std::random_device randomDevice;
static std::mt19937 random_value(randomDevice());
static std::uniform_real_distribution<> uniform_distribution(-1, 1);


struct network_node
{
	double _input;
	double _weight;

	network_node()
	{
		_input = 1.0;
		_weight = uniform_distribution(random_value);
	}

	double node_value()
	{
		return _input*_weight;
	}
};
#endif /*NETWORK_NODE_HPP*/
