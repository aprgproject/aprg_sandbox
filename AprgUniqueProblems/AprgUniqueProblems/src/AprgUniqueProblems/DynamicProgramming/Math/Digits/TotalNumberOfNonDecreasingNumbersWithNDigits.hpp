#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class TotalNumberOfNonDecreasingNumbersWithNDigits {
public:
    using Count = int;
    using Value = int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT = std::numeric_limits<Count>::max();
    TotalNumberOfNonDecreasingNumbersWithNDigits(Count const numberOfDigits);

    Count getCountUsingNaiveRecursion() const;    Count getCountUsingMemoizationDP() const;
    Count getCountUsingIterativeDP() const;
    Count getCountUsingIterativeDPAndSpaceEfficient() const;
    Count getCountUsingSummationFormula() const;

private:
    Count getCountUsingNaiveRecursion(Value const digitValue, Count const digitIndex) const;
    Count getCountUsingMemoizationDP(CountMatrix& countMatrix, Value const digitValue, Count const digitIndex) const;

    Count const m_numberOfDigits;
};

}  // namespace alba

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "digit value" and "digit index" has a "count"
// -> Sum all recursion base cases of "digit value" from 0 to 9 and digit index as 0.
// -> Each "count" (with inputs "digit value" and "digit index") can be computed by:
// ---> If "digit index" > 0 (this means NOT the most significant digit):
// -----> Accumulate all the counts of all parts of the next digit:
// -------> Iterating "beforeDigitValue" from 0 to "digit value":
// ---------> Recursively call "beforeDigitValue" with "digit index"-1
// -----> Result is the accumulated count
// ---> Else (this means the most significant digit):
// -----> Result is 1

// 2) Dynamic Programming by Iterative method:
// -> Create an matrix of counts with size of columns as 10 and size of rows as "numberOfDigits"
// -> At the start, because its for the most significant digit, fill the first row with 1.
// -> Thus each "digit value" and "digit index" has a count.
// -> Forward traversal for "digit value" and "digit index" (starting with "digit index" at 1, since first row is
// filled)
// -> Traversal uses previous counts to compute for a new count
// -> The computation of each count (each cell in the matrix) is:
// ---> Accumulate all the counts of all parts from previous counts:
// -----> Iterating "beforeDigitValue" from 0 to "digit value":
// -------> Get the previous count by checking the matrix with "beforeDigitValue" and "digit index"-1
// ---> Get sum of counts of the last row for the total count

// 3) Dynamic Programming by Iterative method and space efficient:
// -> Create an array of counts with size as 10.
// -> Initially, because its for the most significant digit, initialize with 1.
// -> Thus each "digit value" has a count.
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous counts to compute for a new count.
// -> The computation of each next count (each cell in the array) is:
// ---> Accumulate all the counts of all parts from previous counts:
// -----> Iterating "beforeDigitValue" from 0 to "digit value":
// -------> Get the previous count by checking the array with "beforeDigitValue"
// ---> Get sum of array of counts for the total count

// Total number of non-decreasing numbers with n digits

// A number is non-decreasing if every digit (except the first one) is greater than or equal to previous digit.
// For example, 223, 4455567, 899, are non-decreasing numbers.
// So, given the number of digits n, you are required to find the count of total non-decreasing numbers with n digits.

// Examples:
// Input:  n = 1
// -> Output: count  = 10
// Input:  n = 2
// -> Output: count  = 55
// Input:  n = 3
// -> Output: count  = 220
