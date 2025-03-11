#include <iostream>
#include <map>
#include <vector>

#include "backpack.hpp"

int main() {
    auto items = BpItems{{1, 1}, {2, 2}, {1, 2}, {3, 3}};

    auto bp = Backpack();
    bp.load(items, 5);
}
