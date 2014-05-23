/*
 * Author: Bucky Frost
 * File: tests.cpp
 * Purpose: Testing surite for checkers AI.
 */

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "neural_network.hpp"
#include "checker_board.hpp"
#include <ostream>


std::vector<double> negative_checker_board(32, -1.0);
std::vector<double> empty_checker_board(32, 0.0);
std::vector<double> full_checker_board(32, 1.0);

std::vector<int> standard_network = {32, 40, 10, 1};

TEST_CASE( "Default Constructed Neural Network Class" ) {

	Neural_Network first_net;

	double solution1 = (-1.0*32.0)/(1.0 + abs(-1.0*32.0));
	double solution2 = (0.0*32.0)/(1.0 + abs(0.0*32.0));
	double solution3 = (1.0*32.0)/(1.0 + abs(1.0*32.0));

}


TEST_CASE( "Specified Network Construction" ) {
	std::vector<double> negative_checker_board(32, -1.0);

	std::vector<int> network_layout = {32, 1, 1, 1};

	Neural_Network constructed_network(network_layout);

	REQUIRE( constructed_network.network_evaluate(empty_checker_board) != 0.0 );
	REQUIRE( constructed_network.network_evaluate(negative_checker_board) != 0.0 );
}


TEST_CASE( "Network Operators" ) {
	Neural_Network first_network(standard_network);
	Neural_Network second_network(standard_network);

	REQUIRE( first_network == first_network);

}


TEST_CASE( "Network File I/O" ) {
	Neural_Network saved_network(standard_network);

	std::ofstream ofs("test_network_save.txt");

	boost::archive::text_oarchive oa(ofs);

	oa << saved_network;
	ofs.close();

	saved_network.network_evaluate(negative_checker_board);

	Neural_Network restored_network(standard_network);

	std::ifstream ifs("test_network_save.txt");
	boost::archive::text_iarchive ia(ifs);
	ia >> restored_network;

	REQUIRE( saved_network != restored_network );	

	restored_network.network_evaluate(negative_checker_board);
	REQUIRE( restored_network == saved_network );	
}


TEST_CASE( "Checker Board" ) {
	std::string initial_board = "_w_w_w_w\n"
					"w_w_w_w_\n"
					"_w_w_w_w\n"
					"________\n"
					"________\n"
					"r_r_r_r_\n"
					"_r_r_r_r\n"
					"r_r_r_r_\n";


	std::ostringstream board_format;

	Checker_Board board;
	board.print_board(board_format);

	REQUIRE(board_format.str() == initial_board);


	std::vector<coordinate> possible_moves = board.getMoves(std::make_pair('a',0);
}
