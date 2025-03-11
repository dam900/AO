#include <iostream>
#include <vector>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    uint cost(const KnapsackProblemInstance& pinstance);

   private:
    std::vector<uint> csol_;
};