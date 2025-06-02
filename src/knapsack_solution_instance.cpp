#include "knapsack_solution_instance.hpp"

#include <algorithm>
#include <numeric>
#include <optional>
#include <random>

uint64_t KnapsackSolutionInstance::cost() {
    return std::accumulate(this->csol_.begin(), this->csol_.end(), 0, [this](uint64_t sum, const auto& item) {
        return sum + pinstance_.getItemPrice(item);
    });
}

uint64_t KnapsackSolutionInstance::weight() {
    uint64_t current_weight = 0;
    for (const auto& item : csol_) {
        current_weight += pinstance_.getItemWeight(item);
    }
    return current_weight;
}

std::vector<uint64_t> KnapsackSolutionInstance::get_sol() {
    return csol_;
}

std::vector<uint64_t> KnapsackSolutionInstance::get_prev_sol() {
    return prev_solution_;
}
std::vector<std::pair<uint64_t, double>> KnapsackSolutionInstance::get_sorted_items_by_ratio() const {
    std::vector<std::pair<uint64_t, double>> sorted_items;
    for (uint64_t i = 0; i < pinstance_.numItems; i++) {
        double ratio = static_cast<double>(pinstance_.getItemPrice(i)) / pinstance_.getItemWeight(i);
        sorted_items.emplace_back(i, ratio);
    }
    std::sort(sorted_items.begin(), sorted_items.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return sorted_items;
}

void KnapsackSolutionInstance::make_change(const std::vector<std::pair<uint64_t, double>>& sorted_items) {
    std::copy(csol_.begin(), csol_.end(), std::back_inserter(prev_solution_));
    uint64_t current_weight = weight();

    std::optional<uint64_t> removed_item_id;

    for (const auto& item : sorted_items) {
        uint64_t item_id = item.first;
        uint64_t item_weight = pinstance_.getItemWeight(item_id);

        if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
            csol_.push_back(item_id);
            return;
        }
    }

    if (!csol_.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, csol_.size() - 1);

        uint64_t random_index = dis(gen);
        removed_item_id = csol_[random_index];
        current_weight -= pinstance_.getItemWeight(csol_[random_index]);
        csol_.erase(csol_.begin() + random_index);
    }

    // for (const auto& item : sorted_items) {
    //     uint64_t item_id = item.first;
    //     uint64_t item_weight = pinstance_.getItemWeight(item_id);
    //     uint64_t item_price = pinstance_.getItemPrice(item_id);

    //     if (removed_item_id.has_value()) {
    //         uint64_t removed_weight = pinstance_.getItemWeight(removed_item_id.value());
    //         uint64_t removed_price = pinstance_.getItemPrice(removed_item_id.value());

    //         if (item_weight == removed_weight && item_price == removed_price) {
    //             continue;
    //         }
    //     }

    //     if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end() && current_weight + item_weight <= pinstance_.capacity) {
    //         csol_.push_back(item_id);
    //         current_weight += item_weight;
    //     }
    // }

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, sorted_items.size() - 1);

for (size_t i = 0; i < 100; ++i) {

    uint64_t random_index = dis(gen);
    uint64_t item_id = sorted_items[random_index].first;
    uint64_t item_weight = pinstance_.getItemWeight(item_id);
    uint64_t item_price = pinstance_.getItemPrice(item_id);

    if (std::find(csol_.begin(), csol_.end(), item_id) == csol_.end())
    {
        if (current_weight + item_weight <= pinstance_.capacity) {
            csol_.push_back(item_id);
            current_weight += item_weight;
        }
    }
}


}

void KnapsackSolutionInstance::revert() {
    // csol_ = prev_solution_;
    std::copy(prev_solution_.begin(), prev_solution_.end(), std::back_inserter(csol_));
}
