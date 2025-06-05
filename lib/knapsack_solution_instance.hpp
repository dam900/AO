#pragma once

#include <iostream>
#include <vector>
#include <set>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    KnapsackSolutionInstance(KnapsackProblemInstance pinstance) : pinstance_(pinstance) {};
    void revert(); 
    void make_change();
    int cost();
    int weight();
    std::vector<bool> getSol();
    std::vector<bool> getPSol();

   private:

    KnapsackProblemInstance pinstance_;
    std::vector<bool> csol_ = std::vector<bool>(pinstance_.numItems, false);         
    std::vector<bool> prev_solution_;  
};
