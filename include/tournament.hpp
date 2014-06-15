/**
 * Author: Bucky Frost
 * File: tournament.hpp
 * Purpose: Header file for the turnament class.
 */

#ifndef TOURNAMENT_HPP
#define TOURNAMENT_HPP

#include <list>
#include "minimax.hpp"
#include "neural_network.hpp"
#include "checker_board.hpp"
#include "game.hpp"

// TODO
// Tournament types: round robin, elimination, (swiss-system?)
class Tournament
{
private:
	std::vector<Game *> _games;
public:
	void start(Neural_Network & red_player, Neural_Network & white_player)
	{
		
	}
};

#endif /*TOURNAMENT_HPP*/
