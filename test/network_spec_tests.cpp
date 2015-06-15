#ifndef NETWORK_SPEC_TEST
#define NETWORK_SPEC_TEST

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "network_spec.hpp"
#include "neural_network.hpp"

const std::string standard_network_topography("32 40 10 1");
std::vector<double> eval_data(0, 32);

TEST_CASE ("Network Specification") {
	SECTION ("construction from String") {
		Network_Spec network_spec_ctor_test(standard_network_topography);

		std::istringstream buffer(standard_network_topography);
		unsigned int tmp = 0;

		for (auto it = network_spec_ctor_test.begin(); it != network_spec_ctor_test.end(); ++it) {
			if (buffer.good()) {
				buffer >> tmp;
			}
			REQUIRE( *it == tmp );
		}
	}
}

TEST_CASE ("Neural Network") {
	SECTION ("Construction from Specification") {
		Network_Spec net_spec(standard_network_topography);
		Neural_Network spec_constructed(net_spec);
	}

	SECTION ("Evaluation Function") {
		Network_Spec net_spec(standard_network_topography);
		Neural_Network spec_constructed(net_spec);
		REQUIRE ( spec_constructed.start(eval_data.begin(), eval_data.end()) != 0 );
	}
}
#endif /*NETWORK_SPEC_TEST*/
