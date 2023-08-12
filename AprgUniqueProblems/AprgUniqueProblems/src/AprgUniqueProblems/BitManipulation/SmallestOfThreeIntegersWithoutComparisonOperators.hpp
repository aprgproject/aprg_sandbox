#pragma once

#include <cstdint>

namespace alba {

class SmallestOfThreeIntegersWithoutComparisonOperators {
public:
    using Value = uint64_t; // The comparison works only on unsigned values.

    SmallestOfThreeIntegersWithoutComparisonOperators();
    Value getSmallest(Value const value1, Value const value2, Value const value3) const;    bool isLessThan(Value const value1, Value const value2) const;
};

}  // namespace alba
// Write a program to find the smallest of three integers, without using any of the comparison operators.
// Let 3 input numbers be x, y and z.
