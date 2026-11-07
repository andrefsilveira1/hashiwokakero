#pragma once

#include "board.hpp"

namespace hashi {

void print_cell_info(cell c);
void print_cell(cell c);
void print_board(const Board& board);
void print_edg_list(const Board& board);

} // namespace hashi
