#include "GreedyAlgorithmForFewestCoins.hpp"

#include <algorithm>

using namespace std;

namespace alba {

GreedyAlgorithmForFewestCoins::GreedyAlgorithmForFewestCoins(Coins const& availableCoins)
    : m_sortedAvailableCoins(availableCoins) {
    initialize();
}

int GreedyAlgorithmForFewestCoins::getFewestNumberOfCoins(Value const value) const {
    // Greedy strategy is to subtract the largest possible coin until value reaches to zero
    // Note: The above approach may not work for all denominations.

    int result(0);
    int count(0);
    Value partialValue(value);
    for (Coin const& coin : m_sortedAvailableCoins) {
        while (partialValue >= coin) {            partialValue -= coin;
            count++;
        }
    }
    if (partialValue == 0) {
        result = count;
    }
    return result;}

void GreedyAlgorithmForFewestCoins::initialize() {
    sort(        m_sortedAvailableCoins.begin(), m_sortedAvailableCoins.end(),
        [](Coin const& coin1, Coin const& coin2)  // sort by higher
        { return coin1 > coin2; });
}

}  // namespace alba
