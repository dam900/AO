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
        // Wczytaj dane problemu z pliku test.in
        auto [items, capacity] = load_data_from_file("test.in");

        // Wczytaj rozwiązanie z pliku outp.out
        auto [optimal_price, solution_items] = load_solution_from_file("outp.out");

        // Wyświetl dane problemu
        std::cout << "\nProblem data:" << std::endl;
        std::cout << "Capacity: " << capacity << std::endl;

        // Wyświetl rozwiązanie
        std::cout << "\nSolution:" << std::endl;
        std::cout << "Total profit: " << optimal_price << std::endl;

        KnapsackProblemInstance bp = KnapsackProblemInstance{};

        bp.load(items, capacity);

        // auto cooling_strategy = std::make_unique<LogarithmicCoolingStrategy>(0.01);
        auto cooling_strategy = std::make_unique<GeometricCoolingStrategy>(0.997);

        SimulatedAnnealingSolver solver(std::move(cooling_strategy), bp);

        uint64_t max_iter = 1000;
        double initial_temp = 1000.0;
        auto solution = solver.solve(max_iter, initial_temp);

        std::cout << "Best solution found: " << solution.cost() << std::endl;
        std::cout << "Best solution weight: " << solution.weight() << std::endl;
        std::cout << "Optimal soultion price: " << optimal_price << std::endl;
        std::cout << "Is under the wieght limit: " << ((solution.weight() < capacity) ? "True" : "False") << std::endl;
        std::cout << "By how much: " << static_cast<int>(capacity) - static_cast<int>(solution.weight()) << std::endl;
        std::cout << "Is optimal: " << ((solution.cost() == optimal_price) ? "True" : "False") << std::endl;
        std::cout << "Difference: " << static_cast<int>(optimal_price) - static_cast<int>(solution.cost()) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
