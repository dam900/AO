#include <iostream>
#include <vector>

#include "knapsack_problem_instance.hpp"

class KnapsackSolutionInstance {
   public:
    KnapsackSolutionInstance(KnapsackProblemInstance pinstance) : pinstance_(pinstance) {};
    uint cost();
    void make_change();  // zmiana wewnętrznego rozwiazania
    void revert();       // cofnięcie zmiany

   private:
    KnapsackProblemInstance pinstance_;
    std::vector<uint> csol_;
};
