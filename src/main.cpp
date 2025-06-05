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

        int max_iter;
        int optimum;
        double initial_prob;
        std::string path;
        
        if (argc < 4) {
            path = "/home/damian/Downloads/instances_01_KP/large_scale/knapPI_1_500_1000_1";
            max_iter = 1000;
            initial_prob = 0.8;
            optimum = read_optimum("/home/damian/Downloads/instances_01_KP/large_scale-optimum/knapPI_1_500_1000_1");
        } else {
            max_iter = std::stoi(argv[1]);
            initial_prob = std::stod(argv[2]);
            path = argv[3];
            // Remove text after the last slash (including it) from path
            auto last_slash = path.find_last_of('/');
            std::string filename = (last_slash != std::string::npos) ? path.substr(last_slash + 1) : path;
            std::string dir = (last_slash != std::string::npos) ? path.substr(0, last_slash) : "";

            optimum = read_optimum(dir.append("-optimum/").append(filename));
        }

        std::cout << "Using path: " << path << std::endl;
        std::cout << "Max iterations: " << max_iter << std::endl;
        std::cout << "Initial probability: " << initial_prob << std::endl;
        std::cout << "Optimum: " << optimum << std::endl << std::endl;
        

        KnapsackProblemInstance bp = KnapsackProblemInstance{};
        bp.load(path);

        auto cooling_strategy = std::make_unique<GeometricCoolingStrategy>(1);
        auto capacity = bp.capacity;

        SimulatedAnnealingSolver solver(std::move(cooling_strategy), bp);
        auto solution = solver.solve(max_iter, initial_prob);

        std::cout << "Best solution found: " << solution.cost() << std::endl;
        std::cout << "Best solution weight: " << solution.weight() << std::endl;
        std::cout << "Is under the wieght limit: " << ((solution.weight() < capacity) ? "True" : "False") << std::endl;
        std::cout << "By how much: " << capacity - solution.weight() << std::endl;
        std::cout << "Optimal solution: " << optimum << std::endl;
        std::cout << "Difference from optimum: " << optimum - solution.cost() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
