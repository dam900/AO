#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>

#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"
#include "simulated_annealing_solver.hpp"

int read_optimum(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path); 
    }
    std::string line;
    std::getline(file, line);

    int optimum;
    std::stringstream ss(line);
    if (!(ss >> optimum)) {
        throw std::runtime_error("Could not read optimum from file: " + path);
    }
    
    file.close();
    return optimum;

}

int main(int argc, char* argv[]) {
    try {
        std::vector<std::string> paths = {
            "knapPI_1_100_1000_1",
            "knapPI_1_200_1000_1",
            "knapPI_1_500_1000_1",
            "knapPI_1_1000_1000_1",
            "knapPI_1_2000_1000_1",
            "knapPI_1_5000_1000_1",
            "knapPI_1_10000_1000_1",
            "knapPI_2_100_1000_1",
            "knapPI_2_200_1000_1",
            "knapPI_2_500_1000_1",
            "knapPI_2_1000_1000_1",
            "knapPI_2_2000_1000_1",
            "knapPI_2_5000_1000_1",
            "knapPI_2_10000_1000_1",
            "knapPI_3_100_1000_1",
            "knapPI_3_200_1000_1",
            "knapPI_3_500_1000_1",
            "knapPI_3_1000_1000_1",
            "knapPI_3_2000_1000_1",
            "knapPI_3_5000_1000_1",
            "knapPI_3_10000_1000_1",
        };
    
        int max_iter = 1000;
        double initial_prob = 0.8;
    
        for (auto& path : paths) {

            std::string data_path = "large_scale/" + path;
            std::string optimum_path = "large_scale-optimum/" + path;

            int optimum = read_optimum(optimum_path);

            std::cout << "Processing path: " << data_path << std::endl;

            KnapsackProblemInstance bp = KnapsackProblemInstance{};
            bp.load(data_path);
            
            auto capacity = bp.capacity;
            
            for (const auto& strategy_type : {"Geometric", "Linear"}) {
                std::unique_ptr<CoolingStrategy> cooling_strategy;
    
                if (strategy_type == std::string("Geometric")) {
                    cooling_strategy = std::make_unique<GeometricCoolingStrategy>(1);
                } else if (strategy_type == std::string("Linear")) {
                    cooling_strategy = std::make_unique<LinearCoolingStrategy>(0.01);
                }

                // Solver bez is_greedy
                SimulatedAnnealingSolver solver_non_greedy(std::move(cooling_strategy), bp);
                auto solution_non_greedy = solver_non_greedy.solve(max_iter, initial_prob);
        
                std::ofstream file_non_greedy("results_non_greedy.txt", std::ios::app);
                file_non_greedy << "Path: " << path << "\n";
                file_non_greedy << "Cooling strategy: " << strategy_type << "\n";
                file_non_greedy << "Best solution found: " << solution_non_greedy.cost() << "\n";
                file_non_greedy << "Best solution weight: " << solution_non_greedy.weight() << "\n";
                file_non_greedy << "Is under the weight limit: " << ((solution_non_greedy.weight() < capacity) ? "True" : "False") << "\n";
                file_non_greedy << "By how much: " << capacity - solution_non_greedy.weight() << "\n";
                file_non_greedy << "Optimal solution: " << optimum << "\n";
                file_non_greedy << "Difference from optimum: " << optimum - solution_non_greedy.cost() << "\n\n";
                file_non_greedy.close();
                
                if (strategy_type == std::string("Geometric")) {
                    cooling_strategy = std::make_unique<GeometricCoolingStrategy>(1);
                } else if (strategy_type == std::string("Linear")) {
                    cooling_strategy = std::make_unique<LinearCoolingStrategy>(0.01);
                }
    
                // Solver z is_greedy

                SimulatedAnnealingSolver solver_greedy(std::move(cooling_strategy), bp);
                auto solution_greedy = solver_greedy.solve(max_iter, initial_prob, true);
    
        
                std::ofstream file_greedy("results_greedy.txt", std::ios::app);
                file_greedy << "Path: " << path << "\n";
                file_greedy << "Cooling strategy: " << strategy_type << "\n";
                file_greedy << "Best solution found: " << solution_greedy.cost() << "\n";
                file_greedy << "Best solution weight: " << solution_greedy.weight() << "\n";
                file_greedy << "Is under the weight limit: " << ((solution_greedy.weight() < capacity) ? "True" : "False") << "\n";
                file_greedy << "By how much: " << capacity - solution_greedy.weight() << "\n";
                file_greedy << "Optimal solution: " << optimum << "\n";
                file_greedy << "Difference from optimum: " << optimum - solution_greedy.cost() << "\n\n";
                file_greedy.close();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
