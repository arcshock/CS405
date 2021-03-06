/**
 * Author: Bucky Frost
 * File: player.hpp
 * Purpose: Header file for the players class.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <string>
using std::string;

class Player
{
protected:
	string _name;
	char _color;
	

	Player() = default;
public:
	Player(char color, std::string name = "unknown"): _name(name), _color(color)
	{}
// TODO
// Would this function call the approipriate minimax function?
//	void make_move(Checker_Board current_board) = 0;

	virtual ~Player() = default;
};
#endif /*PLAYER_HPP*/
