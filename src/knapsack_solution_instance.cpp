#include "knapsack_solution_instance.hpp"

#include <numeric>

uint KnapsackSolutionInstance::cost() {
    return std::accumulate(this->csol_.begin(), this->csol_.end(), 0, [this](uint sum, const auto& item) { return sum + pinstance_.getItemPrice(item); });
}