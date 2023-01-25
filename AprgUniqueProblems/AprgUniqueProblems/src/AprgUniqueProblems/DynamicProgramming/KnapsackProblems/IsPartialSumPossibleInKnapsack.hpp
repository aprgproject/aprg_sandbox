#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class IsPartialSumPossibleInKnapsack
{
public:

    using Index = unsigned int;
    using Value = unsigned int;
    enum class State
    {
        Unused,
        False,
        True
    };
    using Values = std::vector<Value>;
    using Booleans = std::vector<bool>;
    using BooleanMatrix = matrix::AlbaMatrix<bool>;
    using StateMatrix = matrix::AlbaMatrix<State>;

    IsPartialSumPossibleInKnapsack(Value const targetSum, Values const& values);

    bool isPartialSumPossibleUsingNaiveRecursion() const;
    bool isPartialSumPossibleUsingMemoizationDP() const;
    bool isPartialSumPossibleUsingTabularDP() const;
    bool isPartialSumPossibleUsingTabularDPAndSpaceEfficient() const;

private:
    bool isPartialSumPossibleUsingNaiveRecursion(Value const partialSum, Index const valueIndex) const;
    bool isPartialSumPossibleUsingMemoizationDP(StateMatrix & stateMatrix, Value const partialSum, Index const valueIndex) const;

    Value m_targetSum;
    Values m_inputValues;
};

}

// RELATED PROBLEM:
// Partition problem
// Partition problem is to determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is the same.
// Examples:
// -> arr[] = {1, 5, 11, 5}
// ---> Output: true
// ---> The array can be partitioned as {1, 5, 5} and {11}
// -> arr[] = {1, 5, 3}
// ---> Output: false
// ---> The array cannot be partitioned into equal sum sets.

// Following are the two main steps to solve this problem:
// 1) Calculate sum of the array. If sum is odd, there can not be two subsets with equal sum, so return false.
// 2) If sum of array elements is even, calculate sum/2 and find a subset of array with sum equal to sum/2.
// The first step is simple. The second step is crucial, it can be solved either using recursion or Dynamic Programming.

// Recursive Solution
// -> Let isSubsetSum(arr, n, sum/2) be the function that returns true if there is a subset of arr[0..n-1] with sum equal to sum/2
// -> The isSubsetSum problem can be divided into two subproblems
// ->  a) isSubsetSum() without considering last element (reducing n to n-1)
// ->  b) isSubsetSum considering the last element (reducing sum/2 by arr[n-1] and n to n-1)
// -> If any of the above subproblems return true, then return true.
// -> isSubsetSum (arr, n, sum/2) = isSubsetSum (arr, n-1, sum/2) ||
// ->                               isSubsetSum (arr, n-1, sum/2 - arr[n-1])

