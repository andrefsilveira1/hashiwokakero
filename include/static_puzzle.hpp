#pragma once

#include "board.hpp"
#include <utility>
#include <vector>

namespace new_base {
    struct Edge {
        int id;
        int island_a;
        int island_b;
        bool is_vertical;
    };

    struct Puzzle {
        std::vector<Island> islands;
        std::vector<Edge> edges;

        std::vector<std::vector<std::vector<int>>> connections;
        std::vector<std::vector<std::vector<int>>> crossing_edges;
    };

    Puzzle generate_puzzle(const Board& board);
}