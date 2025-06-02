#pragma once

#include <iostream>
#include <vector>
#include <set>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    KnapsackSolutionInstance(KnapsackProblemInstance pinstance) : pinstance_(pinstance) {};
    uint64_t cost();
    void revert();  // Undo the last change
    uint64_t weight();
    void make_change(std::set<std::vector<bool>>& checked_solutions);
    std::vector<bool> get_sol();  // Current solution (list of item IDs)
    std::vector<bool> get_prev_sol();

   private:
    KnapsackProblemInstance pinstance_;
    std::vector<bool> csol_ = std::vector<bool>(pinstance_.numItems, false);           // Current solution (list of item IDs)
    std::vector<bool> prev_solution_;  // Previous solution for revert
};
