/*
 * Author: Bucky Frost
 * File: tests.cpp
 * Purpose: Testing surite for checkers AI.
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include "neural_network.hpp"

TEST_CASE( "Initial Neural" ) {
	REQUIRE( feed_forward() == 0 );
}
