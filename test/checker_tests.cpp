#ifndef CHECKER_TEST
#define CHECKER_TEST

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "checker_board.hpp"

TEST_CASE ("Checker Board") {
	SECTION ("Board Construction") {
		Checker_Board test_board;
		char expected = ' ';
		std::string location = "";
		test_board.print();

		for (int row = 0; row < 3; ++row) {
			for (char column = 'A'; column < 'I'; ++column) {
				switch (row) {
					case 0:
					case 2:
						switch (column) {
							case 'A':
							case 'C':
							case 'E':
							case 'G':
								expected = 'r';
								location = column + std::to_string(row);
								REQUIRE ( test_board.space_state(location) == expected );
								break;
						}
						break;
					case 1:
						switch (column) {
							case 'B':
							case 'D':
							case 'F':
							case 'H':
								expected = 'r';
								location = column + std::to_string(row);
								REQUIRE ( test_board.space_state(location) == expected );
								break;
						}
						break;
					case 6:
						switch (column) {
							case 'A':
							case 'C':
							case 'E':
							case 'G':
								expected = 'w';
								location = column + std::to_string(row);
								REQUIRE ( test_board.space_state(location) == expected );
								break;
						}
						break;

					case 5:
					case 7:
						switch (column) {
							case 'B':
							case 'D':
							case 'F':
							case 'H':
								expected = 'w';
								location = column + std::to_string(row);
								REQUIRE ( test_board.space_state(location) == expected );
								break;
						}
						break;

					default:
						expected = '_';
						location = column + std::to_string(row);
						REQUIRE ( test_board.space_state(location) == expected );
						break;
				}
			}
		}
	}

	SECTION ("First Red Row Pawn Moves") {
		Checker_Board board;
		int move_count = 0;
		auto available_moves = board.get_moves("A2");
		for (auto it = available_moves.begin(); it != available_moves.end(); ++it) {
			++move_count;
		}
		REQUIRE ( move_count == 2 );
	}
}
#endif /*CHECKER_TEST*/
