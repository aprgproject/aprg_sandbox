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
    Value getBinomialCoefficientUsingTabularDP() const;
    Value getBinomialCoefficientUsingTabularDPAndSpaceEfficient() const;
    Value getBinomialCoefficientUsingGcf() const;

private:
    Value getBinomialCoefficientUsingNaiveRecursion(Value const n, Value const k) const;
    Value getBinomialCoefficientUsingMemoizationDP(ValueMatrix & valueMatrix, Value const n, Value const k) const;
    Value const m_n;
    Value const m_k;
};

}

// The following are the common definitions of Binomial Coefficients.
// A binomial coefficient C(n, k) can be defined as the coefficient of x^k in the expansion of (1 + x)^n.
// A binomial coefficient C(n, k) also gives the number of ways, disregarding order,
// that k objects can be chosen from among n objects more formally,
// the number of k-element subsets (or k-combinations) of a n-element set.

// Write a function that takes two parameters n and k and returns the value of Binomial Coefficient C(n, k).
// For example, your function should return 6 for n = 4 and k = 2, and it should return 10 for n = 5 and k = 2.

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


