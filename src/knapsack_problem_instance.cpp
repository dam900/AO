#ifndef BACKPACK
#define BACKPACK

#include "knapsack_problem_instance.hpp"

void KnapsackProblemInstance::load(const BpItems items, uint capacity) {
    for (uint idx = 0; idx < items.size(); idx++) {
        this->weights_.insert({idx, items[idx].first});
        this->prices_.insert({idx, items[idx].second});
    }
    this->capacity = capacity;
    this->numItems = items.size();
}

BpItem KnapsackProblemInstance::getItem(uint id) const {
    return {weights_.at(id), prices_.at(id)};
}

uint KnapsackProblemInstance::getItemWeight(uint id) const {
    return weights_.at(id);
}

uint KnapsackProblemInstance::getItemPrice(uint id) const {
    return prices_.at(id);
}

#endif