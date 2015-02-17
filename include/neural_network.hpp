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

	network_type network; /**< Testing of the Doxygen markup for member variables. */

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


	// Feed forward the network to evaluate the checker board.
	double network_evaluate(std::vector<double>::iterator begin_input, std::vector<double>::iterator end_input);
/*

	bool operator==(const Neural_Network & other) const
	{
		return other._network == _network;
	}


	bool operator!=(const Neural_Network & other) const
	{
		return !(*this == other);
	}
*/
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
#endif /*NEURAL_NETWORK_HPP*/
