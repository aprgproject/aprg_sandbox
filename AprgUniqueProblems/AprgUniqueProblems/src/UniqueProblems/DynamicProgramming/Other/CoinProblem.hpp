#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <set>
#include <vector>

namespace alba {

class CoinProblem {
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

    using Value = int;
    using Coins = std::vector<Value>;
    using CoinSet = std::set<Value>;
    using CoinPermutation = std::vector<Value>;
    using CoinPermutations = std::set<CoinPermutation>;
    using CoinCombination = std::multiset<Value>;
    using CoinCombinations = std::set<CoinCombination>;
    using CountPerValue = std::vector<int>;
    using CountMatrix = matrix::AlbaMatrix<int>;
    using VectorOfCoins = std::vector<Coins>;
    using CoinPermutationsPerValue = std::vector<CoinPermutations>;
    using CoinCombinationsPerValue = std::vector<CoinCombinations>;
    static constexpr int UNUSED_COUNT = std::numeric_limits<int>::max();

    CoinProblem(Coins const& availableCoins);

    // fewest coins
    int getNumberOfFewestCoinsUsingMemoizationDP(Value const total) const;
    int getNumberOfFewestCoinsIterativeDP(Value const total) const;
    Coins getFewestCoinsUsingMemoizationDP(Value const total) const;
    Coins getFewestCoinsUsingIterativeDP(Value const total) const;

    // permutations
    int getNumberOfCoinPermutationsMemoizationDP(Value const total) const;
    int getNumberOfCoinPermutationsIterativeDP(Value const total) const;
    CoinPermutations getCoinPermutationsUsingMemoizationDP(Value const total) const;
    CoinPermutations getCoinPermutationsUsingIterativeDP(Value const total) const;

    // combinations
    int getNumberOfCoinCombinationsUsingMemoizationDP(Value const total) const;
    int getNumberOfCoinCombinationsUsingIterativeDP(Value const total) const;
    int getNumberOfCoinCombinationsUsingIterativeDPAndSpaceEfficient(Value const total) const;
    CoinCombinations getCoinCombinationsUsingMemoizationDP(Value const total) const;
    CoinCombinations getCoinCombinationsUsingIterativeDP(Value const total) const;

private:
    Value getMaxAvailableCoin() const;
    Value getMaxOfTotalAndMaxCoinPlusOne(Value const total) const;

    // fewest coins
    int getNumberOfFewestCoinsUsingMemoizationDPInternal(CountPerValue& countPerValue, Value const total) const;
    Coins getFewestCoinsUsingMemoizationDPInternal(VectorOfCoins& fewestCoins, Value const total) const;

    // permutations
    int getNumberOfCoinPermutationsMemoizationDPInternal(CountPerValue& countPerValue, Value const total) const;
    CoinPermutations getCoinPermutationsUsingMemoizationDPInternal(
        CoinPermutationsPerValue& coinPermutationsPerValue, Value const total) const;

    // combinations
    int getNumberOfCoinCombinationsUsingMemoizationDPInternal(
        CountMatrix& countByValueByCoin, Value const total, int const coinIndex) const;
    CoinCombinations getCoinCombinationsUsingMemoizationDPInternal(
        CoinCombinationsPerValue& coinCombinationsPerValue, Value const total) const;
    Coins m_availableCoins;
};

}  // namespace alba

// COIN COMBINATIONS PROBLEM:
// Given a value N, if we want to make change for N cents,
// and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins,
// how many ways can we make the change?
// The order of coins doesn’t matter.

// Examples:
// For N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}.
// -> So output should be 4.
// For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}.
// -> So the output should be 5.

// 1) Optimal Substructure
// -> To count the total number of solutions, we can divide all set solutions into two sets.
// ---> 1) Solutions that do not contain mth coin (or Sm).
// ---> 2) Solutions that contain at least one Sm.
// -> Let count(S[], m, n) be the function to count the number of solutions,
// then it can be written as sum of count(S[], m-1, n) and count(S[], m, n-Sm).
// -> Therefore, the problem has optimal substructure property as the problem can be solved using solutions to
// subproblems.

// It should be noted that without memoization the above function computes the same subproblems again and again.
// See the following recursion tree for S = {1, 2, 3} and n = 5.
// The function C({1}, 3) is called two times.
// If we draw the complete tree, then we can see that there are many subproblems being called more than once.
// Note that C() is the function for counting the combinations
//                             C({1,2,3}, 5)
//                            |             |
//                          |                 |
//              C({1,2,3}, 2)                 C({1,2}, 5)
//             |       |                      |      |
//            |         |                    |         |
// C({1,2,3}, -1)  C({1,2}, 2)        C({1,2}, 3)    C({1}, 5)
//                |    |             |     |           |     |
//              |       |           |       |         |        |
//     C({1,2},0)  C({1},2)   C({1,2},1) C({1},3)    C({1}, 4)  C({}, 5)
//                    | |     | |        ||         |     |
//                   |   |   |   |     |   |       |       |
//                 .      .  .     .   .     .   C({1}, 3) C({}, 4)
//                                                | |
//                                               |   |
//                                              .      .

// FEWEST COIN PROBLEM:
// Given a value V, if we want to make change for V cents, and we have infinite supply of each of C = { C1, C2, .. , Cm}
// valued coins, what is the minimum number of coins to make the change?

// Examples:
// -> Input: coins[] = {25, 10, 5}, V = 30
// ---> Output: Minimum 2 coins required
// ---> We can use one coin of 25 cents and one of 5 cents
// -> Input: coins[] = {9, 6, 5, 1}, V = 11
// ---> Output: Minimum 2 coins required
// ---> We can use one coin of 6 cents and 1 coin of 5 cents

// This problem is a variation of the problem discussed Coin Change Problem.
// Here instead of finding total number of possible solutions, we need to find the solution with minimum number of
// coins.

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
