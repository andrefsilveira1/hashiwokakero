#pragma once

#include <string>
#include <vector>

namespace hashi {

constexpr int NO_LINE = 0;
constexpr int HORIZONTAL = 1;
constexpr int D_HORIZONTAL = 2;
constexpr int VERTICAL = 3;
constexpr int D_VERTICAL = 4;

struct coord {
    int x;
    int y;

    coord();
    coord(int m_x, int m_y);
};

struct cell {
    cell *lft, *rgt, *top, *bot;
    int init_val, val;
    int lft_value = 0;
    int rgt_value = 0;
    int top_value = 0;
    int bot_value = 0;
    int line;
    coord cd;

    cell();
    cell(int v);

    bool is_island() const;
    bool is_open_island() const;
    bool is_closed_island() const;
    int qnt_adj();
    void decrease_val();
    bool add_line(int dir);
    std::vector<cell*> adj_list();
    bool check_adj(cell* c);
    std::string get_cell_val(std::string dir);

    friend bool is_adjacent(cell* c);
};

bool is_adjacent(cell* c);

} // namespace hashi
