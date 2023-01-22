#pragma once

#include <vector>

namespace alba
{

class KnapsackProblem
{
public:

    using Value = unsigned int;
    using Values = std::vector<Value>;
    KnapsackProblem(Values const& values);

    Values getAllPossiblePartialSums() const;    Values getAllPossiblePartialSumsWithSquareRootAlgorithm();
private:
    Values m_inputValues;
};

}
// The term knapsack refers to problems where a set of objects is given, and subsets with some properties have to be found.
// Knapsack problems can often be solved using dynamic programming.

// In this section, we focus on the following problem:
// Given a list of weights [w1,w2,...,wn], determine all sums that can be constructed using the weights.

// Recurrence formulation:
// -> Let possible(x,k) = true if we can construct a sum x using the first k weights, and otherwise possible(x,k) = false
// -> possible(x,k) = possible(x-weight of k,k-1) union possible(x,k-1)


// Other discussions:
// Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
// In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively.
// Also given an integer W which represents knapsack capacity,
// find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W.
// You cannot break an item, either pick the complete item or don’t pick it (0-1 property).