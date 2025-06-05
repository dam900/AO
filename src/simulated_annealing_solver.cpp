#include "simulated_annealing_solver.hpp"

#include <math.h>
#include <algorithm>
#include <random>
#include <set>

#define SELF_TUNE_ITERATIONS 100

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(int max_iter, double starting_probabilty) {
    auto best = sinstance_;
    auto global_best = sinstance_;
    auto best_cost = best.cost();
    auto global_best_cost = best_cost;
    auto self_tune_sol = KnapsackSolutionInstance(pinstance_);

    std::vector<int> deltas = std::vector<int>(SELF_TUNE_ITERATIONS, 0);

    for (size_t i = 0; i < SELF_TUNE_ITERATIONS; i++) {
        self_tune_sol.make_change();
        auto current_cost = self_tune_sol.cost();
        auto delta = current_cost - 10000;
        deltas[i] = std::abs(delta);
    }

    auto max = std::max_element(deltas.begin(), deltas.end()); // Ensure max is non-negative
    double t = -static_cast<double>(*max) / log(starting_probabilty);
    auto new_cooling_rate = std::pow((1.0 / t), (1.0 / max_iter));

    if (auto strat = dynamic_cast<GeometricCoolingStrategy*>(cooling_strategy_.get()); strat != nullptr) {
        strat->setCoolingRate(new_cooling_rate);
    } else {
        std::cerr << "Cooling strategy is not GeometricCoolingStrategy, cannot set cooling rate." << std::endl;
        return global_best;
    }

    for (size_t i = 0; i <= max_iter; i++) {
        best.make_change();

        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;

        
        if (current_cost > best_cost) {
            best_cost = current_cost;
        } else if (static_cast<double>(rand()) / RAND_MAX < exp(-static_cast<double>(delta) / static_cast<double>(t))) {
            best_cost = current_cost;
        } else {
            best.revert();
        }
        
        if (current_cost > global_best_cost) {
            global_best = best;
            global_best_cost = current_cost;
        }

        t = cooling_strategy_->next(t);
    }

    return global_best;
}