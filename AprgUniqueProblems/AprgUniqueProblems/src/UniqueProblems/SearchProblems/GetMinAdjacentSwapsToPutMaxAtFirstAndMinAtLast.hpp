#pragma once

namespace alba {

namespace algorithm {

template <typename Values>
class GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLast {
public:
    using Count = int;
    using Index = int;
    using Value = typename Values::value_type;

    GetMinAdjacentSwapsToPutMaxAtFirstAndMinAtLast() = default;

    Count getMinAdjacentSwaps(Values const& values) {
        Count result(0);
        Index size = values.size();
        if (size > 1) {            Index firstMaxIndex = 0, lastMinIndex = 0;
            Value minimum(values.front()), maximum(values.front());
            int i = 0;
            for (Value const& value : values) {                if (maximum < value) {
                    maximum = value;
                    firstMaxIndex = i;
                }
                if (minimum >= value) {
                    minimum = value;
                    lastMinIndex = i;
                }
                i++;
            }
            result = firstMaxIndex + (values.size() - 1 - lastMinIndex);
            if (lastMinIndex < firstMaxIndex) {
                --result;  // reduce one because of overlap
            }
        }
        return result;    }
};

}  // namespace algorithm
}  // namespace alba

// Given N number of elements, find the minimum number of swaps required so that the maximum element
// is at the beginning and the minimum element is at last with the condition that only swapping of adjacent elements is
// allowed.

// The approach will be to find the index of the largest element(let l).
// Find the index of the leftmost largest element if largest element appears in the array more than once.
// Similarly, find the index of the rightmost smallest element(let r). There exists two cases to solve this problem.
// -> Case 1: If l < r: Number of swaps = l + (n-r-1)
// -> Case 2: If l > r: Number of swaps = l + (n-r-2), as one swap has already been performed while swapping the larger
// element to the front

// Time Complexity: O(N)
