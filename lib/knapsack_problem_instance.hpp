#pragma once
#include <iostream>
#include <map>
#include <vector>

using BpItem = std::pair<uint, uint>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<uint, uint>;
using PriceMap = std::map<uint, uint>;

class KnapsackProblemInstance {
   public:
    void load(const BpItems items, uint capacity);
    void load(std::string filename, uint capacity);

    class Iterator {
       public:
        Iterator(WeightMap::const_iterator weightIt, PriceMap::const_iterator priceIt)
            : weightIt_(weightIt), priceIt_(priceIt) {}

        bool operator!=(const Iterator& other) const {
            return weightIt_ != other.weightIt_ || priceIt_ != other.priceIt_;
        }

        void operator++() {
            ++weightIt_;
            ++priceIt_;
        }

        BpItem operator*() const {
            return {weightIt_->first, priceIt_->second};
        }

       private:
        WeightMap::const_iterator weightIt_;
        PriceMap::const_iterator priceIt_;
    };

    Iterator begin() const {
        return Iterator(weights_.cbegin(), prices_.cbegin());
    }

    Iterator end() const {
        return Iterator(weights_.cend(), prices_.cend());
    }

    BpItem getItem(uint id) const;
    uint getItemWeight(uint id) const;
    uint getItemPrice(uint id) const;

    uint capacity;
    uint numItems;

   private:
    WeightMap weights_;
    PriceMap prices_;
};
