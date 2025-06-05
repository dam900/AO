#include "simulated_annealing_solver.hpp"

#include <math.h>
#include <algorithm>
#include <random>
#include <set>

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(int max_iter, double initial_temp) {
    auto best = sinstance_;
    auto global_best = sinstance_;
    auto best_cost = best.cost();
    auto global_best_cost = best_cost;
    double t = initial_temp;

    for (int i = 0; i <= max_iter; i++) {
        best.make_change();

        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;

        
        if (current_cost > best_cost) {
            best_cost = current_cost;
        } else if (static_cast<double>(rand()) / RAND_MAX < exp(-delta / t)) {
            best_cost = current_cost;
        } else {
            best.revert();
        }
        
        if (current_cost > global_best_cost) {
            global_best = best;
            global_best_cost = current_cost;
        }

        t = cooling_strategy_->next(t);

        printf("Iteration %d, Weight: %d, Best Cost: %d, Global Best Cost: %d\n",
               i, best.weight(), best_cost, global_best_cost);
    }

    return global_best;
}