#ifndef BACKPACK
#define BACKPACK

#include "knapsack_problem_instance.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <algorithm>

void KnapsackProblemInstance::load(const BpItems items, int capacity) {
    for (int idx = 0; idx < items.size(); idx++) {
        this->weights_.insert({idx, items[idx].first});
        this->prices_.insert({idx, items[idx].second});
    }
    this->capacity = capacity;
    this->numItems = items.size();
}

BpItem KnapsackProblemInstance::getItem(int id) const {
    return {weights_.at(id), prices_.at(id)};
}

int KnapsackProblemInstance::getItemWeight(int id) const {
    return weights_.at(id);
}

int KnapsackProblemInstance::getItemPrice(int id) const {
    return prices_.at(id);
}

std::vector<std::pair<int, double>> KnapsackProblemInstance::get_sorted_items_by_ratio() const {
    std::vector<std::pair<int, double>> items_with_ratio;

    for (const auto& [id, weight] : weights_) {
        double ratio = static_cast<double>(prices_.at(id)) / weight;
        items_with_ratio.emplace_back(id, ratio);
    }
    
    std::sort(items_with_ratio.begin(), items_with_ratio.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    return items_with_ratio;
}

std::tuple<BpItems, int> load_data_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    BpItems items;
    int num_items;
    int capacity;

    file >> num_items;

    for (int i = 0; i < num_items; ++i) {
        int id, profit, weight;
        file >> id >> profit >> weight;
        items.emplace_back(weight, profit);
    }

    file >> capacity;

    file.close();

    return {items, capacity};
}

std::pair<int, BpItems> load_solution_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    BpItems solution_items;
    int total_profit;

    file >> total_profit;

    int profit, weight;
    while (file >> profit >> weight) {
        solution_items.emplace_back(weight, profit);
    }

    file.close();

    return {total_profit, solution_items};
}

std::pair<BpItems, int> load_from_file_01(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    BpItems items;
    int value, weight, capacity, iters;


    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> iters >> capacity;

    for (size_t i = 0; i < iters; i++) {
        std::getline(file, line);
        std::stringstream ss(line);
        if (ss >> value >> weight) {
            items.emplace_back(weight, value);
        } 
    }

    file.close();

    std::cout << "Loaded " << items.size() << " items from file: " << filename << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "Item " << i << ": Weight = " << items[i].first << ", Value = " << items[i].second << std::endl;
    }

    return {items, capacity};
}

#endif