#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

/**
 * File: network_node.hpp
 * Purpose: Define the struct that is used in interal of the neural network.
 */

#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


static std::random_device random_dev;
static std::mt19937 random_value(random_dev());
static std::uniform_real_distribution<> uniform_distribution(-1, 1);


class Network_Node
{
private:
	double value;
	double weight;

	double sigmoid(double input)
	{
		return input/(1.0 + abs(input));
	}
public:
	Network_Node(): value(1.0), weight(uniform_distribution(random_value)) {}


	void input(double input)
	{
		value =+ input*weight;
	}


	double node_value()
	{
		return sigmoid(value);
	}


	bool operator==(const Network_Node & other) const
	{
		return (other.value == value && other.weight == weight);
	}


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & weight;
	}
};
#endif /*NETWORK_NODE_HPP*/
