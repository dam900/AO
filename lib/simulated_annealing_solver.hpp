#include <memory>
#include <math.h>

#include "knapsack_problem_instance.hpp"
#include "knapsack_solution_instance.hpp"
#include "results_saver.hpp"

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
    virtual void setCoolingRate(double t_0, int max_iter) = 0;
};

class SimulatedAnnealingSolver {
   public:
    SimulatedAnnealingSolver(std::unique_ptr<CoolingStrategy> cooling_strategy, KnapsackProblemInstance pinstance, ResultsSaver<double> saver) : cooling_strategy_(std::move(cooling_strategy)), pinstance_(pinstance), sinstance_(pinstance), results_saver_(saver) {}
    KnapsackSolutionInstance solve(int max_iter, double inital_temp, bool is_greedy);

   private:
    KnapsackProblemInstance pinstance_;
    KnapsackSolutionInstance sinstance_;
    std::unique_ptr<CoolingStrategy> cooling_strategy_;
    ResultsSaver<double> results_saver_;
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
    void setCoolingRate(double t_0, int max_iter) override {
        cooling_rate = (t_0 - 1.0) / max_iter;
    }

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
    void setCoolingRate(double t_0, int max_iter) override {
        cooling_rate = std::pow((1.0 / t_0), (1.0 / max_iter));
    }

   private:
    double cooling_rate;
};

/**
 * Logarithmic cooling strategy
 * The temperature is decreased by a constant rate
 * t_{i+1} = t_i / (1 + t_i * cooling_rate)
 */
class LogarithmicCoolingStrategy : public CoolingStrategy {
   public:
    LogarithmicCoolingStrategy(double cooling_rate) : cooling_rate(cooling_rate) {}
    double next(double prev_t) override { return prev_t / (1 + cooling_rate * prev_t); }
    void setCoolingRate(double t_0, int max_iter) override {
        cooling_rate = (t_0 - 1.0) / (max_iter * t_0);
    }

   private:
    double cooling_rate;
};