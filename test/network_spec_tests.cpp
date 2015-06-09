#ifndef NETWORK_SPEC_TEST
#define NETWORK_SPEC_TEST

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "catch.hpp"
#include "network_spec.hpp"

const std::string standard_network_topography("32 40 10 1");

TEST_CASE ("Network Specification") {
	SECTION ("construction from string") {
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
#endif /*NETWORK_SPEC_TEST*/
