#pragma once

#include <vector>

namespace alba
{

class KnapsackProblem
{
public:
    // The term knapsack refers to problems where a set of objects is given, and subsets with some properties have to be found.
    // Knapsack problems can often be solved using dynamic programming.

    // In this section, we focus on the following problem:
    // Given a list of weights [w1,w2,...,wn], determine all sums that can be constructed using the weights.

    // Recurrence formulation:
    // -> Let possible(x,k) = true if we can construct a sum x using the first k weights, and otherwise possible(x,k) = false
    // -> possible(x,k) = possible(x-weight of k,k-1) union possible(x,k-1)

    using Value = unsigned int;
    using Values = std::vector<Value>;

    KnapsackProblem(Values const& values);

    Values getAllPossiblePartialSums() const;
    Values getAllPossiblePartialSumsWithSquareRootAlgorithm();
private:
    Values m_inputValues;
};

}
