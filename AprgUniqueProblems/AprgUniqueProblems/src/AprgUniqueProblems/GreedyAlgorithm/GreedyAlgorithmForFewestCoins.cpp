#include "GreedyAlgorithmForFewestCoins.hpp"

#include <algorithm>

using namespace std;

namespace alba
{

GreedyAlgorithmForFewestCoins::GreedyAlgorithmForFewestCoins(
        Coins const& availableCoins)
    : m_sortedAvailableCoins(availableCoins)
{
    initialize();
}

unsigned int GreedyAlgorithmForFewestCoins::getFewestNumberOfCoins(Value const value) const
{
    // Greedy strategy is to subtract the largest possible coin until value reaches to zero
    // Note: The above approach may not work for all denominations.

    unsigned int result(0U);
    unsigned int count(0U);    Value partialValue(value);
    for(Coin const& coin : m_sortedAvailableCoins)
    {
        while(partialValue >= coin)        {
            partialValue -= coin;
            count++;
        }
    }
    if(partialValue == 0U)
    {
        result = count;
    }
    return result;
}

void GreedyAlgorithmForFewestCoins::initialize()
{
    sort(m_sortedAvailableCoins.begin(), m_sortedAvailableCoins.end(), [](
         Coin const& coin1, Coin const& coin2) // sort by higher
    {
        return coin1 > coin2;
    });
}

}
