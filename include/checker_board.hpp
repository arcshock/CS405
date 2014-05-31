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
			_board.push_back(temp);
			temp.clear();
		}
	}

	Checker_Board(std::string input_board)
	{
		if (input_board.size() != 72)
			throw std::invalid_argument("Invalid Board");

		for (int board_row = 0; board_row < 8; ++board_row) {
			_board.emplace_back(8, '_');
		}

		int string_index = 0;
		for (char board_row = 7; board_row >= 0; --board_row) {
			for (int board_column = 0; board_column < 8; ++board_column) {
				_board[board_row][board_column] = input_board[string_index++];
			}
			++string_index; //get rid of the new line.
		} 
	}


	void print_board(std::ostream & output_stream)
	{
		for (char board_column = 7; board_column >= 0; --board_column) {
			for (int board_row = 0; board_row < 8; ++board_row) {
				output_stream << _board[board_column][board_row];
			}
			output_stream << "\n";
		}

/*
		for (auto row : _board) {
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

		switch (_board[row][column]) {
			case 'r':
				pawn_jumps('w', board_coordinate, moves);
				if(moves.empty()) {
					if (is_valid(std::make_pair(column - 1, row + 1)) && is_empty(std::make_pair(row + 1, column - 1)))
						moves.emplace_back(std::make_pair(row + 1, column - 1));
					if (is_valid(std::make_pair(column + 1, row + 1)) && is_empty(std::make_pair(row + 1, column + 1)))
						moves.emplace_back(std::make_pair(row + 1, column + 1));
				}
				break;
			case 'w':
				if (is_valid(std::make_pair(column - 1, row + 1)) && (_board[row + 1][column - 1] == 'r' || _board[row + 1][column - 1] == 'R')) {
					if (is_valid(std::make_pair(column - 2, row + 2)) && (_board[row + 2][column - 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column - 2));
				} if (is_valid(std::make_pair(column + 1, row + 1)) && (_board[row + 1][column + 1] == 'r' || _board[row + 1][column + 1] == 'R')) {
					if (is_valid(std::make_pair(column + 2, row + 2)) && (_board[row + 2][column + 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column + 2));
				} else {
					if (is_valid(std::make_pair(column - 1, row - 1)) && _board[row - 1][column - 1] == '_')
						moves.emplace_back(std::make_pair(row - 1, column - 1));
					if (is_valid(std::make_pair(column + 1, row - 1)) && _board[row - 1][column + 1] == '_')
						moves.emplace_back(std::make_pair(row - 1, column + 1));
				}
				break;
			case 'R':
			case 'W':
				if (is_valid(std::make_pair(column - 1, row + 1)) && (_board[row + 1][column - 1] == 'r' || _board[row + 1][column - 1] == 'R')) {
					if (is_valid(std::make_pair(column - 2, row + 2)) && (_board[row + 2][column - 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column - 2));
				} else if (is_valid(std::make_pair(column + 1, row + 1)) && (_board[row + 1][column + 1] == 'r' || _board[row + 1][column + 1] == 'R')) {
					if (is_valid(std::make_pair(column + 2, row + 2)) && (_board[row + 2][column + 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column + 2));
				} else if (is_valid(std::make_pair(column - 1, row + 1)) && (_board[row + 1][column - 1] == 'w' || _board[row + 1][column - 1] == 'W')) {
					if (is_valid(std::make_pair(column - 2, row + 2)) && (_board[row + 2][column - 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column - 2));
				} else if (is_valid(std::make_pair(column + 1, row + 1)) && (_board[row + 1][column + 1] == 'w' || _board[row + 1][column + 1] == 'W')) {
					if (is_valid(std::make_pair(column + 2, row + 2)) && (_board[row + 2][column + 2] == '_'))
						moves.emplace_back(std::make_pair(row + 2, column + 2));
				} else {
					if (is_valid(std::make_pair(column - 1, row + 1)) && _board[row + 1][column - 1] == '_')
						moves.emplace_back(std::make_pair(row + 1, column - 1));
					if (is_valid(std::make_pair(column + 1, row + 1)) && _board[row + 1][column + 1] == '_')
						moves.emplace_back(std::make_pair(row + 1, column + 1));
					if (is_valid(std::make_pair(column - 1, row - 1)) && _board[row - 1][column - 1] == '_')
						moves.emplace_back(std::make_pair(row - 1, column - 1));
					if (is_valid(std::make_pair(column + 1, row - 1)) && _board[row - 1][column + 1] == '_')
						moves.emplace_back(std::make_pair(row - 1, column + 1));
				}
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

		if (row + 2 == move_row)
			if(column + 2 == move_column)
				_board[row + 1][column + 1] = '_';
			else
				_board[row + 1][column - 1] = '_';
		else if (row - 2 == move_row)
			if (column + 2 == move_column)
				_board[row - 1][column + 1] = '_';
			else
				_board[row - 1][column - 1] = '_';

		switch (_board[row][column]) {
			case 'r':
				if (_board[move_row][move_column] == '_')
					std::swap(_board[row][column], _board[move_row][move_column]);
				if (move_row == 7)
					_board[move_row][move_column] = 'R';
			case 'w':
				if (_board[move_row][move_column] == '_')
					std::swap(_board[row][column], _board[move_row][move_column]);
				if (move_row == 0)
					_board[move_row][move_column] = 'W';
			case 'R':
			case 'W':
				if (_board[move_row][move_column] == '_')
					std::swap(_board[row][column], _board[move_row][move_column]);
		}
	}
private:
	std::vector<std::vector<char> > _board;

	bool is_valid(coordinate board_location)
	{
		int row = board_location.first;
		int column = board_location.second;

		return (( 0 <= row && row < 8) && (0 <= column && column < 8));
	}

	bool is_empty(coordinate board_cell)
	{
		int row = board_cell.first;
		int column = board_cell.second;

		return (_board[row][column] == '_');
	}


	void pawn_jumps(char enemy_color, coordinate location, std::vector<coordinate> moves)
	{
		int row = location.first;
		int column = location.second;
		int row_offset = 0;

		if (enemy_color == 'r')
			row_offset = -1;
		else
			row_offset = 1;
			
		for (int col_offset = -1; col_offset < 1; col_offset += 2) {
			if (is_valid(std::make_pair(column + col_offset, row + row_offset))) {
				char adjacent_space = std::tolower(_board[row + row_offset][column + col_offset]);
				if (adjacent_space == std::tolower(enemy_color))
					if (is_valid(std::make_pair(column + col_offset*2, row + row_offset*2)) && 
					(is_empty(std::make_pair(row + row_offset*2, column + col_offset*2))))
						moves.emplace_back(std::make_pair(row + row_offset*2, column + col_offset*2));
			}
		}
	}
};
#endif /*CHECKER_BOARD_HPP*/
