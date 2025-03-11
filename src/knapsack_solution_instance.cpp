#include "knapsack_solution_instance.hpp"

#include <numeric>

uint KnapsackSolutionInstance::cost(const KnapsackProblemInstance& pinstance) {
    return std::accumulate(this->csol_.begin(), this->csol_.end(), 0, [&pinstance](uint sum, const auto& item) { return sum + pinstance.getItemPrice(item); });
}