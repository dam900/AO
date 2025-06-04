#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"
#include "simulated_annealing_solver.hpp"

int main() {
    try {
        auto data = load_from_file_01("/home/damian/Downloads/instances_01_KP/large_scale/knapPI_1_500_1000_1");
        auto capacity = data.second;

        std::cout << "\nProblem data:" << std::endl;
        std::cout << "Capacity: " << data.second << std::endl;

        KnapsackProblemInstance bp = KnapsackProblemInstance{};

        bp.load(data.first, data.second);

        // auto cooling_strategy = std::make_unique<LogarithmicCoolingStrategy>(0.01);
        auto cooling_strategy = std::make_unique<GeometricCoolingStrategy>(0.997);

        SimulatedAnnealingSolver solver(std::move(cooling_strategy), bp);

        uint64_t max_iter = 15000;
        double initial_temp = 1000.0;
        auto solution = solver.solve(max_iter, initial_temp);
        std::cout << "Best solution found: " << solution.cost() << std::endl;
        std::cout << "Best solution weight: " << solution.weight() << std::endl;
        std::cout << "Is under the wieght limit: " << ((solution.weight() < capacity) ? "True" : "False") << std::endl;
        std::cout << "By how much: " << static_cast<int>(capacity) - static_cast<int>(solution.weight()) << std::endl;
        auto optimum = 28857;
        std::cout << "Optimal solution: " << optimum << std::endl;
        std::cout << "Difference from optimum: " << static_cast<int>(optimum) - static_cast<int>(solution.cost()) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
