#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP
/**
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
#include <fstream>
#include <iterator>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "network_node.hpp"
#include "network_spec.hpp"

typedef std::vector<std::vector<Network_Node>> network_type;
class Neural_Network 
{
private:
	Neural_Network() = default;

	network_type network;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) { ar & network; }
public:
	/**
	 *	Constructor for the neural network class that takes in a constant string with space delimited
	 *	integers that specify the size of each layer in the network.
	 *
	 *	Pre-Condition: The string argument must contain only integer values that are delimited by spaces.
	 *
	 *	Post Condition: A neural network object that have a simple feedforward network of a topography specified
	 *	by the passed in string.
	 *
	 *	Throw Guarantee: None
	 */
	Neural_Network(const std::string network_specification);


	Neural_Network(Network_Spec network_specifications);


	double start(std::vector<double>::iterator begin_input, std::vector<double>::iterator end_input);
};

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


double Neural_Network::start(std::vector<double>::iterator begin_input, std::vector<double>::iterator end_input)
{
	//Load up the inputs into the network
	auto input_layer = network.begin();
	for (auto input_node = input_layer->begin(); input_node != input_layer->end(); ++input_node) {
		input_node->input(*begin_input);
		++begin_input;
	}

	//Input layer value
	double layer_summation = 0.0;
	input_layer = network.begin();

	for (auto node = input_layer->begin(); node != input_layer->end(); ++node) {
		layer_summation =+ node->node_value(); //current summation of the input layer on 1st iteration 
	}

	//Propergate the values through the network
	double network_value = 0.0;
	for (auto layer = network.begin() + 1; layer != network.end(); ++layer) { //start on 2nd lay
		//Load the values from the previous layer.
		for (auto node = layer->begin(); node != layer->end(); ++node) {
			node->input(layer_summation);
		}
		//Update the layer summation value
		for (auto node = layer->begin(); node != layer->end(); ++node) {
			layer_summation =+ node->node_value();
			network_value = node->node_value();	
		}
	}

	return network_value;
}
#endif /*NEURAL_NETWORK_HPP*/
