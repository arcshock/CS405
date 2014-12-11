#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

/*
 * Author: Bucky Frost
 * File: network_node.hpp
 * Purpose: Define the struct that is used in interal of the neural network.
 */

#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

static std::random_device randomDevice;
static std::mt19937 random_value(randomDevice());
static std::uniform_real_distribution<> uniform_distribution(-1, 1);

struct network_node
{
	float _input;
	float _weight;

	network_node() : _input(1.0)
	{
		_weight = uniform_distribution(random_value);
	}

        void set_input(float val) { _input = val; }
	float node_value() { return _input*_weight; }

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _input;
		ar & _weight;
	}

	bool operator==(const network_node & other) const
	{
		return (other._input == _input && other._weight == _weight);
	}
};
#endif /*NETWORK_NODE_HPP*/
