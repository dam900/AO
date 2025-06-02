#include "simulated_annealing_solver.hpp"

#include <math.h>
#include <algorithm>
#include <random>
#include <set>

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(uint64_t max_iter, double initial_temp) {
    auto best = sinstance_;
    auto global_best = sinstance_;
    auto best_cost = best.cost();
    auto global_best_cost = best_cost;
    double t = initial_temp;
    auto sorted_items = pinstance_.get_sorted_items_by_ratio();
    printf("Sorted items: ");
    for (const auto& item : sorted_items) {
        printf("id: %li , ratio: %f", item.first, item.second);
        printf("\n");
    }
    std::set<std::vector<bool>> checked_solutions;

    for (uint64_t i = 0; i <= max_iter; i++) {
        best.make_change(checked_solutions);

        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;

        if (current_cost > global_best_cost) {
            global_best = best;
            global_best_cost = current_cost;
        }

        if (current_cost > best_cost) {
            best_cost = current_cost;
        } else if (static_cast<double>(rand()) / RAND_MAX < exp(-delta / t)) {
            best_cost = current_cost;
        } else {
            best.revert();
        }

        checked_solutions.insert(best.get_sol());

        t = cooling_strategy_->next(t);

        printf("Iteration %lu, Weight: %lu, Best Cost: %lu, Global Best Cost: %lu\n",
               i, best.weight(), best_cost, global_best_cost);
    }

    return global_best;
}