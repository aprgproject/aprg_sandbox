#pragma once

#include <limits>
#include <vector>

namespace alba {

class ComputeSumOfDigitsInAllNumbersFrom1ToN {
public:
    using Value = int;
    using Values = std::vector<Value>;
    static constexpr Value UNUSED_COUNT = std::numeric_limits<Value>::max();
    ComputeSumOfDigitsInAllNumbersFrom1ToN(Value const lastNumber);

    Value getValueUsingNaiveSolution() const;    Value getValueUsingMemoizationDP() const;
    Value getValueUsingSummationValues() const;

private:
    Value getValueUsingMemoizationDP(Value const number) const;
    Value getSummationFrom1ToN(Value const number) const;
    Value const m_lastNumber;
};

}  // namespace alba

// Compute sum of digits in all numbers from 1 to n

// Given a number n, find the sum of digits in all numbers from 1 to n.
// Examples:
// Input: n = 5
// -> Output: Sum of digits in numbers from 1 to 5 = 15
// Input: n = 12
// -> Output: Sum of digits in numbers from 1 to 12 = 51
// Input: n = 328
// -> Output: Sum of digits in numbers from 1 to 328 = 3241
