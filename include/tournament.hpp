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

// TODO
// Tournament types: round robin, elimination, (swiss-system?)
class Tournament
{
public:
	void start(Neural_Network & red_player, Neural_Network & white_player)
	{
		Checker_Board board;

		for (int counter = 0; counter < 150; ++counter) {
			if (counter % 2 == 0) {
				board = minimax(red_player, board, 6, 'r');
			} else {
				board = minimax(white_player, board, 6, 'w');
			}
		}
		board.print_board(std::cout);

		int counter = 0;
		int num_of_red = 0;
		int num_of_white = 0;
		std::list<Checker_Board> board_history;

		do {
			num_of_red = 0;
			num_of_white = 0;

			if (counter % 2 == 0) {
				board = minimax(red_player, board, 6, 'r');
			} else {
				board = minimax(white_player, board, 6, 'w');
			}
			++counter;

			for (int row = 0; row < 8; ++row) {
				for (int col = 0; col < 8; ++col) {
					if (board.is_red(std::make_pair(row, col))) {
						++num_of_red;
					} else if (board.is_white(std::make_pair(row, col))) {
						++num_of_white;
					}
				}
			}

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

		} while ( num_of_red > 0 && num_of_white > 0 );

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
	}
private:
};

#endif /*TOURNAMENT_HPP*/
