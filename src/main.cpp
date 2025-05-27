#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <tuple>
#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"
#include "simulated_annealing_solver.hpp"

int main() {
    try {
        
        // Wczytaj dane problemu z pliku test.in
        auto [items, capacity] = load_data_from_file("test.in");

        // Wczytaj rozwiązanie z pliku outp.out
        auto [total_profit, solution_items] = load_solution_from_file("outp.out");

        // Wyświetl dane problemu
        std::cout << "\nProblem data:" << std::endl;
        std::cout << "Capacity: " << capacity << std::endl;

        // Wyświetl rozwiązanie
        std::cout << "\nSolution:" << std::endl;
        std::cout << "Total profit: " << total_profit << std::endl;

        

        KnapsackProblemInstance bp = KnapsackProblemInstance{};

        bp.load(items, capacity);


        //auto cooling_strategy = std::make_unique<LogarithmicCoolingStrategy>(0.01);
        auto cooling_strategy = std::make_unique<GeometricCoolingStrategy>(0.997);

        SimulatedAnnealingSolver solver(std::move(cooling_strategy), bp);

        uint64_t max_iter = 10000;
        double initial_temp = 1000.0;
        auto solution = solver.solve(max_iter, initial_temp);

        std::cout << "\nBest solution found:" << solution.cost() << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
