#include "render.hpp"

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

namespace hashi {

void print_cell_info(cell c) {
    std::cout << "{ val: " << c.val << ", ";
    std::cout << "lft: " << c.lft_value << ", ";
    std::cout << "rgt: " << c.rgt_value << ", ";
    std::cout << "top: " << c.top_value << ", ";
    std::cout << "bot: " << c.bot_value;
    std::cout << " } ";
}

void print_cell(cell c) {
    if (c.is_island()) {
        std::cout << c.init_val << "  ";
    } else {
        std::vector<std::string> switch_line(6);
        switch_line[NO_LINE] = " ";
        switch_line[HORIZONTAL] = "-";
        switch_line[D_HORIZONTAL] = "=";
        switch_line[VERTICAL] = "|";
        switch_line[D_VERTICAL] = "ǁ";

        if (c.line > D_VERTICAL) std::cout << "? ";
        else std::cout << switch_line[c.line] << " ";
    }
}

void print_board(const Board& board) {
    for (int row = 0; row < board.rows(); row++) {
        for (int column = 0; column < board.columns(); column++) {
            print_cell(board.at(row, column));
        }
        std::cout << std::endl;
    }
}

void print_edg_list(const Board& board) {
    const auto& edges = board.edges();
    std::cout << board.island_count() << " " << static_cast<int>(edges.size()) << std::endl;
    for (const auto& e : edges) {
        std::printf("%d %d %d %d\n", e.first.cd.x, e.first.cd.y,
                    e.second.cd.x, e.second.cd.y);
    }
}

} // namespace hashi
