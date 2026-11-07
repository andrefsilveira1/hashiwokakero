#pragma once
#include <vector>

struct IslandNeighbor {
    int id = -1;
    bool active = false;
};

struct BuiltBridge {
    int island_id = -1;
    int degree = 0; // Using this degree variable to represents the number of bridges between two island.
};

namespace hashi {


    class Island {
    public:
        int id = -1;
        int required_bridges = 0;
        int current_degree = 0;
        int x = -1;
        int y = -1;
        IslandNeighbor above, below, right, left;
        std::vector<BuiltBridge> bridges;

        Island();
        int get_current_degree() const;
        int island_error() const;
    };

} // namespace hashi