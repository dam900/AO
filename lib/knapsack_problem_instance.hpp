#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <cstdint> 

using BpItem = std::pair<int, int>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<int, int>;
using PriceMap = std::map<int, int>;
using ItemRatio = std::pair<int, double>; 

class KnapsackProblemInstance {
   public:
    void load(const BpItems items, int capacity);
    void load(std::string& filename);

    BpItem getItem(int id) const;
    int getItemWeight(int id) const;
    int getItemPrice(int id) const;

    int capacity;
    int numItems;

    std::vector<ItemRatio> sorted_by_ratio() const;
    
   private:
    WeightMap weights_;
    PriceMap prices_;
};
