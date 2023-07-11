#include "FractionalKnapsack.hpp"

#include <algorithm>

using namespace std;

namespace alba {

FractionalKnapsack::Profit FractionalKnapsack::getBestProfit(Weight const maximumWeight, Items const& items) const {
    // Time Complexity: O(N log N)
    // Auxiliary Space: O(N)

    Items sortedItems(items);
    sort(sortedItems.begin(), sortedItems.end(), [](Item const& item1, Item const& item2) {
        return static_cast<double>(item1.first) / item1.second > static_cast<double>(item2.first) / item2.second;
    });

    Profit result(0);
    Weight remainingWeight(maximumWeight);
    for (auto const& [weight, profit] : items) {
        if (weight <= maximumWeight) {
            remainingWeight -= weight;
            result += profit;
        } else {
            result += profit * (static_cast<double>(remainingWeight) / weight);
            break;
        }
    }
    return result;
}

}  // namespace alba
