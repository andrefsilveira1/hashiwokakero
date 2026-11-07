#pragma once

#include "cell.hpp"

#include <utility>
#include <vector>
#include "island.hpp"

namespace hashi {

using board_t = std::vector<std::vector<cell>>;
using Connection = std::pair<int, int>;


class Board {
public:
    explicit Board(const std::vector<std::vector<int>>& values);

    int rows() const;
    int columns() const;
    int island_count() const;
    int max_edges() const;
    int count_edges() const;
    int value_function() const;
    bool bool_value_function() const;

    cell& at(int row, int column);
    const cell& at(int row, int column) const;
    const std::vector<std::pair<cell, cell>>& edges() const;
    const std::vector<Island>& islands() const;
    const Island& island(int id) const;
    const std::vector<Connection>& connections() const;

    void connect_cells(cell& first, cell& second);

private:
    board_t cells_;
    int island_count_ = 0;
    std::vector<std::pair<cell, cell>> edges_;
    std::vector<Island> islands_;
    std::vector<std::vector<int>> island_ids_;
    std::vector<Connection> connections_;

    void initialize();
    void initialize_islands();
    void initialize_connections();
    bool reach_column(const cell& first, const cell& second) const;
    bool reach_row(const cell& first, const cell& second) const;
    void print_connections();
    void synchronize_island_adjacency();
    void set_island_neighbor(IslandNeighbor& destination, cell* neighbor);
    void add_built_bridge(int from_id, int to_id);
};

bool are_same_line(cell first, cell second);
bool are_same_column(cell first, cell second);

} // namespace hashi
