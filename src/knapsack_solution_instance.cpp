#include "knapsack_solution_instance.hpp"

#include <algorithm>
#include <numeric>
#include <optional>
#include <random>

// uint64_t KnapsackSolutionInstance::cost() {
//     return std::accumulate(this->csol_.begin(), this->csol_.end(), 0, [this](uint64_t sum, const auto& item) {
//         return sum + pinstance_.getItemPrice(item);
//     });
// }

uint64_t KnapsackSolutionInstance::weight() {
    uint64_t weight = 0;
    for (size_t i = 0; i < csol_.size(); i++) {
        if (csol_[i]) {
            weight += pinstance_.getItemWeight(i);
        }
    }
    return weight;
}

std::vector<bool> KnapsackSolutionInstance::get_sol() {
    return csol_;
}

std::vector<bool> KnapsackSolutionInstance::get_prev_sol() {
    return prev_solution_;
}

// void KnapsackSolutionInstance::make_change(const std::vector<std::pair<uint64_t, double>>& sorted_items) {
//     std::copy(csol_.begin(), csol_.end(), std::back_inserter(prev_solution_));
//     uint64_t current_weight = weight();

//     std::optional<uint64_t> removed_item_id;

//     for (const auto& item : sorted_items) {
//         uint64_t item_id = item.first;
//         uint64_t item_weight = pinstance_.getItemWeight(item_id);

//         if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
//             csol_.push_back(item_id);
//             return;
//         }
//     }

//     if (!csol_.empty()) {
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dis(0, csol_.size() - 1);

//         uint64_t random_index = dis(gen);
//         removed_item_id = csol_[random_index];
//         current_weight -= pinstance_.getItemWeight(csol_[random_index]);
//         csol_.erase(csol_.begin() + random_index);
//     }

//     // for (const auto& item : sorted_items) {
//     //     uint64_t item_id = item.first;
//     //     uint64_t item_weight = pinstance_.getItemWeight(item_id);
//     //     uint64_t item_price = pinstance_.getItemPrice(item_id);

//     //     if (removed_item_id.has_value()) {
//     //         uint64_t removed_weight = pinstance_.getItemWeight(removed_item_id.value());
//     //         uint64_t removed_price = pinstance_.getItemPrice(removed_item_id.value());

//     //         if (item_weight == removed_weight && item_price == removed_price) {
//     //             continue;
//     //         }
//     //     }

//     //     if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
//     //         csol_.push_back(item_id);
//     //         current_weight += item_weight;
//     //     }
//     // }

// std::random_device rd;
// std::mt19937 gen(rd());
// std::uniform_int_distribution<> dis(0, sorted_items.size() - 1);

// for (size_t i = 0; i < 100; ++i) {

//     uint64_t random_index = dis(gen);
//     uint64_t item_id = sorted_items[random_index].first;
//     uint64_t item_weight = pinstance_.getItemWeight(item_id);
//     uint64_t item_price = pinstance_.getItemPrice(item_id);

//     if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end())
//     {
//         if (current_weight + item_weight <= pinstance_.capacity) {
//             csol_.push_back(item_id);
//             current_weight += item_weight;
//         }
//     }
// }


// }

void KnapsackSolutionInstance::revert() {
    std::copy(prev_solution_.begin(), prev_solution_.end(), std::back_inserter(csol_));
}

uint64_t KnapsackSolutionInstance::cost() {
    uint64_t sum = 0;
    for (size_t i = 0; i < csol_.size(); i++) {
        if (csol_[i]) {
            sum += pinstance_.getItemPrice(i);
        }
    }
    return sum;
}
void KnapsackSolutionInstance::make_change(std::set<std::vector<bool>>& checked_solutions) {
    std::copy(csol_.begin(), csol_.end(), std::back_inserter(prev_solution_));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob_dist(0.0, 1.0);
    std::uniform_int_distribution<> dis(0, pinstance_.numItems - 1);

    auto sorted_items = pinstance_.get_sorted_items_by_ratio();
    uint64_t current_weight = weight();

    double action_prob = prob_dist(gen);

    if (action_prob <= 0.5) {
        double add_prob = prob_dist(gen);

        if (add_prob <= 0.5) {
            for (const auto& item : sorted_items) {
                uint64_t item_id = item.first;
                uint64_t item_weight = pinstance_.getItemWeight(item_id);

                if (!csol_[item_id] && current_weight + item_weight <= pinstance_.capacity) {
                    csol_[item_id] = true;
                    current_weight += item_weight;

                    if (checked_solutions.find(csol_) != checked_solutions.end()) {
                        csol_[item_id] = false;
                        current_weight -= item_weight;
                    } else {
                        break;
                    }
                }
            }
        } else {
            for (size_t i = 0; i < 100; ++i) {
                uint64_t random_index = dis(gen);
                uint64_t item_weight = pinstance_.getItemWeight(random_index);

                if (!csol_[random_index] && current_weight + item_weight <= pinstance_.capacity) {
                    csol_[random_index] = true;
                    current_weight += item_weight;

                    if (checked_solutions.find(csol_) != checked_solutions.end()) {
                        csol_[random_index] = false;
                        current_weight -= item_weight;
                    } else {
                        break;
                    }
                }
            }
        }
    } else {
        std::vector<uint64_t> selected_items;
        for (size_t i = 0; i < csol_.size(); ++i) {
            if (csol_[i]) {
                selected_items.push_back(i);
            }
        }

        if (!selected_items.empty()) {
            double remove_prob = prob_dist(gen);

            if (remove_prob <= 0.5) {
                uint64_t worst_item_id = selected_items[0];
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
                uint64_t random_item_id = selected_items[remove_dis(gen)];

                csol_[random_item_id] = false;
                current_weight -= pinstance_.getItemWeight(random_item_id);
            }
        }
    }
}
