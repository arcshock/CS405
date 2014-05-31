#ifndef CHECKER_BOARD_HPP
#define CHECKER_BOARD_HPP

/**
 * Author: Bucky Frost
 * File: checker_baord.hpp
 * Purpose: A board and functions for playing checkers.
 */

#include <map>
#include <string>
#include <ostream>
#include "game_piece.hpp"


class Checker_Board
{
public:
	Checker_Board()
	{
		std::vector<char> temp;
		temp.clear();

		for (int board_row = 0; board_row < 8; ++board_row) {
			for (int board_column = 0; board_column < 8; ++board_column) {
				switch (board_row) {
					case 0:
					case 2:
						if (board_column%2 == 0)
							temp.emplace_back('r');
						else
							temp.emplace_back('_');
						break;
					case 1:
						if (board_column%2 == 1)
							temp.emplace_back('r');
						else
							temp.emplace_back('_');
						break;
					case 5:
					case 7:
						if (board_column%2 == 1)
							temp.emplace_back('w');
						else
							temp.emplace_back('_');
						break;
					case 6:
						if (board_column%2 == 0) 
							temp.emplace_back('w');
						else
							temp.emplace_back('_');
						break;
					default:
						temp.emplace_back('_');
						break;
				
				}
			}
			_board_pieces.push_back(temp);
			temp.clear();
		}
	}

	Checker_Board(std::string input_board)
	{
		if (input_board.size() != 72)
			throw std::invalid_argument("Invalid Board");

		for (int board_row = 0; board_row < 8; ++board_row) {
			_board_pieces.emplace_back(8, '_');
		}

		int string_index = 0;
		for (char board_row = 7; board_row >= 0; --board_row) {
			for (int board_column = 0; board_column < 8; ++board_column) {
				_board_pieces[board_row][board_column] = input_board[string_index++];
			}
			++string_index; //get rid of the new line.
		} 
	}


	void print_board(std::ostream & output_stream)
	{
		for (char board_column = 7; board_column >= 0; --board_column) {
			for (int board_row = 0; board_row < 8; ++board_row) {
				output_stream << _board_pieces[board_column][board_row];
			}
			output_stream << "\n";
		}

/*
		for (auto row : _board_pieces) {
			for (auto board_space : row) {
				output_stream << board_space;
			}
			output_stream << "\n";
		}
*/
	}
	

	// This could be a bad method in that it reports moves of a piece that could be made invalid.
	std::vector<coordinate> get_moves(coordinate board_coordinate)
	{
		std::vector<coordinate> moves;

		int row = board_coordinate.first;
		int column = board_coordinate.second;

		if ((0 > column && column > 7) || ( 0 > row && row > 7))
			throw std::out_of_range ("Invalid board location");

		switch (_board_pieces[row][column]) {
			case 'r':
				if ((column - 1 >= 0) && (row + 1 < 8) && _board_pieces[row + 1][column - 1] == '_')
					moves.emplace_back(std::make_pair(row + 1, column - 1));
				if ((column + 1 >= 0) && (row + 1 < 8) && _board_pieces[row + 1][column + 1] == '_')
					moves.emplace_back(std::make_pair(row + 1, column + 1));
				break;
			case 'w':
				if ((column - 1 >= 0) && (row - 1 >= 0) && _board_pieces[row - 1][column - 1] == '_')
					moves.emplace_back(std::make_pair(row - 1, column - 1));
				if ((column + 1 >= 0) && (row - 1 >= 0) && _board_pieces[row - 1][column + 1] == '_')
					moves.emplace_back(std::make_pair(row - 1, column + 1));
				break;
			case 'R':
			case 'W':
				if ((column - 1 >= 0) && (row + 1 < 8) && _board_pieces[row + 1][column - 1] == '_')
					moves.emplace_back(std::make_pair(row + 1, column - 1));
				if ((column + 1 >= 0) && (row + 1 < 8) && _board_pieces[row + 1][column + 1] == '_')
					moves.emplace_back(std::make_pair(row + 1, column + 1));
				if ((column - 1 >= 0) && (row - 1 >= 0) && _board_pieces[row - 1][column - 1] == '_')
					moves.emplace_back(std::make_pair(row - 1, column - 1));
				if ((column + 1 >= 0) && (row - 1 >= 0) && _board_pieces[row - 1][column + 1] == '_')
					moves.emplace_back(std::make_pair(row - 1, column + 1));
				break;
			default:
				break;
		}
		return moves;
	}


	void move_piece(coordinate piece_location, coordinate move)
	{
		int row = piece_location.first;
		int column = piece_location.second;

		int move_row = move.first;
		int move_column = move.second;

		switch (_board_pieces[row][column]) {
			case 'r':
				if (_board_pieces[move_row][move_column] == '_')
					std::swap(_board_pieces[row][column], _board_pieces[move_row][move_column]);
				if (move_row == 7)
					_board_pieces[move_row][move_column] = 'R';
			case 'w':
				if (_board_pieces[move_row][move_column] == '_')
					std::swap(_board_pieces[row][column], _board_pieces[move_row][move_column]);
				if (move_row == 0)
					_board_pieces[move_row][move_column] = 'W';
			case 'R':
			case 'W':
				if (_board_pieces[move_row][move_column] == '_')
					std::swap(_board_pieces[row][column], _board_pieces[move_row][move_column]);
		}
	}
private:
	std::vector<std::vector<char>> _board_pieces;
};
#endif /*CHECKER_BOARD_HPP*/
