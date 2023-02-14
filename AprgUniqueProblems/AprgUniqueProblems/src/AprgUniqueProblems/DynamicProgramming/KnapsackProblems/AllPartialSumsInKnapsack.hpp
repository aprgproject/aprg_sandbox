#pragma once

#include <vector>

namespace alba
{

class AllPartialSumsInKnapsack
{
public:

    using Value = unsigned int;
    using Values = std::vector<Value>;
    using Booleans = std::vector<bool>;

    AllPartialSumsInKnapsack(Values const& values);

    Values getAllPossiblePartialSums() const;
    Values getAllPossiblePartialSumsBySettingFutureValues() const;
    Values getAllPossiblePartialSumsWithSquareRootAlgorithm();

private:
    Values getAllPossiblePartialSums(Booleans const& isPartialSumPossible) const;

    Values m_inputValues;
};

}


// APPROACH:
// 1) Dynamic Programming by Tabular method:
// -> Get the maximum possible partial sum and create an array of booleans ("isPartialSumPossible") with that size
// -> Thus each "partial sum" has a boolean if its possible.
// -> Set "partial sum" = 0 as true (0 is possible partial sum)
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous values (because it was for a previous item) to compute for a new value
// -> Traverse all input values (this ensures that input values are only used once):
// ---> Traverse all the partial sums (from maximum sum to zero):
// -----> This "partial sum" is possible if "partial sum" >= "input value" and if "partial sum"-"input value" is possible

// 2) Dynamic Programming by Tabular method (by setting future values):
// -> Get the maximum possible partial sum and create an array of booleans ("isPartialSumPossible") with that size
// -> Thus each "partial sum" has a boolean if its possible.
// -> Set "partial sum" = 0 as true (0 is possible partial sum)
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous values (because it was for a previous item) to compute for a new value
// -> Traverse all input values (this ensures that input values are only used once):
// ---> Traverse all the partial sums (from maximum sum to zero):
// -----> If current "partial sum" is possible:
// -------> A future "partial sum" is possible if its equal to the current "partial sum" plus an "input value".




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
