#pragma once

#include "board.hpp"
#include <utility>
#include <vector>

namespace hashi {
    struct Edge {
        int id;
        int island_a;
        int island_b;
        bool is_vertical;
    };

    struct Puzzle {
        std::vector<Island> islands;
        std::vector<Edge> edges;

        std::vector<std::vector<int>> incident_edges;
        std::vector<std::pair<int, int>> crossing_pairs;
    };

    Puzzle generate_puzzle(const Board& board);
}
