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
			}
		}

		for (int ii = 0; ii < 73; ++ii) {
			if (ii % 9 == 0) {
				continue;
			}
		}
	}

	char space_state(string location)
	{
		return pieces_m[location];
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
#endif /*CHECKER_BOARD_HPP*/
