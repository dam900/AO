#pragma once

#include <iostream>
#include <vector>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    KnapsackSolutionInstance(KnapsackProblemInstance pinstance) : pinstance_(pinstance) {};
    uint64_t cost();
    void revert();  // Undo the last change
    std::vector<std::pair<uint64_t, double>> get_sorted_items_by_ratio() const;
    void make_change(const std::vector<std::pair<uint64_t, double>>& sorted_items);
    uint64_t weight();
    std::vector<uint64_t> get_sol();  // Current solution (list of item IDs)
    std::vector<uint64_t> get_prev_sol();

   private:
    KnapsackProblemInstance pinstance_;
    std::vector<uint64_t> csol_;           // Current solution (list of item IDs)
    std::vector<uint64_t> prev_solution_;  // Previous solution for revert
};
