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

// APPROACH:
// 1) Naive Recursion /  Dynamic Programming by Memoization:
// -> Each "partialSum" and "value index" has a boolean "isPartialSum" possible
// -> Start recursion at the "targetSum" and value index as 0.
// -> Each "isPartialSum" (with inputs "partialSum" and "value index") can be computed by:
// ---> If "partialSum" == value at "value index":
// -----> Return true
// ---> Else if "partialSum" > value at "value index":
// -----> Get "isPossible" if value is USED:
// -------> Recursively call "partialSum" - value at "value index" and increment to next "value index"
// -----> Get "isPossible" if value is SKIPPED:
// -------> Recursively call "partialSum" and increment to next "value index"
// -----> Return the OR logic of the two (if one of them is possible then its possible)
// ---> Else ("partialSum" < value at "value index"):
// -----> Get "isPossible" if value is SKIPPED:
// -------> Recursively call "partialSum" and increment to next "value index"

// 2) Dynamic Programming by Tabular method:
// -> Create an matrix ("isPartialSumPossible") of booleans with size of columns as "targetSum" and size of rows as number of input values
// -> Thus each "partial sum" and "value index" has a boolean if its possible.
// -> Partial sums that are equal to input values are possible and set to true.
// -> Forward traversal (from top-left to bottom-right)
// -> Traversal uses previous values to compute for a new value
// -> The computation of each cell in "isPartialSumPossible" is:
// ---> Get the previous input value (decrement value index)
// ---> Get initial value of isPossible: Get entry on the matrix if the partial sum and previous input value is possible
// ---> If isPossible is false and "partialSum" >= previous input value:
// -----> Replace "isPossible" if previous input value is USED: Get entry on the matrix if the (partial sum - previous input value) and previous input value is possible

// 3) Dynamic Programming by Tabular method and space efficient:
// -> Create an array of booleans ("isPartialSumPossible") with size as "targetSum"
// -> Thus each "partial sum" has a boolean if its possible.
// -> Set "partial sum" = 0 as true (0 is possible partial sum)
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous values to compute for a new value
// -> Traverse all input values (this ensures that input values are only used once):
// ---> Traverse all the partial sums (from target sum to zero):
// -----> This "partial sum" is possible if "partial sum" >= "input value" and if "partial sum"-"input value" is possible



// Subset Sum Problem
// Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.
// Example:
// -> Input: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
// ---> Output: True// ---> There is a subset (4, 5) with sum 9.
// -> Input: set[] = {3, 34, 4, 12, 5, 2}, sum = 30
// ---> Output: False
// ---> There is no subset that add up to 30.


// Method 1: (Naive Recursion method):
// Approach: For the recursive approach we will consider two cases.
// -> Consider the last element and now the required sum = target sum – value of ‘last’ element and number of elements = total elements – 1
// -> Leave the ‘last’ element and now the required sum = target sum and number of elements = total elements – 1
// Following is the recursive formula for isSubsetSum() problem.
// -> isSubsetSum(set, n, sum)
// -> = isSubsetSum(set, n-1, sum) ||
// ->   isSubsetSum(set, n-1, sum-set[n-1])
// Base Cases:
// -> isSubsetSum(set, n, sum) = false, if sum > 0 and n == 0
// -> isSubsetSum(set, n, sum) = true, if sum == 0


// Complexity Analysis: The naive recursive solution may try all subsets of given set in worst case.
// Therefore time complexity of the above solution is exponential.
// The problem is in-fact NP-Complete (There is no known polynomial time solution for this problem).


// Method 2 (Tabular method):
// To solve the problem in Pseudo-polynomial time use the Dynamic programming.
// So we will create a 2D array of size (arr.size() + 1) * (target + 1) of type boolean.
// The state DP[i][j] will be true if there exists a subset of elements from A[0….i] with sum value = ‘j’.
// The approach for the problem is:
// -> if (A[i-1] > j)
// ---> DP[i][j] = DP[i-1][j]
// -> else
// ---> DP[i][j] = DP[i-1][j] OR DP[i-1][j-A[i-1]]
// This means that if current element has value greater than ‘current sum value’ we will copy the answer for previous cases
// And if the current sum value is greater than the ‘ith’ element we will see if any of previous states have already experienced the sum=’j’ OR any previous states experienced a value ‘j – A[i]’ which will solve our purpose.


// Method 3 (Memoization method):
// -> In this method, we also follow the recursive approach but In this method,
// we use another 2-D matrix in  we first initialize with -1 or any negative value.
// -> In this method, we avoid the few of the recursively call which is repeated itself that’s why we use 2-D matrix.
// In this matrix we store the value of the previous call value.

// Method 4 (Tabular method with less space):
// To further reduce space complexity, we create a boolean 1D array subset[sum+1].
// Using bottom up manner we can fill up this table.// The idea is that we can check if the sum till position “i” is possible
// then if the current element in the array at position j is x, then sum i+x is also possible.
// We traverse the sum array from back to front so that we don’t count any element twice.




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

