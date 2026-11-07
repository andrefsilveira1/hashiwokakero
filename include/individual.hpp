#pragma once
#include "evaluator.hpp"
#include <vector>

using Genome = std::vector<int>;

struct Individual {
    Genome genes;
    QualityEvaluator quality;
};
