#ifndef GAME_PIECE_HPP
#define GAME_PIECE_HPP

/**
 * Author: Bucky Frost
 * File: game_piece.hpp
 * Purpose: Define the game pieces of board games.
 */

#include <utility>

typedef std::pair<char, int> coordinate;

class Game_Piece{
public:
	Game_Piece() = default;


	Game_Piece(char color, std::string type, coordinate board_location): _color(color), _type(type), _board_location(board_location) {}
	std::vector<coordinate> get_moves()
	{
		char row = _board_location.first;
		int column = _board_location.second;

		std::vector<coordinate> possible_moves;

		if (_type == "pawn") {
			// TODO range checking on row.

			if (_color == 'r') {
				++row;
			} else {
				--row;
			}

			if (column - 1 >= 0) {
				possible_moves.push_back(std::make_pair(row, column - 1));
			}

			if (column + 1 <= 7) {
				possible_moves.push_back(std::make_pair(row, column + 1));
			}

		} else if (_type == "king") {
		
			++row;
			
			if (column - 1 >= 0) {
				possible_moves.push_back(std::make_pair(row, column - 1));
			}

			if (column + 1 <= 7) {
				possible_moves.push_back(std::make_pair(row, column + 1));
			}

			row -= 2;
			
			if (column - 1 >= 0) {
				possible_moves.push_back(std::make_pair(row, column - 1));
			}

			if (column + 1 <= 7) {
				possible_moves.push_back(std::make_pair(row, column + 1));
			}

		}
	}
private:
	char _color;
	std::string _type;
	coordinate _board_location;
};
#endif /*GAME_PIECE_HPP*/
