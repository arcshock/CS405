/*
 * Author: Bucky Frost
 * File: tests.cpp
 * Purpose: Testing surite for checkers AI.
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "neural_network.hpp"

TEST_CASE( "Default Constructed Neural Network Class" ) {

	Neural_Network first_net;

	std::vector<double> negative_checker_board(32, -1.0);
	double solution1 = (-1.0*32.0)/(1.0 + abs(-1.0*32.0));


	std::vector<double> empty_checker_board(32, 0.0);
	double solution2 = (0.0*32.0)/(1.0 + abs(0.0*32.0));


	std::vector<double> full_checker_board(32, 1.0);
	double solution3 = (1.0*32.0)/(1.0 + abs(1.0*32.0));

/*	REQUIRE( first_net.network_evaluate(negative_checker_board) == solution1 );
	REQUIRE( first_net.network_evaluate(empty_checker_board) == solution2 );
	REQUIRE( first_net.network_evaluate(full_checker_board) == solution3 );*/
}

TEST_CASE( "Specified Network Construction" ) {
	std::vector<double> empty_checker_board(32, 0.0);
	std::vector<double> negative_checker_board(32, -1.0);

	std::vector<int> network_layout = {32, 1, 1, 1};

	Neural_Network constructed_network(network_layout);

	REQUIRE( constructed_network.network_evaluate(empty_checker_board) != 0.0 );
	REQUIRE( constructed_network.network_evaluate(negative_checker_board) != 0.0 );
}
