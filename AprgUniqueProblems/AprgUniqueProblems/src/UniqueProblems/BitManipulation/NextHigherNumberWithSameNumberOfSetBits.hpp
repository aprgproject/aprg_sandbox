#pragma once

#include <cstdint>

namespace alba {

class NextHigherNumberWithSameNumberOfSetBits {
public:
    using Value = uint64_t;

    NextHigherNumberWithSameNumberOfSetBits();
    Value getNextHigherNumber(Value const value) const;
};

}  // namespace alba

// Given a number x, find next number with same number of 1 bits in it’s binary representation.
// For example, consider x = 12, whose binary representation is 1100 (excluding leading zeros on 32 bit machine).
// It contains two logic 1 bits.
// The next higher number with two logic 1 bits is 17 (100012).
