#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum
{
public:
    using Count = unsigned int;
    using Value = unsigned int;
    using Counts = std::vector<Count>;
    using CountMatrix = matrix::AlbaMatrix<Count>;
    static constexpr Count UNUSED_COUNT=std::numeric_limits<Count>::max();

    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum(Count const numberOfDigits, Value const sumOfDigits);

    Count getCountUsingNaiveRecursion() const;
    Count getCountUsingMemoizationDP() const;    Count getCountUsingTabularDP() const;
    Count getCountUsingTabularDPAndSpaceEfficient() const;
    Count getCountBySearchingValuesWith1And9Increment() const;

private:
    Count getCountUsingNaiveRecursion(Value const partialSum, Count const digitIndex) const;
    Count getCountUsingMemoizationDP(CountMatrix & countMatrix, Value const partialSum, Count const digitIndex) const;

    Count const m_numberOfDigits;
    Value const m_sumOfDigits;};

}
// Count of n digit numbers whose sum of digits equals to given sum

// Given two integers ‘n’ and ‘sum’, find count of all n digit numbers with sum of digits as ‘sum’. Leading 0’s are not counted as digits.
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

// The idea is simple, we subtract all values from 0 to 9 from given sum and recur for sum minus that digit. Below is recursive formula.
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
// -> if it is then we will start increment number by 9 until it reaches to number whose sum of digit’s is greater than given sum,
// -> then again we will increment by 1 until we found another number with given sum.
