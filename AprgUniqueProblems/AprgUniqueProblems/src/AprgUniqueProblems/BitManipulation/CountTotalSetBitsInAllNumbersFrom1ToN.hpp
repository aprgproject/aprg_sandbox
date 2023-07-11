#pragma once

#include <cstdint>
#include <vector>

namespace alba {

class CountTotalSetBitsInAllNumbersFrom1ToN {
public:
    using Value = uint64_t;
    using Values = std::vector<Value>;

    CountTotalSetBitsInAllNumbersFrom1ToN();
    Value getTotalSetBitsUsingPopcount(Value const endValue) const;
    Value getTotalSetBitsUsingPreComputedBitCounts(Value const endValue) const;
    Value getTotalSetBitsUsingBitCounts(Value const endValue) const;
};

}  // namespace alba

// Given an array where every element occurs three times, except one element which occurs only once.
// Find the element that occurs once. The expected time complexity is O(n) and O(1) extra space.
