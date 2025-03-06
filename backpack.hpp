#include <iostream>
#include <map>
#include <vector>

using BpItem = std::pair<uint, uint>;
using BpItems = std::vector<BpItem>;
using WeightMap = std::map<uint, uint>;
using PriceMap = std::map<uint, uint>;

class Backpack {
   public:
    Backpack(const BpItems& items, uint capacity);
    Backpack(std::string filename, uint capacity);

    void load(const BpItems& items);
    void load(std::string filename);

    BpItem getItem(uint id) const;
    uint getItemWeight(uint id) const;
    uint getItemPrice(uint id) const;

    uint capacity;
    uint numItems;

   private:
    WeightMap weights_;
    PriceMap prices_;
};
