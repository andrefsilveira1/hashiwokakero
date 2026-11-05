#include "static_puzzle.hpp"

namespace new_base {
    Puzzle generate_puzzle(const Board& board) {
        Puzzle puzzle;
        puzzle.islands = board.islands();
        const auto& connections = board.connections();
        for (const auto& connection : connections) {
            Edge edge;
            edge.id = static_cast<int>(puzzle.edges.size());
            edge.island_a = connection.first;
            edge.island_b = connection.second;
            const Island& island_a = puzzle.islands[connection.first];
            const Island& island_b = puzzle.islands[connection.second];
            edge.is_vertical = (island_a.x != island_b.x);
            puzzle.edges.push_back(edge);
        }

        for (const auto& puzzle_edge : puzzle.edges) {
            const Island& island_a = puzzle.islands[puzzle_edge.island_a];
            const Island& island_b = puzzle.islands[puzzle_edge.island_b];
            int x1 = island_a.x;
            int y1 = island_a.y;
            int x2 = island_b.x;
            int y2 = island_b.y;

            if (puzzle_edge.is_vertical) {
                for (int x = std::min(x1, x2) + 1; x < std::max(x1, x2); ++x) {
                    puzzle.connections[x][y1].push_back(puzzle_edge.id);
                }
            } else {
                for (int y = std::min(y1, y2) + 1; y < std::max(y1, y2); ++y) {
                    puzzle.connections[x1][y].push_back(puzzle_edge.id);
                }
            }
        }

        for (size_t i = 0; i < puzzle.edges.size(); ++i) {
            const Edge& edge1 = puzzle.edges[i];
            const Island& island_a1 = puzzle.islands[edge1.island_a];
            const Island& island_b1 = puzzle.islands[edge1.island_b];

            for (size_t j = i + 1; j < puzzle.edges.size(); ++j) {
                const Edge& edge2 = puzzle.edges[j];
                const Island& island_a2 = puzzle.islands[edge2.island_a];
                const Island& island_b2 = puzzle.islands[edge2.island_b];

                if ((island_a1.x < island_a2.x && island_b1.x > island_b2.x) ||
                    (island_a1.x > island_a2.x && island_b1.x < island_b2.x)) {
                    if ((island_a1.y < island_a2.y && island_b1.y > island_b2.y) ||
                        (island_a1.y > island_a2.y && island_b1.y < island_b2.y)) {
                        // The edges cross each other
                        puzzle.crossing_edges[edge1.id][edge2.id].push_back(edge2.id);
                        puzzle.crossing_edges[edge2.id][edge1.id].push_back(edge1.id);
                    }
                }
            }
        }
        return puzzle;
    }

}