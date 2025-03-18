#include <memory>

#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"

class SimulatedAnnealingSolver {
   public:
    SimulatedAnnealingSolver(std::unique_ptr<CoolingStrategy> cooling_strategy, KnapsackProblemInstance pinstance) : cooling_strategy_(std::move(cooling_strategy)), pinstance_(pinstance), sinstance_(pinstance) {}
    KnapsackSolutionInstance solve(uint max_iter, double inital_temp);

   private:
    KnapsackProblemInstance pinstance_;
    KnapsackSolutionInstance sinstance_;
    std::unique_ptr<CoolingStrategy> cooling_strategy_;
};

/**
 * Interface for cooling strategies
 */
class CoolingStrategy {
   public:
    /**
     * Get the next temperature.
     * This function is called after each iteration
     * @param prev_t the previous temperature
     */
    virtual double next(double prev_t) = 0;
};

/**
 * Linear cooling strategy
 * The temperature is decreased by a constant rate
 * t_{i+1} = t_i - cooling_rate
 */
class LinearCoolingStrategy : public CoolingStrategy {
   public:
    LinearCoolingStrategy(double cooling_rate) : cooling_rate(cooling_rate) {}
    double next(double prev_t) override { return prev_t - cooling_rate; }

   private:
    double cooling_rate;
};
/**
 * Geometric cooling strategy
 * The temperature is decreased by a constant rate
 * t_{i+1} = t_i * cooling_rate

*/
class GeometricCoolingStrategy : public CoolingStrategy {
   public:
    GeometricCoolingStrategy(double cooling_rate) : cooling_rate(cooling_rate) {}
    double next(double prev_t) override { return prev_t * cooling_rate; }

   private:
    double cooling_rate;
};

/**
 * Logarithmic cooling strategy
 * The temperature is decreased by a constant rate
 * t_{i+1} = t_i / (1 + lambda * cooling_rate)
 */
class LogarithmicCoolingStrategy : public CoolingStrategy {
   public:
    LogarithmicCoolingStrategy(double lambda) : lambda(lambda) {}
    double next(double prev_t) override { return prev_t / (1 + lambda * prev_t); }

   private:
    double cooling_rate;
    double lambda;
};