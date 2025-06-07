#include "knapsack_solution_instance.hpp"

#include <algorithm>
#include <numeric>
#include <optional>
#include <random>

int KnapsackSolutionInstance::cost() {
    int sum = 0;
    for (size_t i = 0; i < csol_.size(); i++) {
        if (csol_[i]) {
            sum += pinstance_.getItemPrice(i);
        }
    }
    return sum;
}

int KnapsackSolutionInstance::weight() {
    int weight = 0;
    for (size_t i = 0; i < csol_.size(); i++) {
        if (csol_[i]) {
            weight += pinstance_.getItemWeight(i);
        }
    }
    return weight;
}

std::vector<bool> KnapsackSolutionInstance::getSol() {
    return csol_;
}

std::vector<bool> KnapsackSolutionInstance::getPSol() {
    return prev_solution_;
}

void KnapsackSolutionInstance::initialize()
{
    auto sorted_items = pinstance_.sorted_by_ratio();
    int current_weight = 0;
    for (const auto& item : sorted_items) {
        int item_id = item.first;
        int item_weight = pinstance_.getItemWeight(item_id);

        if (current_weight + item_weight <= pinstance_.capacity) {
            csol_[item_id] = true;
            current_weight += item_weight;
        } else {
            csol_[item_id] = false;
        }
    }
}

void KnapsackSolutionInstance::revert() {
    std::copy(prev_solution_.begin(), prev_solution_.end(), std::back_inserter(csol_));
}

void KnapsackSolutionInstance::make_change(bool is_greedy) {
    std::copy(csol_.begin(), csol_.end(), std::back_inserter(prev_solution_));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> dis(0, pinstance_.numItems - 1);

    auto sorted_items = pinstance_.sorted_by_ratio();
    int current_weight = weight();

    for (const auto& item : sorted_items) {
        int item_id = item.first;
        int item_weight = pinstance_.getItemWeight(item_id);

        if (!csol_[item_id] && current_weight + item_weight <= pinstance_.capacity) {
            csol_[item_id] = true;
            current_weight += item_weight;
            return;
        }
    }

    if (is_greedy) {
            int worst_item_id = -1;
            double worst_ratio = std::numeric_limits<double>::max();
        
            for (size_t i = 0; i < csol_.size(); ++i) {
                if (csol_[i]) {
                    double ratio = static_cast<double>(pinstance_.getItemPrice(i)) / pinstance_.getItemWeight(i);
                    if (ratio < worst_ratio) {
                        worst_item_id = i;
                        worst_ratio = ratio;
                    }
                }
            }
        
            if (worst_item_id != -1) {
                csol_[worst_item_id] = false;
                current_weight -= pinstance_.getItemWeight(worst_item_id);
            }
        
            for (const auto& item : sorted_items) {
                int item_id = item.first;
                int item_weight = pinstance_.getItemWeight(item_id);
        
                if (item_id != worst_item_id && !csol_[item_id] && current_weight + item_weight <= pinstance_.capacity) {
                    csol_[item_id] = true;
                    current_weight += item_weight;
                }
            }

    } 
    
    else {
        std::uniform_int_distribution<> remove_dis(0, csol_.size() - 1);
        int random_item_id = remove_dis(gen);

        if (csol_[random_item_id]) {
            csol_[random_item_id] = false;
            current_weight -= pinstance_.getItemWeight(random_item_id);
        }
    

        for (int iteration = 0; iteration < 100; ++iteration) {
            int random_index = dis(gen);
            int item_weight = pinstance_.getItemWeight(random_index);
        
            if (!csol_[random_index] && current_weight + item_weight <= pinstance_.capacity) {
                csol_[random_index] = true;
                current_weight += item_weight;
            }

            if (current_weight == pinstance_.capacity) {
                break;
            }
        }
    }
}
