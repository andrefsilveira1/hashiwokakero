#include "island.hpp"


namespace hashi {
    int Island::get_current_degree() const {
        return this->current_degree;
    }

    int Island::island_error() const {
        return this->required_bridges - this->get_current_degree();
    }
}
