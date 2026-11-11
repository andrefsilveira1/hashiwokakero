#pragma once
#include "static_puzzle.hpp"
#include <vector>

namespace hashi {
    struct Evaluation {
        int degree_error = 0;
        int crossing_pairs = 0;
        int disconnected_components = 0;
        int penalty = 0;
        bool is_valid = false;
    };

    class QualityEvaluator {
    public:
        Evaluation evaluate(const Puzzle& puzzle, const std::vector<int>& genome) const;
        int calculate_degree_error(const Puzzle& puzzle, const std::vector<int>& genome) const;
        int calculate_crossing_edges(const Puzzle& puzzle, const std::vector<int>& genome) const;
        int calculate_disconnected_components(const Puzzle& puzzle, const std::vector<int>& genome) const;
    };
} // namespace hashi
