/**
 * Author: Bucky Frost
 * File: minimax.hpp
 * Purpose: Header file of the minimax search algorithm.
 */

#include "neural_network.hpp"
#include "checker_board.hpp"
#include <queue>

double minimax(Neural_Network & white_player, Neural_Network & red_player, Checker_Board & board, int ply)
{
	// TODO
	std::priority_queue<std::vector<coordinate> > pieces_moves;

	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			auto location = std::make_pair(row, col);
			if (ply % 2 == 0) {
				if (board.is_red()) {
					auto move = board.get_move();
					Checker_Board evaluation_board = board;
					evaluation_board.move_piece(location, move);
				} 
			else {
				if (board.is_white()) {
					piece_moves.emplace(board.get_move());
				}
			}
		}
	}


}
