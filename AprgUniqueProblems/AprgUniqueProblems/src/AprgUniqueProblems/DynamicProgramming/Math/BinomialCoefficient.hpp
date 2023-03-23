#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class BinomialCoefficient
{
public:

    using Value = unsigned int;
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    static constexpr Value UNUSED_VALUE=std::numeric_limits<Value>::max();

    BinomialCoefficient(Value const n, Value const k);

    Value getBinomialCoefficientUsingNaiveRecursion() const;
    Value getBinomialCoefficientUsingMemoizationDP() const;
    Value getBinomialCoefficientUsingIterativeDP() const;
    Value getBinomialCoefficientUsingIterativeDPAndSpaceEfficient() const;
    Value getBinomialCoefficientUsingGcf() const;

private:
    Value getBinomialCoefficientUsingNaiveRecursion(Value const n, Value const k) const;
    Value getBinomialCoefficientUsingMemoizationDP(ValueMatrix & valueMatrix, Value const n, Value const k) const;
    Value const m_n;
    Value const m_k;};

}

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "n" and "k" has a "value"
// -> Start recursion at the "input n" and "input k" as 0.
// -> Each "value" (with inputs "n" and "k") can be computed by:
// ---> If "n" < "k":
// -----> Result is 0 (invalid cases are zero)
// ---> Else If "k"==0 || "n"=="k":
// -----> Result is 1 (base cases are 1, C(n, 0) = C(n, n) = 1)
// ---> Else:
// -----> Sum the two parts:
// -------> Recursively call "n"-1 and "k"
// -------> Recursively call "n"-1 and "k"-1
// -----> Result is the sum

// 2) Dynamic Programming by Iterative method:
// -> Create an matrix of counts with size of columns as "input n"+1 and size of rows as "input k"+1
// -> At the start, initialize matrix with 0 (for invalid cases is 0)
// -> At the start, fill the first row with 1 (for base case C(n, 0) = 1)
// -> Thus each "n" and "k" has a value.
// -> Forward traversal for "n" and "k" (starting with "n" at 1 and "k" at 1, since first column/row is filled)
// -> Traversal uses previous values to compute for a new value
// -> The computation of each value (each cell in the matrix) is:
// ---> If "n"=="k":
// -----> Result is 1 (base case C(n, n) = 1)
// ---> Else:
// -----> Sum the two parts:
// -------> Get the value of matrix at "n"-1 and "k"
// -------> Get the value of matrix at "n"-1 and "k"-1
// -----> Result is the sum
// -> The last entry in the matrix (with indices "input n" and "input k") contains the total value.

// 3) Dynamic Programming by Iterative method and space efficient:
// -> Create an array of counts with size as "input k"+1.
// -> At the start, initialize array with 0 (for invalid cases is 0)
// -> At the start, fill the first cell with 1 (for base case C(n, 0) = 1)
// -> Thus each "n" and "k" has a value.
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous value to compute for a new value.
// -> The computation of each next value (each cell in the array) is:
// ---> Continue to accumulate for each cell in the array with
// ----->  Get the value of array at "k"-1
// -> The last entry in the array (with index "targetSumOfDigits") contains the total count.
// NOTE: Check comments at the code for demonstration on how it works




// The following are the common definitions of Binomial Coefficients.
// A binomial coefficient C(n, k) can be defined as the coefficient of x^k in the expansion of (1 + x)^n.
// A binomial coefficient C(n, k) also gives the number of ways, disregarding order,
// that k objects can be chosen from among n objects more formally,
// the number of k-element subsets (or k-combinations) of a n-element set.

// Write a function that takes two parameters n and k and returns the value of Binomial Coefficient C(n, k).// For example, your function should return 6 for n = 4 and k = 2, and it should return 10 for n = 5 and k = 2.

// 1) Optimal Substructure
// The value of C(n, k) can be recursively calculated using the following standard formula for Binomial Coefficients.
// -> C(n, k) = C(n-1, k-1) + C(n-1, k)
// -> C(n, 0) = C(n, n) = 1

// 2) Overlapping Subproblems
// It should be noted that the above function computes the same subproblems again and again.
// For large values of n, there will be many common subproblems.
// Since the same subproblems are called again, this problem has Overlapping Subproblems property.
// So the Binomial Coefficient problem has both properties (see this and this) of a dynamic programming problem.
// Like other typical Dynamic Programming(DP) problems,
// re-computations of the same subproblems can be avoided by constructing a temporary 2D-array C[][] in a bottom-up manner.


