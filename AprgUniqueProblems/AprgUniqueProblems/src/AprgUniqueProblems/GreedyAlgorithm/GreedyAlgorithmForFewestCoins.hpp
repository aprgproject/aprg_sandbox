#pragma once

#include <vector>

namespace alba
{

class GreedyAlgorithmForFewestCoins
{
public:
    using Coin = unsigned int;
    using Coins = std::vector<Coin>;
    using Value = unsigned int;

    GreedyAlgorithmForFewestCoins(Coins const& availableCoins);

    unsigned int getFewestNumberOfCoins(Value const value) const;

private:
    void initialize();
    Coins m_sortedAvailableCoins;
};

}

