#ifndef NETWORK_SPEC_HPP
#define NETWORK_SPEC_HPP
/**
 * File: network_spec.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
#include <fstream>
#include <iterator>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "network_node.hpp"

class Network_Spec
{
private:
	Network_Spec() = default;


	std::vector<unsigned int> network_topography;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & network_topography;
	}

public:
	Network_Spec(std::string network_description)
	{
		std::istringstream buffer(network_description);

		unsigned int tmp = 0;

		while (buffer.good())  {
			buffer >> tmp;
			network_topography.emplace_back(tmp);
		}
	}


	std::vector<unsigned int>::iterator begin()
	{
		return network_topography.begin();
	}
	

	std::vector<unsigned int>::iterator end()
	{
		return network_topography.end();
	}
};
#endif /*NETWORK_SPEC_HPP*/
