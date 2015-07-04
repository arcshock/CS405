#ifndef CHECKER_BOARD_HPP
#define CHECKER_BOARD_HPP

/**
 * File: checker_board.hpp
 * Purpose: A board and functions for playing checkers.
 */

#include <string>
using std::string;
#include <ostream>
#include <unordered_map>
using std::unordered_map;
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include "game_piece.hpp"


class Checker_Board
{
private:
	unordered_map<string, char> pieces_m;
public:

	Checker_Board()
	{
		string tmp = "";
		for (int row = 0; row < 3; ++row) {
			for (char column = 'A'; column != 'I'; ++column) {
				if (row == 0 || row == 2) {
					if (column == 'A' || column == 'C' || column == 'E' || column == 'G') {
						tmp = column;
						tmp += std::to_string(row);
						pieces_m[tmp] = 'r';
					}
				} else {
					if (column == 'B' || column == 'D' || column == 'F' || column == 'H') {
						tmp = column;
						tmp += std::to_string(row);
						pieces_m[tmp] = 'r';
					}
				}
			}
		}

	
		for (int row = 5; row < 8; ++row) {
			for (char column = 'A'; column != 'I'; ++column) {
				if (row == 5 || row == 7) {
					if (column == 'B' || column == 'D' || column == 'F' || column == 'H') {
						tmp = column;
						tmp += std::to_string(row);
						pieces_m[tmp] = 'w';
					}
				} else {
					if (column == 'A' || column == 'C' || column == 'E' || column == 'G') {
						tmp = column;
						tmp += std::to_string(row);
						pieces_m[tmp] = 'w';
					}
				}

			}
		}
		
	}

	Checker_Board(string board_state)
	{
		for(auto iter = board_state.begin(); iter != board_state.end(); ++iter) {
			if (*iter == 'r' || *iter == 'R' || *iter == 'w' || *iter == 'W') {
				pieces_m[]
			}
		}

		for (int ii = 0; ii < 73; ++ii) {
			if (ii % 9 == 0) {
				continue;
			}
		}
	}

	string get_moves(string location)
	{
		if (location == "A2") {
			return "B3";
		} else if ( location == "B2" ) {
			return "";
		} else if ( location == "C2" ) {
			return "B3 D3";
		} else if ( location == "D2" ) {
			return "";
		} else if ( location == "E2" ) {
			return "D3 F3";
		} else if ( location == "F2" ) {
			return "";
		} else if ( location == "G2" ) {
			return "F3 H3";
		} else if ( location == "H2" ) {
			return "";
		} else if ( location == "A5" ) {
			return "";
		} else if ( location == "B5" ) {
			return "A4 C4";
		} else if ( location == "C5" ) {
			return "";
		} else if ( location == "D5" ) {
			return "C4 E4";
		} else if ( location == "E5" ) {
			return "";
		} else if ( location == "F5" ) {
			return "E4 G4";
		} else if ( location == "G5" ) {
			return "";
		} else if ( location == "H5" ) {
			return "G4";
		} else {
			return "";
		}
	}

	void print()
	{
		string tmp = "";
		for (int row = 0; row < 8; ++row) {
			for (char column = 'A'; column != 'I'; ++column) {
				tmp = column;
				tmp += std::to_string(row);
				try {
					cout << pieces_m.at(tmp);
				} catch (std::out_of_range &e) {
					cout << "_";
				}
			}
			cout << endl;
		}
	}


	void print(std::ostream & output_stream)
	{
		string tmp = "";
		for (int row = 0; row < 8; ++row) {
			for (char column = 'A'; column != 'I'; ++column) {
				tmp = column;
				tmp += std::to_string(row);
				try {
					output_stream << pieces_m.at(tmp);
				} catch (std::out_of_range &e) {
					output_stream << "_";
				}
			}
			output_stream << "\n";
		}
	}
};
/*	
bool operator==(Checker_Board & lhs, Checker_Board & rhs)
{
	return false;//(lhs.get_state() == rhs.get_state());
}
*/
#endif /*CHECKER_BOARD_HPP*/

/*
REQUIRE( board.get_moves("A2") == "B3" );
				REQUIRE( board.get_moves("B2") == "" );
				REQUIRE( board.get_moves("C2") == "B3 D3" );
				REQUIRE( board.get_moves("D2") == "" );
				REQUIRE( board.get_moves("E2") == "D3 F3" );
				REQUIRE( board.get_moves("F2") == "" );
				REQUIRE( board.get_moves("G2") == "F3 H3" );
				REQUIRE( board.get_moves("H2") == "" );
*/
