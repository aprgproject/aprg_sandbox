#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>

namespace alba {

namespace algorithm {

template <typename Values>
class FindThePairWithClosestToSum {
public:
    using Value = typename Values::value_type;
    using ValuePair = std::pair<Value, Value>;

    FindThePairWithClosestToSum()  // values can be unsorted
    {}

    ValuePair getValuePairThatIsClosestToSum(Values const& values1, Values const& values2, Value const& sumToCheck) {
        ValuePair result{};
        if (!values1.empty() && !values2.empty()) {
            Value minimumDeviation = std::numeric_limits<Value>::max();
            auto forwardIt1 = values1.cbegin();
            auto reverseIt2 = values2.crbegin();
            while (forwardIt1 != values1.cend() && reverseIt2 != values2.crend()) {
                Value currentSum = *forwardIt1 + *reverseIt2;
                Value currentDeviation = mathHelper::getPositiveDelta(currentSum, sumToCheck);
                if (currentDeviation < minimumDeviation) {
                    minimumDeviation = currentDeviation;
                    result = {*forwardIt1, *reverseIt2};
                }
                if (currentSum < sumToCheck) {
                    forwardIt1++;
                } else {
                    reverseIt2++;
                }
            }
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// Given two sorted arrays and a number x, find the pair whose sum is closest to x and the pair has an element from each
// array. We are given two arrays ar1[0…m-1] and ar2[0..n-1] and a number x, we need to find the pair ar1[i] + ar2[j]
// such that absolute value of (ar1[i] + ar2[j] – x) is minimum.

// Can we do it in a single pass and O(1) extra space?
// The idea is to start from left side of one array and right side of another array,
// and use the algorithm same as step 2 of above approach.

// Following is detailed algorithm:
// 1) Initialize a variable diff as infinite (Diff is used to store the difference between pair and x).
// -> We need to find the minimum diff.
// 2) Initialize two index variables l and r in the given sorted array.
// -> (a) Initialize first to the leftmost index in ar1:  l = 0
// -> (b) Initialize second  the rightmost index in ar2:  r = n-1
// 3) Loop while  l = 0
// -> (a) If  abs(ar1[l] + ar2[r] - sum) < diff  then
// ---> update diff and result
// -> (b) If (ar1[l] + ar2[r] <  sum )  then l++
// -> (c) Else r--
