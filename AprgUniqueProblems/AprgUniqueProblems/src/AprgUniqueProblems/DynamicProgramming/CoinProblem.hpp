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

// Given a value V, if we want to make change for V cents, and we have infinite supply of each of C = { C1, C2, .. , Cm} valued coins,
// what is the minimum number of coins to make the change?

// Examples:
// -> Input: coins[] = {25, 10, 5}, V = 30
// ---> Output: Minimum 2 coins required
// ---> We can use one coin of 25 cents and one of 5 cents

// -> Input: coins[] = {9, 6, 5, 1}, V = 11
// ---> Output: Minimum 2 coins required
// ---> We can use one coin of 6 cents and 1 coin of 5 cents

// This problem is a variation of the problem discussed Coin Change Problem.
// Here instead of finding total number of possible solutions, we need to find the solution with minimum number of coins.

// The minimum number of coins for a value V can be computed using below recursive formula.
// If V == 0, then 0 coins required.
// If V > 0, minCoins(coins[0..m-1], V) = min {1 + minCoins(V-coin[i])} where i varies from 0 to m-1  and coin[i] <= V

// The time complexity of a direct solution is exponential.
// If we draw the complete recursion tree, we can observe that many subproblems are solved again and again.
// For example, when we start from V = 11, we can reach 6 by subtracting one 5 times and by subtracting 5 one times.
// So the subproblem for 6 is called twice.
// Since same subproblems are called again, this problem has Overlapping Subproblems property.
// So the min coins problem has both properties  of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// recomputations of same subproblems can be avoided by constructing a temporary array table[][] in bottom up manner.
// Time complexity of DP solution using loops is O(mV).