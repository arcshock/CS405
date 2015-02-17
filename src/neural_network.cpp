/**
 * File: neural_network.cpp
 * Purpose: implementation file of neural network.
 */

#include <sstream>
#include <iostream>
#include "neural_network.hpp"


Neural_Network::Neural_Network(std::string network_specification)
{
	std::istringstream buffer(network_specification);

	int tmp = 0;

	while (buffer.good())  {
		buffer >> tmp;
		network.emplace_back(std::vector<Network_Node>(tmp));
	}
}


Neural_Network::Neural_Network(Network_Spec network_specifications)
{
	for (auto iter = network_specifications.begin(); iter != network_specifications.end(); ++iter) {
		network.emplace_back(std::vector<Network_Node>(*iter));
	}
}

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
