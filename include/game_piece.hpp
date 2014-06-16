#ifndef GAME_PIECE_HPP
#define GAME_PIECE_HPP

/**
 * Author: Bucky Frost
 * File: game_piece.hpp
 * Purpose: Define the game pieces of board games.
 */

#include <utility>

typedef std::pair<int, int> coordinate;

class Game_Piece 
{
public:
	Game_Piece() = default;


	Game_Piece(coordinate board_location): _board_location(board_location) {}
	virtual	std::vector<coordinate> get_moves() = 0;

protected:
	coordinate _board_location;
};


class Checker_Piece : public Game_Piece
{
public:
	Checker_Piece() = default;
	Checker_Piece(char type, coordinate board_location) : Game_Piece(board_location) 
	{
		if (type == 'r' || type == 'R' || type == 'w' || type == 'W') {
			_type = type;
		} else {
			throw std::invalid_argument("Invalid Checker piece type");
		}
		if ((board_location.first == 'a' && _type == 'w') || (board_location.first == 'h' && _type == 'r')) {
			_type = toupper(_type);
		}
		
	}


	std::vector<coordinate> get_moves()
	{
		std::vector<coordinate> possible_moves;

		if (_type == 'R' || _type == 'W') {
			auto moves = king_moves();
			possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
		} else {
			auto moves = pawn_moves(_type);
			possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
		}

		return possible_moves;
	}
private:
	char _type;


	std::vector<coordinate> pawn_moves(char type)
	{
		char row = _board_location.first;
		int column = _board_location.second;
		std::vector<coordinate> pawn_moves;

		if (type == 'r' || type == 'W') {
			if ( 'h' > row && row >= 'a') {
				++row;
			}
		} else {
			if ( 'h' >= row && row > 'a') {
				--row;
			}
		}

		if (column - 1 >= 0) {
			pawn_moves.emplace_back(std::make_pair(row, column - 1));
		}
		if (column + 1 <= 7) {
			pawn_moves.emplace_back(std::make_pair(row, column + 1));
		}

		return pawn_moves;
	}

	std::vector<coordinate> king_moves()
	{
		std::vector<coordinate> king_moves;

		if (_type == 'R') {
			auto red_pawn_moves = pawn_moves('r');
			king_moves.insert(king_moves.end(), red_pawn_moves.begin(), red_pawn_moves.end());
		} else {
			auto white_pawn_moves = pawn_moves(_type);
			king_moves.insert(king_moves.end(), white_pawn_moves.begin(), white_pawn_moves.end());
		}

		return king_moves;
	}

};
#endif /*GAME_PIECE_HPP*/
