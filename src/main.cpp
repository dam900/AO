#include <iostream>
#include <map>
#include <vector>
#include <memory>

#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"
#include "simulated_annealing_solver.hpp"

int main() {

    auto items = BpItems{{1, 1}, {2, 2}, {1, 2}, {3, 3}, {4, 5}, {2, 3}};

    KnapsackProblemInstance bp = KnapsackProblemInstance{};
    bp.load(items, 5);

    std::cout << "Items in the problem instance:" << std::endl;
    for (const auto& item : bp) {
        std::cout << "Item weight: " << item.first << ", value: " << item.second << std::endl;
    }

    auto cooling_strategy = std::make_unique<LogarithmicCoolingStrategy>(0.01);

    SimulatedAnnealingSolver solver(std::move(cooling_strategy), bp);

    uint max_iter = 1000;
    double initial_temp = 100.0;
    auto solution = solver.solve(max_iter, initial_temp);

    std::cout << "\nBest solution found:" << std::endl;
    uint total_weight = 0;
    uint total_value = 0;
    for (const auto& item_id : solution.get_sorted_items_by_ratio()) {
        auto item = bp.getItem(item_id.first);
        total_weight += item.first;
        total_value += item.second;
        std::cout << "Item ID: " << item_id.first << ", weight: " << item.first << ", value: " << item.second << std::endl;
    }
    std::cout << "Total weight: " << total_weight << ", Total value: " << total_value << std::endl;

    return 0;
}
