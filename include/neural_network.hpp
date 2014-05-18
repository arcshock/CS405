#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/*
 * Author: Bucky Frost
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
#include "network_node.hpp"

class Neural_Network
{
public:
	Neural_Network() = default;


	Neural_Network(std::vector<int> network_specifications)
	{
		int network_layers = network_specifications.size();

		for (int ii = 0; ii < network_layers; ++ii) {
			_network.emplace_back(std::vector<network_node>(network_specifications[ii]));
		}
	}


	// Feed forward the network to evaluate the checker board.
	double network_evaluate(std::vector<double> & board_input)
	{
		double evaluation_value = 0.0;

		int network_input_size = _network[0].size();
		int input_layer = 0;

		try {
			for (int ii = 0; ii < network_input_size; ++ii) {
					_network[input_layer][ii]._input = board_input[ii];
			}
		} catch (const std::out_of_range & range_error) {
			std::cerr << "Out of Range error loading input to network: " << range_error.what() << '\n';
		}

		try { 
			for (int network_layer = input_layer + 1; network_layer < _network.size(); ++network_layer) {
				for (int layer_column = 0; layer_column < _network[network_layer].size(); ++layer_column) {
					for (int ii = 0; ii < _network[network_layer - 1].size(); ++ii)
						_network[network_layer][layer_column]._input += sigmoid(_network[network_layer - 1][ii].node_value());
				}
			}
		} catch (const std::out_of_range & range_error) {
			std::cerr << "Out of Range error in feed forward of network: " << range_error.what() << '\n';
		}

		auto network_output = _network.back();
		evaluation_value = _network.back().back().node_value();
		return sigmoid(evaluation_value);
	}


private:
	double sigmoid(double input)
	{
		return input/(1.0 + abs(input));
	}
	

	std::vector<std::vector<network_node>> _network;
};
#endif /*NEURAL_NETWORK_HPP*/
