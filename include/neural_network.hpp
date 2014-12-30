#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/**
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
using std::vector;
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
#include "network_node.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

typedef vector<vector<network_node>> network;
class Neural_Network 
{
private:
	Neural_Network() = default;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _network;
	}

	network _network;
public:
	Neural_Network(std::vector<int> network_specifications)
	{
		int network_layers = network_specifications.size();

		for (int layer_info = 0; layer_info < network_layers; ++layer_info) {
			_network.emplace_back(std::vector<network_node>(network_specifications[layer_info]));
		}
	}


	// Feed forward the network to evaluate the checker board.
	double network_evaluate(std::vector<double> & board_input)
	{
		double evaluation_value = 0.0;

		int network_input_size = _network[0].size();
		unsigned int input_layer = 0; // Remove this value and integrate the for loops for simplification

		try {
			for (int inputIdx = 0; inputIdx < network_input_size; ++inputIdx) {
				_network[input_layer][inputIdx]._input = board_input[inputIdx];
			}
		} catch (const std::out_of_range & range_error) {
			std::cerr << "Out of Range error loading input to network: " << range_error.what() << '\n';
		}

		try { 
			for (unsigned int network_layer = input_layer + 1; network_layer < _network.size(); ++network_layer) {
				for (unsigned int layer_column = 0; layer_column < _network[network_layer].size(); ++layer_column) {
					for (unsigned int ii = 0; ii < _network[network_layer - 1].size(); ++ii) {
						_network[network_layer][layer_column]._input += (_network[network_layer - 1][ii].node_value());
                                        }

				}
			}
		} catch (const std::out_of_range & range_error) {
			std::cerr << "Out of Range error in feed forward of network: " << range_error.what() << '\n';
		}

		auto network_output = _network.back();
		evaluation_value = _network.back().back().node_value();
		return evaluation_value;
	}


	bool operator==(const Neural_Network & other) const
	{
		return other._network == _network;
	}


	bool operator!=(const Neural_Network & other) const
	{
		return !(*this == other);
	}
};
#endif /*NEURAL_NETWORK_HPP*/
