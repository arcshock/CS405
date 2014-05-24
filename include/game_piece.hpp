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
private:
	char _color;
	std::string _type;
	coordinate _board_location;
};
#endif /*GAME_PIECE_HPP*/
