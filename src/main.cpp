#include "board.hpp"
#include "render.hpp"

#include <iostream>
#include <vector>

int main() {
    using namespace hashi;

    const std::vector<std::vector<int>> puzzle = {
        {1, 0, 1}
    };

    const Board board(puzzle);

    std::cout << "Puzzle grid:\n";
    print_board(board);
    std::cout << "Islands found: " << board.island_count() << '\n';
}
