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

void KnapsackSolutionInstance::revert() {
    std::copy(prev_solution_.begin(), prev_solution_.end(), std::back_inserter(csol_));
}

void KnapsackSolutionInstance::make_change() {
    std::copy(csol_.begin(), csol_.end(), std::back_inserter(prev_solution_));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> dis(0, pinstance_.numItems - 1);

    auto sorted_items = pinstance_.sorted_by_ratio();
    int current_weight = weight();

    double action_prob = prob_dist(gen);

    if (action_prob <= 0.5) {
        double add_prob = prob_dist(gen);

        if (add_prob <= 0.5) {
            for (const auto& item : sorted_items) {
                int item_id = item.first;
                int item_weight = pinstance_.getItemWeight(item_id);

                if (!csol_[item_id] && current_weight + item_weight <= pinstance_.capacity) {
                    csol_[item_id] = true;
                    current_weight += item_weight;

                }
            }
        } else {
            for (size_t i = 0; i < 100; ++i) {
                int random_index = dis(gen);
                int item_weight = pinstance_.getItemWeight(random_index);

                if (!csol_[random_index] && current_weight + item_weight <= pinstance_.capacity) {
                    csol_[random_index] = true;
                    current_weight += item_weight;

                }
            }
        }
    } else {
        std::vector<int> selected_items;
        for (size_t i = 0; i < csol_.size(); ++i) {
            if (csol_[i]) {
                selected_items.push_back(i);
            }
        }

        if (!selected_items.empty()) {
            double remove_prob = prob_dist(gen);

            if (remove_prob <= 0.5) {
                int worst_item_id = selected_items[0];
                double worst_ratio = static_cast<double>(pinstance_.getItemPrice(worst_item_id)) /
                                     pinstance_.getItemWeight(worst_item_id);

                for (const auto& item_id : selected_items) {
                    double ratio = static_cast<double>(pinstance_.getItemPrice(item_id)) /
                                   pinstance_.getItemWeight(item_id);
                    if (ratio < worst_ratio) {
                        worst_item_id = item_id;
                        worst_ratio = ratio;
                    }
                }

                csol_[worst_item_id] = false;
                current_weight -= pinstance_.getItemWeight(worst_item_id);
            } else {
                std::uniform_int_distribution<> remove_dis(0, selected_items.size() - 1);
                int random_item_id = selected_items[remove_dis(gen)];

                csol_[random_item_id] = false;
                current_weight -= pinstance_.getItemWeight(random_item_id);
            }
        }
    }
}
