#include <iostream>
#include <map>
#include <vector>

#include "knapsack_problem_instance.hpp"

int main() {
    auto items = BpItems{{1, 1}, {2, 2}, {1, 2}, {3, 3}};

    KnapsackProblemInstance bp = KnapsackProblemInstance{};
    bp.load(items, 5);

        for (const auto& item : bp) {
        std::cout << "Item weight: " << item.first << ", value: " << item.second << std::endl;
    }
}
