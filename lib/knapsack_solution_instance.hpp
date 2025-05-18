#include <iostream>
#include <vector>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    KnapsackSolutionInstance(KnapsackProblemInstance pinstance) : pinstance_(pinstance) {};
    uint cost();
    void revert(); // Undo the last change
    std::vector<std::pair<uint, double>> get_sorted_items_by_ratio() const;
    void make_change(const std::vector<std::pair<uint, double>>& sorted_items);

   private:
    KnapsackProblemInstance pinstance_;
    std::vector<uint> csol_; // Current solution (list of item IDs)
    std::vector<uint> prev_solution_; // Previous solution for revert
};
