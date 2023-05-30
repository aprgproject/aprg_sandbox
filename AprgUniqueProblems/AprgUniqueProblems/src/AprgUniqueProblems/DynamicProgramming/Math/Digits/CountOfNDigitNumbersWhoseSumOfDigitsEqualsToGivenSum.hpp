#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum {
public:
    using Count = int;
    using Value = int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT = std::numeric_limits<Count>::max();

    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum(Count const numberOfDigits, Value const sumOfDigits);

    Count getCountUsingNaiveRecursion() const;
    Count getCountUsingMemoizationDP() const;
    Count getCountUsingIterativeDP() const;
    Count getCountUsingIterativeDPAndSpaceEfficient() const;
    Count getCountBySearchingValuesWith1And9Increment() const;

private:
    Count getCountUsingNaiveRecursion(Value const partialSum, Count const digitIndex) const;
    Count getCountUsingMemoizationDP(CountMatrix& countMatrix, Value const partialSum, Count const digitIndex) const;

    Count const m_numberOfDigits;
    Value const m_targetSumOfDigits;
};

}  // namespace alba

// APPROACH:
// 1) Naive Recursion / Dynamic Programming by Memoization:
// -> Each "partialSum" and "digit index" has a "count"
// -> Start recursion at the "targetSumOfDigits" and "digit index" as 0.
// -> Each "count" (with inputs "partialSum" and "digit index") can be computed by:
// ---> If "digit index" > 0 (this means NOT the most significant digit):
// -----> If "partialSum" > 0
// -------> Accumulate all the counts of all parts of the next digit:
// ---------> With "digit value" from 0 to 9
// -----------> Recursively call "partialSum" - "digit value" with "digit index"-1
// -------> Result is the accumulated count
// -----> Else:
// -------> Result is 1 (if partial sum is zero, add one count for zero digit value)
// ---> Else "partialSum" <= 9 ((this means the most significant digit should be 1 to 9):
// -----> Result is 1 (if last digit, add one count if possible)

// 2) Dynamic Programming by Iterative method:
// -> Create an matrix of counts with size of columns as "targetSumOfDigits"+1 and size of rows as "numberOfDigits"
// -> At the start, because its for the most significant digit, fill the first row with 1 if possible (note the count
// for zero is 1)
// -> Thus each "partialSum" and "digit index" has a count.
// -> Forward traversal for "partialSum" and "digit index" (starting with "digit index" at 1, since first row is filled)
// -> Traversal uses previous counts to compute for a new count
// -> The computation of each count (each cell in the matrix) is:
// ---> Accumulate all the counts of all parts from previous counts:
// -----> With "digit value" from of 0 to 9:
// -------> Get the previous count by checking the matrix with "partialSum" - "digit value" and "digit index"-1
// -> The last entry in the matrix (with indices "targetSumOfDigits" and "numberOfDigits"-1) contains the total count.

// 3) Dynamic Programming by Iterative method and space efficient:
// -> Create an array of counts with size as "targetSumOfDigits"+1.
// -> Initially, because its for the most significant digit, initialize with 1 if possible (note the count for zero is
// 1)
// -> Thus each "partialSum" has a count.
// -> Reverse traversal (from right to left)
// ---> Reverse traversal so that the changed values wont be changed again in one iteration
// -> Traversal uses previous counts to compute for a new count.
// -> The computation of each next count (each cell in the array) is:
// ---> Accumulate all the counts of all parts from previous counts:
// -----> With "digit value" from of 1 to 9 (no need to process zero because the count is 1):
// -------> Get the previous count by checking the array with "partialSum" - "digit value"
// -> The last entry in the array (with index "targetSumOfDigits") contains the total count.

// Count of n digit numbers whose sum of digits equals to given sum

// Given two integers ‘n’ and ‘sum’, find count of all n digit numbers with sum of digits as ‘sum’. Leading 0’s are not
// counted as digits.
// -> 1 <= n <= 100 and
// -> 1 <= sum <= 500

// Example:
// Input:  n = 2, sum = 2
// -> Output: 2
// -> Explanation: Numbers are 11 and 20
// Input:  n = 2, sum = 5
// -> Output: 5
// -> Explanation: Numbers are 14, 23, 32, 41 and 50
// Input:  n = 3, sum = 6
// -> Output: 21

// The idea is simple, we subtract all values from 0 to 9 from given sum and recur for sum minus that digit. Below is
// recursive formula.
//
// -> countRec(n, sum) = ∑countRec(n-1, sum-x)
// ->                         where 0 =< x = 0

// One important observation is, leading 0's must be handled explicitly as they are not counted as digits.
// So our final count can be written as below.
// -> finalCount(n, sum) = ∑countRec(n-1, sum-x)
// ->                        where 1 =< x = 0

// Another Method
// -> We can easily count n digit numbers whose sum of digit equals to given sum by iterating all n digits
// -> and checking if current n digit number’s sum is equal to given sum,
// -> if it is then we will start increment number by 9 until it reaches to number whose sum of digit’s is greater than
// given sum,
// -> then again we will increment by 1 until we found another number with given sum.
