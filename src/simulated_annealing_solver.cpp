#include "simulated_annealing_solver.hpp"

#include <math.h>

#include <algorithm>
#include <random>

KnapsackSolutionInstance SimulatedAnnealingSolver::solve(uint64_t max_iter, double initial_temp) {
    auto best = sinstance_;
    auto best_cost = best.cost();
    double t = initial_temp;

    auto sorted_items = best.get_sorted_items_by_ratio();

    for (uint64_t i = 0; i <= max_iter; i++) {
        best.make_change(sorted_items);
        auto current_cost = best.cost();
        auto delta = current_cost - best_cost;

        if (current_cost > best_cost) {
            best_cost = current_cost;
        } else if (static_cast<double>(rand()) / RAND_MAX < exp(-delta / t)) {
            best_cost = current_cost;
        } else {
            best.revert();
        }
        t = cooling_strategy_->next(t);

        auto c = best.get_sol();
        auto p = best.get_prev_sol();
        auto to_print = std::vector<uint64_t>{};

        for (const auto &i : c) {
            if (auto it = std::find(p.begin(), p.end(), i); it == p.end()) {
                to_print.push_back(i);
            }
        }
        for (const auto &item : to_print) {
            std::cout << item << " ";
        }
        std::cout << std::endl;

        // printf("Iteration %lu, Temperature: %.2f, Best Cost: %lu\n", i, t, best_cost);
    }

    return best;
}