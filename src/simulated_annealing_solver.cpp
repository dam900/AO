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

    auto sorted_items = best.get_sorted_items_by_ratio();
    // std::set<std::vector<uint64_t>> checked_solutions;

    for (uint64_t i = 0; i <= max_iter; i++) {
        best.make_change(sorted_items);

        // auto current_solution = best.get_sol();
        // std::sort(current_solution.begin(), current_solution.end());
        // if (checked_solutions.find(current_solution) != checked_solutions.end()) {
        //     best.revert();
        //     continue;
        // }

        // checked_solutions.insert(current_solution);

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

        t = cooling_strategy_->next(t);

        // Debugowanie
        printf("Iteration %lu, Temperature: %.2f, Best Cost: %lu, Global Best Cost: %lu\n", i, t, best_cost, global_best_cost);
    }

    return global_best;
}