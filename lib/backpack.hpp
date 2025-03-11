#include <iostream>
#include <map>
#include <vector>

using BpItem = std::pair<uint, uint>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<uint, uint>;
using PriceMap = std::map<uint, uint>;

class Backpack {
   public:
    Backpack();

    void load(const BpItems items, uint capacity);
    void load(std::string filename, uint capacity);

    BpItem getItem(uint id) const;
    uint getItemWeight(uint id) const;
    uint getItemPrice(uint id) const;

    uint capacity;
    uint numItems;

   private:
    WeightMap weights_;
    PriceMap prices_;
};
