#include "cell.hpp"

#include <algorithm>

namespace hashi {

coord::coord() : x(-1), y(-1) {}
coord::coord(int m_x, int m_y) : x(m_x), y(m_y) {}

cell::cell() : lft(nullptr), rgt(nullptr), top(nullptr), bot(nullptr), init_val(0), val(0), line(NO_LINE) {}

cell::cell(int v)
    : lft(nullptr), rgt(nullptr), top(nullptr), bot(nullptr), init_val(v), val(v), line(NO_LINE) {}

bool cell::is_island() const {
    return is_open_island() || is_closed_island();
}

bool cell::is_open_island() const {
    return val >= 1 && val <= 8;
}

bool cell::is_closed_island() const {
    return val == -1;
}

int cell::qnt_adj() {
    return is_adjacent(lft) + is_adjacent(rgt) + is_adjacent(top) + is_adjacent(bot);
}

void cell::decrease_val() {
    val--;
    if (val == 0) {
        if (lft != nullptr) lft->rgt_value = 0;
        lft = nullptr;
        if (rgt != nullptr) rgt->lft_value = 0;
        rgt = nullptr;
        if (top != nullptr) top->bot_value = 0;
        top = nullptr;
        if (bot != nullptr) bot->top_value = 0;
        bot = nullptr;
        val = -1;
    }
}

bool cell::add_line(int dir) {
    if (line == NO_LINE) {
        line = dir;
    } else {
        line++;
    }
    if (dir == HORIZONTAL) {
        if (top != nullptr && bot != nullptr) {
            top->bot = nullptr;
            bot->top = nullptr;
        }
    } else {
        if (rgt != nullptr && lft != nullptr) {
            rgt->lft = nullptr;
            lft->rgt = nullptr;
        }
    }
    return line == D_HORIZONTAL || line == D_VERTICAL;
}

std::vector<cell*> cell::adj_list() {
    std::vector<cell*> ans;
    if (is_adjacent(lft)) ans.push_back(lft);
    if (is_adjacent(rgt)) ans.push_back(rgt);
    if (is_adjacent(top)) ans.push_back(top);
    if (is_adjacent(bot)) ans.push_back(bot);
    return ans;
}

bool cell::check_adj(cell* c) {
    return lft == c || rgt == c || top == c || bot == c;
}

std::string cell::get_cell_val(std::string dir) {
    if (dir == "lft") {
        if (is_adjacent(lft)) return std::to_string(lft->val);
    } else if (dir == "rgt") {
        if (is_adjacent(rgt)) return std::to_string(rgt->val);
    } else if (dir == "top") {
        if (is_adjacent(top)) return std::to_string(top->val);
    } else if (dir == "bot") {
        if (is_adjacent(bot)) return std::to_string(bot->val);
    } else {
        return "INVALID DIRECTION";
    }
    return "X";
}

bool is_adjacent(cell* c) {
    return c != nullptr && c->is_open_island();
}

} // namespace hashi
