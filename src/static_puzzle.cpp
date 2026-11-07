#include "static_puzzle.hpp"

#include <algorithm>

namespace hashi {
    // Using anonymous namespace to limit this scope
    // I'm wondering if this would be better as a static func. 
    namespace {
        bool edges_cross(const Edge& first, const Edge& second, const std::vector<Island>& islands) {
            const Edge& horizontal = first.is_vertical ? second : first;
            const Edge& vertical = first.is_vertical ? first : second;
            if (horizontal.is_vertical == vertical.is_vertical) {
                return false;
            }

            const Island& horizontal_a = islands[horizontal.island_a];
            const Island& horizontal_b = islands[horizontal.island_b];
            const Island& vertical_a = islands[vertical.island_a];
            const Island& vertical_b = islands[vertical.island_b];

            const int horizontal_row = horizontal_a.x;
            const int vertical_column = vertical_a.y;
            const int min_column = std::min(horizontal_a.y, horizontal_b.y);
            const int max_column = std::max(horizontal_a.y, horizontal_b.y);
            const int min_row = std::min(vertical_a.x, vertical_b.x);
            const int max_row = std::max(vertical_a.x, vertical_b.x);

            return min_column < vertical_column && vertical_column < max_column &&
                   min_row < horizontal_row && horizontal_row < max_row;
        }
    }

    Puzzle generate_puzzle(const Board& board) {
        Puzzle puzzle;
        puzzle.islands = board.islands();
        puzzle.incident_edges.resize(puzzle.islands.size());

        for (const auto& connection : board.connections()) {
            const Island& island_a = puzzle.islands[connection.first];
            const Island& island_b = puzzle.islands[connection.second];

            Edge edge;
            edge.id = static_cast<int>(puzzle.edges.size());
            edge.island_a = connection.first;
            edge.island_b = connection.second;

            edge.is_vertical = island_a.y == island_b.y;
            puzzle.edges.push_back(edge);
        }

        for (const Edge& edge : puzzle.edges) {
            puzzle.incident_edges[edge.island_a].push_back(edge.id);
            puzzle.incident_edges[edge.island_b].push_back(edge.id);
        }

        for (size_t i = 0; i < puzzle.edges.size(); ++i) {
            for (size_t j = i + 1; j < puzzle.edges.size(); ++j) {
                if (edges_cross(puzzle.edges[i], puzzle.edges[j], puzzle.islands)) {
                    puzzle.crossing_pairs.emplace_back(
                        puzzle.edges[i].id, puzzle.edges[j].id);
                }
            }
        }

        return puzzle;
    }
}
