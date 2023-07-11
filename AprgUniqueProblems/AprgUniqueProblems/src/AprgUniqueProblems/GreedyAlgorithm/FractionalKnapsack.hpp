#pragma once

#include <vector>

namespace alba {

class FractionalKnapsack {
public:
    using Index = int;
    using Weight = int;
    using Profit = int;
    using Item = std::pair<Weight, Profit>;
    using Profits = std::vector<Profit>;
    using Items = std::vector<Item>;

    Profit getBestProfit(Weight const maximumWeight, Items const& items) const;
};

}  // namespace alba

// This is a variant of 0-1 Knapsack Problem

// -> Given the weights and values of N items,
// ---> put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
// ---> In Fractional Knapsack,
// ---> we can break items for maximizing the total value of the knapsack
//
// -> Note: In the 0-1 Knapsack problem,
// ---> we are not allowed to break items.
// ---> We either take the whole item or don’t take it.
//
// -> Input:
// ---> Items as (value, weight) pairs
// ---> arr[] = {{60, 10}, {100, 20}, {120, 30}}
// ---> Knapsack Capacity, W = 50
// -> Output: Maximum possible value = 240
// ---> Explanation: by taking items of weight 10 and 20 kg and 2/3 fraction of 30 kg.
// ---> Hence total price will be 60+100+(2/3)(120) = 240
//
// -> Input:
// ---> Items as (value, weight) pairs
// ---> arr[] = {{500, 30}}
// ---> Knapsack Capacity, W = 10
// -> Output: 166.667
