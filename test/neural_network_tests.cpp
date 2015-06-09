#ifndef NEURAL_NETWORK_TEST
#define NEURAL_NETWORK_TEST

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "catch.hpp"
#include "neural_network.hpp"
#include "network_spec.hpp"

const std::string standard_network_topography("32 40 10 1");
std::vector<double> zeroed_input(32, 0.0);

TEST_CASE ("Neural Network Construction") {

	SECTION ("From Network Spec") {
		Network_Spec network_topo(standard_network_topography);
	}
}


TEST_CASE( "Neural Network Serialization" ) {

	const std::string serialization_file("test_network.txt");

	Neural_Network saved_network(standard_network_topography);

	// Serialization
	std::ofstream ofs(serialization_file);
	boost::archive::text_oarchive oa(ofs);
	oa << saved_network;

	ofs.close();

	saved_network.network_evaluate(zeroed_input.begin(), zeroed_input.end());

	Neural_Network restored_network(standard_network_topography);

	std::ifstream ifs(serialization_file);
	boost::archive::text_iarchive ia(ifs);
	ia >> restored_network;

	if (remove(serialization_file.c_str()) != 0) {
		std::cout << "Error on deleting " << serialization_file << std::endl;
	}
}


TEST_CASE( "Network Data" ) {
	Neural_Network default_network(standard_network_topography);
}
#endif /*NEURAL_NETWORK_TEST*/
