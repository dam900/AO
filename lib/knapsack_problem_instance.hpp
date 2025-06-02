#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <cstdint> 

using BpItem = std::pair<uint64_t, uint64_t>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<uint64_t, uint64_t>;
using PriceMap = std::map<uint64_t, uint64_t>;

std::tuple<BpItems, uint64_t> load_data_from_file(const std::string& filename);
std::pair<uint64_t, BpItems> load_solution_from_file(const std::string& filename);
BpItems load_from_file_01(const std::string& filename);

class KnapsackProblemInstance {
   public:
    void load(const BpItems items, uint64_t capacity);
    void load(std::string filename, uint64_t capacity);

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

    BpItem getItem(uint64_t id) const;
    uint64_t getItemWeight(uint64_t id) const;
    uint64_t getItemPrice(uint64_t id) const;

    uint64_t capacity;
    uint64_t numItems;

    std::vector<std::pair<uint64_t, double>> get_sorted_items_by_ratio() const;
    
   private:
    WeightMap weights_;
    PriceMap prices_;
};
