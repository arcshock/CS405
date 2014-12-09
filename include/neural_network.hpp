#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/*
 * Author: Bucky Frost
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
#include <fstream>
#include "network_node.hpp"
#include "player.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class Neural_Network : public Player
{
public:


	Neural_Network(std::vector<int> network_specifications): Player(' ', "unknown")
	{
		int network_layers = network_specifications.size();

		for (int ii = 0; ii < network_layers; ++ii) {
			_network.emplace_back(std::vector<network_node>(network_specifications[ii]));
		}
	}


	// Feed forward the network to evaluate the checker board.
	float network_evaluate(std::vector<float> & board_input)
	{
		float evaluation_value = 0.0;

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
						_network[network_layer][layer_column]._input *= sigmoid(_network[network_layer - 1][ii].node_value());
				}
			}
		} catch (const std::out_of_range & range_error) {
			std::cerr << "Out of Range error in feed forward of network: " << range_error.what() << '\n';
		}

		auto network_output = _network.back();
		evaluation_value = _network.back().back().node_value();
		return sigmoid(evaluation_value);
	}

	bool operator==(const Neural_Network & other) const
	{
		return other._network == _network;
	}


	bool operator!=(const Neural_Network & other) const
	{
		return !(*this == other);
	}
private:
	Neural_Network() = default;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _network;
	}


	float sigmoid(float input)
	{
		return input/(1.0 + abs(input));
	}
	

	std::vector<std::vector<network_node>> _network;
};
#endif /*NEURAL_NETWORK_HPP*/
