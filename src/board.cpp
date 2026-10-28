#include "board.hpp"

#include <algorithm>
#include <stdexcept>

namespace new_base {

Board::Board(const std::vector<std::vector<int>>& values) {
    if (values.empty() || values.front().empty()) {
        throw std::invalid_argument("A board must have at least one row and column.");
    }

    const std::size_t column_count = values.front().size();
    for (const auto& row : values) {
        if (row.size() != column_count) {
            throw std::invalid_argument("All board rows must have the same number of cells.");
        }
    }

    cells_.resize(values.size(), std::vector<cell>(column_count));
    for (std::size_t row = 0; row < values.size(); ++row) {
        for (std::size_t column = 0; column < column_count; ++column) {
            cell& current = cells_[row][column];
            current.val = values[row][column];
            current.init_val = values[row][column];
            current.cd.x = static_cast<int>(row);
            current.cd.y = static_cast<int>(column);
        }
    }

    initialize();
}

int Board::rows() const {
    return static_cast<int>(cells_.size());
}

int Board::columns() const {
    return cells_.empty() ? 0 : static_cast<int>(cells_.front().size());
}

int Board::island_count() const {
    return island_count_;
}

int Board::max_edges() const {
    int max_edges = 0;
    for(int i = 0; i < rows(); i++){
        for(int j = 0; j < columns(); j++){
            if(cells_[i][j].is_island()){
                max_edges += cells_[i][j].init_val;
            }
        }
    }
    return max_edges;
}

int Board::count_edges() const {
    int sum = 0;
    for(int i = 0; i < rows(); i++){
        for(int j = 0; j < columns(); j++){
            if(cells_[i][j].is_open_island()){
                sum += cells_[i][j].val;
            }
        }
    }

    return sum;
}

int Board::value_function() const {
    return max_edges() - count_edges();
}

cell& Board::at(int row, int column) {
    return cells_[row][column];
}

const cell& Board::at(int row, int column) const {
    return cells_[row][column];
}

const std::vector<std::pair<cell, cell>>& Board::edges() const {
    return edges_;
}

const std::vector<Island>& Board::islands() const {
    return islands_;
}

const Island& Board::island(int id) const {
    return islands_.at(static_cast<std::size_t>(id));
}

bool are_same_line(cell first, cell second) {
    return first.cd.x == second.cd.x;
}

bool are_same_collum(cell first, cell second) {
    return first.cd.y == second.cd.y;
}

void Board::connect_cells(cell& first, cell& second) {
    if (!((are_same_line(first, second) || are_same_collum(first, second)) &&
          first.check_adj(&second) && second.check_adj(&first))) {
        return;
    }

    const int first_id = island_ids_[first.cd.x][first.cd.y];
    const int second_id = island_ids_[second.cd.x][second.cd.y];
    for (const BuiltBridge& bridge : islands_.at(first_id).bridges) {
        if (bridge.island_id == second_id && bridge.degree >= 2) return;
    }
    edges_.push_back({first, second});

    // I don't think this is really nice, but it works. 
    add_built_bridge(first_id, second_id);
    add_built_bridge(second_id, first_id);
    first.decrease_val();
    second.decrease_val();

    bool full = false;
    if (are_same_line(first, second)) {
        const int min_y = std::min(first.cd.y, second.cd.y);
        const int max_y = std::max(first.cd.y, second.cd.y);
        const int row = first.cd.x;
        for (int column = min_y + 1; column <= max_y - 1; ++column) {
            full = cells_[row][column].add_line(HORIZONTAL);
        }
        if (cells_[row][min_y].rgt_value > 0) cells_[row][min_y].rgt_value--;
        if (cells_[row][max_y].lft_value > 0) cells_[row][max_y].lft_value--;
        if (full) {
            if (first.cd.y < second.cd.y) {
                first.rgt = nullptr;
                second.lft = nullptr;
            } else {
                second.rgt = nullptr;
                first.lft = nullptr;
            }
        }
    } else {
        const int min_x = std::min(first.cd.x, second.cd.x);
        const int max_x = std::max(first.cd.x, second.cd.x);
        const int column = first.cd.y;
        for (int row = min_x + 1; row <= max_x - 1; ++row) {
            full = cells_[row][column].add_line(VERTICAL);
        }
        if (cells_[min_x][column].bot_value > 0) cells_[min_x][column].bot_value--;
        if (cells_[max_x][column].top_value > 0) cells_[max_x][column].top_value--;
        if (full) {
            if (first.cd.x < second.cd.x) {
                first.bot = nullptr;
                second.top = nullptr;
            } else {
                second.bot = nullptr;
                first.top = nullptr;
            }
        }
    }
    synchronize_island_adjacency();
}

void Board::initialize() {
    std::vector<cell*> last_island_in_row(rows(), nullptr);
    std::vector<cell*> last_island_in_column(columns(), nullptr);

    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            cell& current = cells_[row][column];
            current.lft = last_island_in_row[row];
            current.top = last_island_in_column[column];

            if (current.is_island()) {
                ++island_count_;
                last_island_in_column[column] = &current;
                last_island_in_row[row] = &current;
            }
        }
    }

    last_island_in_row.assign(rows(), nullptr);
    last_island_in_column.assign(columns(), nullptr);

    for (int row = rows() - 1; row >= 0; --row) {
        for (int column = columns() - 1; column >= 0; --column) {
            cell& current = cells_[row][column];
            current.rgt = last_island_in_row[row];
            current.bot = last_island_in_column[column];

            if (current.is_island()) {
                last_island_in_column[column] = &current;
                last_island_in_row[row] = &current;
            }
        }
    }

    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            cell& current = cells_[row][column];
            if (current.top != nullptr) current.top_value = std::min(current.top->val, 2);
            if (current.bot != nullptr) current.bot_value = std::min(current.bot->val, 2);
            if (current.rgt != nullptr) current.rgt_value = std::min(current.rgt->val, 2);
            if (current.lft != nullptr) current.lft_value = std::min(current.lft->val, 2);
        }
    }
    initialize_islands();
}

void Board::initialize_islands() {
    island_ids_.assign(static_cast<std::size_t>(rows()),
                       std::vector<int>(static_cast<std::size_t>(columns()), -1));
    islands_.clear();
    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < columns(); ++column) {
            const cell& current = cells_[row][column];
            if (!current.is_island()) continue;

            const int id = static_cast<int>(islands_.size());
            island_ids_[row][column] = id;
            Island entry;
            entry.id = id;
            entry.required_bridges = current.init_val;
            entry.x = row;
            entry.y = column;
            islands_.push_back(entry);
        }
    }
    synchronize_island_adjacency();
}

void Board::synchronize_island_adjacency() {
    for (Island& entry : islands_) {
        const cell& source = cells_[entry.x][entry.y];
        set_island_neighbor(entry.above, source.top);
        set_island_neighbor(entry.below, source.bot);
        set_island_neighbor(entry.right, source.rgt);
        set_island_neighbor(entry.left, source.lft);
    }
}

void Board::set_island_neighbor(IslandNeighbor& destination, cell* neighbor) {
    // Começamos sem vizinho. Se a célula não aponta para uma ilha, fica id -1.
    destination.id = -1;
    destination.active = false;

    if (neighbor == nullptr) {
        return;
    }

    const int neighbor_id = island_ids_[neighbor->cd.x][neighbor->cd.y];
    if (neighbor_id == -1) {
        return;
    }

    destination.id = neighbor_id;
    destination.active = neighbor->is_open_island();
}

void Board::add_built_bridge(int from_id, int to_id) {
    Island& from = islands_[from_id];

    for (std::size_t i = 0; i < from.bridges.size(); ++i) {
        if (from.bridges[i].island_id == to_id) {
            from.bridges[i].degree++;
            from.current_degree++;
            return;
        }
    }

    BuiltBridge bridge;
    bridge.island_id = to_id;
    bridge.degree = 1;
    from.bridges.push_back(bridge);
    from.current_degree++;
}

} // namespace new_base
