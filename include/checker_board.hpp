#ifndef CHECKER_BOARD_HPP
#define CHECKER_BOARD_HPP

/**
 * Author: Bucky Frost
 * File: checker_baord.hpp
 * Purpose: A board and functions for playing checkers.
 */

#include <ostream>

class Checker_Board
{
public:
	void print_board(std::ostream & output_stream)
	{
		output_stream << _board;
	}
private:
	std::string _board = "_w_w_w_w\n"
				"w_w_w_w_\n"
				"_w_w_w_w\n"
				"________\n"
				"________\n"
				"r_r_r_r_\n"
				"_r_r_r_r\n"
				"r_r_r_r_\n";
};
#endif /*CHECKER_BOARD_HPP*/
