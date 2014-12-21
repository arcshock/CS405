/**
 * Author: Bucky Frost
 * File: minimax.hpp
 * Purpose: Header file of the minimax search algorithm.
 */

#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "neural_network.hpp"
#include "checker_board.hpp"
#include <queue>
#include <limits>

typedef std::pair<coordinate, std::vector<coordinate> > piece_moves;

Checker_Board min(Neural_Network & player, Checker_Board board, std::vector<piece_moves> moves);
Checker_Board max(Neural_Network & player, Checker_Board board, std::vector<piece_moves> moves);
Checker_Board minimax(Neural_Network & player, Checker_Board & board, int depth, char player_color);
Checker_Board * minimax(Player * player, Checker_Board * board, int depth);


Checker_Board * minimax(Player * player, Checker_Board * board, int depth)
{
	// TODO
	return board;
}

// Maybe have the order of the network be the determining factor for maximizing
Checker_Board minimax(Neural_Network & player, Checker_Board & board, int depth, char player_color)
{
	if (depth == 0) {
		return board;
	}

	std::vector<piece_moves> red_moves;
	std::vector<piece_moves> white_moves;

	//double best_value = std::numeric_limits<double>::max();

	// Get the moves of current board
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			auto location = std::make_pair(row, col);
			if (board.is_red(location)) {
				red_moves.emplace_back(std::make_pair(location, board.get_moves(location)));
			} else if (board.is_white(location)) {
				white_moves.emplace_back(std::make_pair(location, board.get_moves(location)));
			}
		}
	}

	if (depth % 2 == 0) { // Player's turn, max
		switch (player_color) {
		case 'r':
			return max(player, board, red_moves);
		case 'w':
			return max(player, board, white_moves);
		}
	} else { // Oponent's turn, min
		switch (player_color) {
		case 'r':
			return min(player, board, red_moves);
		case 'w':
			return min(player, board, white_moves);
		}
	}
	return board;
}

Checker_Board min(Neural_Network & player, Checker_Board board, std::vector<piece_moves> moves) 
{
	double best_value = std::numeric_limits<double>::max();
	auto eval_board = board;
	Checker_Board best_state;

	for (auto move : moves) {
		for (int ii = 0; ii < move.second.size(); ++ii) {
			eval_board.move_piece(move.first, move.second[ii]);
			auto board_state = eval_board.get_state();
			if (player.network_evaluate(board_state) < best_value) {
				best_value = player.network_evaluate(board_state);
				best_state = eval_board;
			}
		}
		eval_board = board;
	}
	return best_state;
}


Checker_Board max(Neural_Network & player, Checker_Board board, std::vector<piece_moves> moves)
{
	double best_value = std::numeric_limits<double>::lowest();
	auto eval_board = board;
	Checker_Board best_state;

	for (auto move : moves) {
		for (int ii = 0; ii < move.second.size(); ++ii) {
			eval_board.move_piece(move.first, move.second[ii]);
			auto board_state = eval_board.get_state();
			if (player.network_evaluate(board_state) > best_value) {
				best_value = player.network_evaluate(board_state);
				best_state = eval_board;
			}
		}
		eval_board = board;
	}
	return best_state;
}
#endif /*MINIMAX_HPP*/
