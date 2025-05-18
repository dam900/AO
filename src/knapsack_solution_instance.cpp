#include "knapsack_solution_instance.hpp"

#include <algorithm>
#include <numeric>
#include <random>


uint KnapsackSolutionInstance::cost() {
    return std::accumulate(this->csol_.begin(), this->csol_.end(), 0, [this](uint sum, const auto& item) {
        return sum + pinstance_.getItemPrice(item);
    });
}

std::vector<std::pair<uint, double>> KnapsackSolutionInstance::get_sorted_items_by_ratio() const {
    std::vector<std::pair<uint, double>> sorted_items;
    for (uint i = 0; i < pinstance_.numItems; i++) {
        double ratio = static_cast<double>(pinstance_.getItemPrice(i)) / pinstance_.getItemWeight(i);
        sorted_items.emplace_back(i, ratio);
    }
    std::sort(sorted_items.begin(), sorted_items.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return sorted_items;
}

void KnapsackSolutionInstance::make_change(const std::vector<std::pair<uint, double>>& sorted_items) {
    prev_solution_ = csol_;

    uint current_weight = 0;
    for (const auto& item : csol_) {
        current_weight += pinstance_.getItemWeight(item);
    }

    for (const auto& item : sorted_items) {
        uint item_id = item.first;
        uint item_weight = pinstance_.getItemWeight(item_id);

        if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
            csol_.push_back(item_id);
            return;
        }
    }

    if (!csol_.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, csol_.size() - 1);

        uint random_index = dis(gen);
        current_weight -= pinstance_.getItemWeight(csol_[random_index]);
        csol_.erase(csol_.begin() + random_index);
    }

    for (const auto& item : sorted_items) {
        uint item_id = item.first;
        uint item_weight = pinstance_.getItemWeight(item_id);

        if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
            csol_.push_back(item_id);
            current_weight += item_weight;
        }
    }
}

void KnapsackSolutionInstance::revert() {
    csol_ = prev_solution_;
}
