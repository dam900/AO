#ifndef BACKPACK
#define BACKPACK

#include "backpack.hpp"

void Backpack::load(const BpItems items, uint capacity) {
    for (uint idx = 0; idx < items.size(); idx++) {
        this->weights_.insert({idx, items[idx].first});
        this->prices_.insert({idx, items[idx].second});
    }
    this->capacity = capacity;
    this->numItems = items.size();
}

BpItem Backpack::getItem(uint id) const {
    return {weights_.at(id), prices_.at(id)};
}

uint Backpack::getItemWeight(uint id) const {
    return weights_.at(id);
}

uint Backpack::getItemPrice(uint id) const {
    return prices_.at(id);
}

#endif