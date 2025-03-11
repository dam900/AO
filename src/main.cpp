#include <iostream>
#include <map>
#include <vector>

#include "backpack.hpp"

using BpItem = std::pair<uint, uint>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<uint, uint>;
using PriceMap = std::map<uint, uint>;

BpItems loadBpData() {
    return BpItems{{1, 1}, {3, 2}, {4, 4}, {4, 4}, {5, 5}, {6, 6}};
}

void initDataContainers(BpItems& items, std::map<uint, uint>& weights, std::map<uint, uint>& prices) {
    for (uint idx = 0; idx < items.size(); idx++) {
        weights.insert({idx, items[idx].first});
        prices.insert({idx, items[idx].second});
    }
}

int main() {
    auto items = loadBpData();
    auto prices = PriceMap{};
    auto weights = WeightMap{};

    const auto MAX_WEIGHT = 5;

    initDataContainers(items, prices, weights);
    for (uint idx = 0; idx < items.size(); idx++) {
        std::cout << idx << prices.at(idx) << weights.at(idx) << std::endl;
    }
}
