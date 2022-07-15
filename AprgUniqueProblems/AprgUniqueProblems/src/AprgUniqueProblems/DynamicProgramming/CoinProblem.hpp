#pragma once

#include <set>
#include <vector>

namespace alba
{

class CoinProblem
{
public:
    // Given a set of coin values coins = {c1, c2,..., ck} and a target sum of money n
    // First problem: Our task is to form the sum n using as few coins as possible.
    // Second problem: Our task is to calculate the total number of ways to produce a sum x using the coins.

    // First problem - recurrence formulation:
    // -> Let solve(x) denote the minimum number of coins required for a sum x.
    // -> solve(x) =
    // ---> if x<0 : infinity
    // ---> if x=0 : 0
    // ---> if x>0 : minimum of (solve(x-coins)+1) for all coins

    // Second problem - recurrence formulation:
    // -> Let solve(x) denote the number of ways we can form the sum x.
    // -> solve(x) =
    // ---> if x<0 : 0
    // ---> if x=0 : 1
    // ---> if x>0 : summation of (solve(x-coins)) for all coins

    using Coin = unsigned int;
    using Coins = std::vector<Coin>;
    using CoinSet = std::set<Coin>;
    using CoinPermutation = std::vector<Coin>;
    using CoinPermutations = std::set<CoinPermutation>;
    using CoinCombination = std::multiset<Coin>;
    using CoinCombinations = std::set<CoinCombination>;
    using CountPerValue = std::vector<unsigned int>;
    using CountPerValueAndPerCoin = std::vector<std::vector<unsigned int>>;
    using VectorOfCoins = std::vector<Coins>;
    using VectorOfCoinPermutations = std::vector<CoinPermutations>;
    using VectorOfCoinCombinations = std::vector<CoinCombinations>;

    CoinProblem(Coins const& availableCoins);

    Coins getFewestCoinsUsingRecursion(Coin const total);
    Coins getFewestCoinsUsingLoops(Coin const total);
    unsigned int getNumberOfCoinPermutations(Coin const total);
    CoinPermutations getCoinPermutationsUsingLoops(Coin const total);
    unsigned int getNumberOfCoinCombinations(Coin const total);
    CoinCombinations getCoinCombinationsUsingRecursion(Coin const total);
    CoinCombinations getCoinCombinationsUsingLoops(Coin const total);
private:
    void addSolutionWithFewestCoins(Coin const total, Coins const& fewestCoinSolution);
    Coins m_availableCoins;
    VectorOfCoins m_fewestCoins;
    CountPerValue m_countPerValue;
    CountPerValueAndPerCoin m_countPerValuePerCoin;
    VectorOfCoinPermutations m_coinPermutations;
    VectorOfCoinCombinations m_coinCombinations;
};

}
