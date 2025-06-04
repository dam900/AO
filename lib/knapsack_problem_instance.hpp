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

std::tuple<BpItems, int> load_data_from_file(const std::string& filename);
std::pair<int, BpItems> load_solution_from_file(const std::string& filename);
std::pair<BpItems, int> load_from_file_01(const std::string& filename);

class KnapsackProblemInstance {
   public:
    void load(const BpItems items, int capacity);
    void load(std::string filename, int capacity);

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

    BpItem getItem(int id) const;
    int getItemWeight(int id) const;
    int getItemPrice(int id) const;

    int capacity;
    int numItems;

    std::vector<std::pair<int, double>> get_sorted_items_by_ratio() const;
    
   private:
    WeightMap weights_;
    PriceMap prices_;
};
