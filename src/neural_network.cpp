/**
 * File: neural_network.cpp
 * Purpose: implementation file of neural network.
 */

#include "neural_network.hpp"
#include <sstream>
#include <iostream>

Neural_Network::Neural_Network(std::string network_specification)
{
	std::istringstream buffer(network_specification);

	int tmp = 0;

	while (buffer.good())  {
		std::cout << " GOOD VAL " << std::endl;
		buffer >> tmp;
		network.emplace_back(std::vector<Network_Node>(tmp));
	}
}


//void Neural_Network::stats()
//{
//	for (auto network_layer = 0; network_layer < network.size(); ++network_layer) {
//		std::cout << network[network_layer].size() << std::endl;
//	}
//}


// Feed forward the network to evaluate the checker board.
//old header: double Neural_Network::network_evaluate(std::vector<double> & board_input)
double Neural_Network::network_evaluate(std::vector<double>::iterator begin_input, std::vector<double>::iterator end_input)
{
	auto network_input_element = network.begin()->begin();

	for (begin_input; begin_input != end_input; ++begin_input) {
		network_input_element->set_input(*begin_input);
		++network_input_element;
	}
}
/*
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
*/
