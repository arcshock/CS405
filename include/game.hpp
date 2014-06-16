/**
 * Author: Bucky Frost
 * File: game.hpp
 * Purpose: Header file for the game class.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include <vector>

class Game
{
private:
	std::vector<Player *> _players;
	Checker_Board * _board;

	Game();
public:
	Game(Player * player1, Player * player2, Checker_Board * board): _board(board)
	{
		_players.push_back(player1);
		_players.push_back(player2);
	}


	void pause()
	{
		// TODO
	}


	Player * begin()
	{
		int counter = 0;
		int num_of_red = 0;
		int num_of_white = 0;
		std::list<Checker_Board> board_history;

		do {
			num_of_red = 0;
			num_of_white = 0;

			
			_board = minimax(*_players.begin(), _board, 6);
			std::swap(_players[0], _players[1]);

			for (int row = 0; row < 8; ++row) {
				for (int col = 0; col < 8; ++col) {
					if (_board->is_red(std::make_pair(row, col))) {
						++num_of_red;
					} else if (_board->is_white(std::make_pair(row, col))) {
						++num_of_white;
					}
				}
			}

/* // TODO Cycle detection!
			if (board_history.size() < 3) {
				board_history.push_back(board);
			} else {
				board_history.push_front(board);
				board_history.pop_back();
			}

			board.print_board(std::cout);
			std::cout << '\n';

			if (board == board_history.back()) {
				std::cout << "REPEAT \n";
			//	std::exit(-1);
			}
*/

		} while (num_of_red && num_of_white);

/* //DEBUGGING
		if (num_of_red > num_of_white) {
			std::cout << "\n"
					"#######\n"
					"RED WON\n"
					"#######\n";
		} else {
			std::cout << "\n"
					"#########\n"
					"WHITE WON\n"
					"#########\n";

		}
*/
		return _players[0];
	}
};

#endif /*GAME_HPP*/
