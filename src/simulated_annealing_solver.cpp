#include "simulated_annealing_solver.hpp"

#include <math.h>

#include <random>

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(uint max_iter, double inital_temp) {
    auto best = sinstance_;
    auto best_cost = best.cost();
    double t = inital_temp;

    for (uint i = 0; i <= max_iter; i++) {
        best.make_change();
        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;
        if (current_cost < best_cost) {
            best_cost = current_cost;
        } else if (0.6 < exp(-delta / t)) /*zmienic na nie stałą*/ {
            best_cost = current_cost;
        } else {
            best.revert();
        }
        t = cooling_strategy_->next(t);
    }
    return sinstance_;
}