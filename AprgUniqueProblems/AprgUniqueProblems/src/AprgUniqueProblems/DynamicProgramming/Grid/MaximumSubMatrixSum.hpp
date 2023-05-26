#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba {

class MaximumSubMatrixSum {
public:
    using Index = int;
    using Value = int;
    struct SubArrayDetails {
        Index left;        Index right;
        Index up;
        Index down;
        Value sum;    };
    using Values = std::vector<Value>;
    using ValueMatrix = matrix::AlbaMatrix<Value>;
    static constexpr Value MIN_VALUE = std::numeric_limits<Value>::min();

    MaximumSubMatrixSum(ValueMatrix const& valueMatrix);

    Value getMaximumSubMatrixSum() const;
    SubArrayDetails getMaximumSubMatrixSumWithDetails() const;

private:
    ValueMatrix const m_valueMatrix;
};

}  // namespace alba

// Maximum sum rectangle in a 2D matrix

// Given a 2D array, find the maximum sum subarray in it.

// For example, in the following 2D array, the maximum sum subarray is highlighted with # rectangle and sum of this
// subarray is 29.
// -----------------
// | 1 | 2|-1|-4|-20|
// ----##########----
// |-8 #-3| 4| 2#  1|
// ----#--------#----
// | 3 # 8|10| 1#  3|
// ----#--------#----
// |-4 #-1| 1| 7# -6|
// ----##########----

// The Naive Solution for this problem is to check every possible rectangle in the given 2D array.
// This solution requires 6 nested loops":
// -> 4 for start and end coordinate of the 2 axis O(n^4)
// -> and 2 for the summation of the sub-matrix O(n^2) (This is constant if you use a 2D range query structure)
// The overall time complexity of this solution would be O(n^6). (And 0(n^4) if you use a 2D range query structure)

// Efficient Approach:
// Kadane’s algorithm for 1D array can be used to reduce the time complexity to O(n^3).
// The idea is to fix the left and right columns one by one and find the maximum sum contiguous rows for every left and
// right column pair. We basically find top and bottom row numbers (which have maximum sum) for every fixed left and
// right column pair. To find the top and bottom row numbers, calculate the sum of elements in every row from left to
// right and store these sums in an array say temp[]. So temp[i] indicates sum of elements from left to right in row i.
// If we apply Kadane’s 1D algorithm on temp[], and get the maximum sum subarray of temp,
// this maximum sum would be the maximum possible sum with left and right as boundary columns.
// To get the overall maximum sum, we compare this sum with the maximum sum so far.
