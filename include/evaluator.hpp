#pragma once
#include "board.hpp"

namespace hashi {
    class QualityEvaluator {
    public:
        int degree_error = 0;
        int crossing_edges = 0;
        int disconnected_islands = 0;
        int penalty = 0;
        bool is_valid = false;

        int calculate_degree_error(const Board& board) const;
        int calculate_crossing_edges(const Board& board) const;
        int calculate_disconnected_islands(const Board& board) const;
        int calculate_penalty(const Board& board) const;
    };
} // namespace hashi