#pragma once
#include "evaluator.hpp"
#include <vector>

namespace hashi {

using Genome = std::vector<int>;

struct Individual {
    Genome genes;
    Evaluation evaluation;
};

} // namespace hashi
