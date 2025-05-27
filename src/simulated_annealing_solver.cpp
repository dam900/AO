#include "simulated_annealing_solver.hpp"

#include <math.h>
#include <random>

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(uint max_iter, double initial_temp) {
    auto best = sinstance_;
    auto best_cost = best.cost();
    double t = initial_temp;

    auto sorted_items = best.get_sorted_items_by_ratio();

    for (uint i = 0; i <= max_iter; i++) {
        best.make_change(sorted_items);
        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;

        if (current_cost < best_cost) {
            best_cost = current_cost;
        } else if (static_cast<double>(rand()) / RAND_MAX < exp(-delta / t)) {
            best_cost = current_cost;
        } else {
            best.revert();
        }
        t = cooling_strategy_->next(t);
    }

    return best;
}