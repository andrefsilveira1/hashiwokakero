#include "board.hpp"
#include "puzzle_io.hpp"
#include "render.hpp"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    using namespace hashi;

    // I've implemented the puzzle_io in order to make it easy to read the puzzle
    // rather than using hard coded valus
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <puzzle-file>\n";
        return 1;
    }

    try {
        const auto values = read_puzzle_file(argv[1]);
        const Board board(values);

        std::cout << "Puzzle:\n";
        print_board(board);
        std::cout << "Islands found: " << board.island_count() << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error reading the puzzle: " << error.what() << '\n';
        return 1;
    }
}
