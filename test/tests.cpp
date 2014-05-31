#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

/**
 * Author: Bucky Frost
 * File: tests.cpp
 * Purpose: Testing surite for checkers AI.
 */


#include "catch.hpp"
#include "neural_network.hpp"
#include "checker_board.hpp"


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


TEST_CASE( "Neural Netowrk Serialization" ) {
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

/*
TEST_CASE( "Checker Pieces" ) {
	Checker_Piece red_pawn('r', std::make_pair('a', 0));
	std::vector<coordinate> red_pawn_moves = red_pawn.get_moves();
	REQUIRE( red_pawn_moves.size() == 1 );
	REQUIRE( red_pawn_moves[0] == std::make_pair('b', 1) );

	Checker_Piece white_king('w', std::make_pair('a', 0));
	std::vector<coordinate> white_king_moves = white_king.get_moves();
	REQUIRE( white_king_moves.size() == 1 );
	REQUIRE( white_king_moves[0] == std::make_pair('b', 1) );
}
*/

TEST_CASE( "Checker Board" ) {				
	std::string initial_board = "_w_w_w_w\n"      // 7
					"w_w_w_w_\n"  // 6
					"_w_w_w_w\n"  // 5
					"________\n"  // 4
					"________\n"  // 3
					"r_r_r_r_\n"  // 2
					"_r_r_r_r\n"  // 1
					"r_r_r_r_\n"; // 0 1 2 3 4 5 6 7


	std::ostringstream board_format;

	Checker_Board board;
	board.print_board(board_format);

	REQUIRE(board_format.str() == initial_board);


	std::vector<coordinate> possible_moves = board.get_moves(std::make_pair(0, 0));
	REQUIRE( possible_moves.empty() == true );

	possible_moves = board.get_moves(std::make_pair(2, 2));
	REQUIRE( possible_moves.size() == 2 );
	REQUIRE( possible_moves[0].first == 3 );
	REQUIRE( possible_moves[0].second == 1 );
	REQUIRE( possible_moves[1].first == 3 );
	REQUIRE( possible_moves[1].second == 3 );

	board.move_piece(std::make_pair(2,2), possible_moves[0] );
	possible_moves = board.get_moves(std::make_pair(2, 2) );
	REQUIRE( possible_moves.size() == 0 );

	possible_moves = board.get_moves(std::make_pair(3, 1) );
	REQUIRE( possible_moves.size() == 2 );
	REQUIRE( possible_moves[0].first == 4 );
	REQUIRE( possible_moves[0].second == 0 );
	REQUIRE( possible_moves[1].first == 4 );
	REQUIRE( possible_moves[1].second == 2 );
}


TEST_CASE( "Checker Board Initialization" ) {
	std::string king_trial = "________\n"
				"___r____\n"
				"________\n"
				"________\n"
				"_W____R_\n"
				"________\n"
				"____w___\n"
				"________\n"; // size == 72

	Checker_Board board(king_trial);

	std::ostringstream board_format;
	board.print_board(board_format);

	REQUIRE( board_format.str() == king_trial );

	auto moves = board.get_moves(std::make_pair(6, 3));
	REQUIRE( moves.size() == 2 );
	REQUIRE( moves[0].first == 7 );
	REQUIRE( moves[0].second == 2 );
	
	board.print_board(std::cout);
	std::cout << std::endl;

	board.move_piece(std::make_pair(6, 3), std::make_pair(7,2));
	
	board.print_board(std::cout);
	moves = board.get_moves(std::make_pair(7, 2));
	REQUIRE( moves.size() == 2 );
	REQUIRE( moves[0].first == 6 );
	REQUIRE( moves[0].second == 1 );
	REQUIRE( moves[1].first == 6 );
	REQUIRE( moves[1].second == 3 );

	moves = board.get_moves(std::make_pair(1, 4));
	REQUIRE( moves.size() == 2 );
	REQUIRE( moves[0].first == 0 );
	REQUIRE( moves[0].second == 3 );
	REQUIRE( moves[1].first == 0 );
	REQUIRE( moves[1].second == 5 );

	board.move_piece(std::make_pair(1, 4), moves[1]);

	moves = board.get_moves(moves[1]);
	REQUIRE( moves.size() == 2 );
	REQUIRE( moves[0].first == 1 );
	REQUIRE( moves[0].second == 4 );
	REQUIRE( moves[1].first == 1 );
	REQUIRE( moves[1].second == 6 );


	moves = board.get_moves(std::make_pair(3, 1));

	REQUIRE( moves.size() == 4 );
	REQUIRE( moves[0].first == 4 );
	REQUIRE( moves[0].second == 0 );
	REQUIRE( moves[1].first == 4 );
	REQUIRE( moves[1].second == 2 );
	REQUIRE( moves[2].first == 2 );
	REQUIRE( moves[2].second == 0 );
	REQUIRE( moves[3].first == 2 );
	REQUIRE( moves[3].second == 2 );
	
	
	moves = board.get_moves(std::make_pair(3, 6));

	REQUIRE( moves.size() == 4 );
	REQUIRE( moves[0].first == 4 );
	REQUIRE( moves[0].second == 5 );
	REQUIRE( moves[1].first == 4 );
	REQUIRE( moves[1].second == 7 );
	REQUIRE( moves[2].first == 2 );
	REQUIRE( moves[2].second == 5 );
	REQUIRE( moves[3].first == 2 );
	REQUIRE( moves[3].second == 7 );

	std::cout << std::endl;
	board.move_piece(std::make_pair(3, 6), moves[1]);
	board.print_board(std::cout);
}

TEST_CASE( "Checker Jumps" ) {
	std::string jump_trial = "__w_____\n"
				"___r____\n"
				"___w_w__\n"
				"____R___\n"
				"___w_w__\n"
				"________\n"
				"_w_w__r_\n"
				"__r__W__\n"; // size == 72

	Checker_Board board(jump_trial);

	auto moves = board.get_moves(std::make_pair(0, 5));

	REQUIRE( moves.size() == 1);
}
#endif /*CATCH_CONFIG_MAIN*/
