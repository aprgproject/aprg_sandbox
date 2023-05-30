#pragma once

#include <limits>
#include <vector>

namespace alba {

class LongestEqualLengthSubArraysWithSameSum {
public:
    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;
    static constexpr Value MIN_VALUE = std::numeric_limits<Value>::min();

    LongestEqualLengthSubArraysWithSameSum(Values const& values);

    Index getLongestTotalLengthOfSubArraysUsingPartialSums() const;
    Index getLongestTotalLengthOfSubArraysByAccumulatingSum() const;

private:
    Values const m_values;
};

}  // namespace alba

// Longest Even Length Substring such that Sum of First and Second Half is same

// Given a string ‘str’ of digits, find the length of the longest substring of ‘str’,
// such that the length of the substring is 2k digits
// and sum of left k digits is equal to the sum of right k digits.

// Examples :
// Input: str = "123123"
// -> Output: 6
// -> The complete string is of even length and sum of first and second
// -> half digits is same
// Input: str = "1538023"
// -> Output: 4
// -> The longest substring with same first and second half sum is "5380"
