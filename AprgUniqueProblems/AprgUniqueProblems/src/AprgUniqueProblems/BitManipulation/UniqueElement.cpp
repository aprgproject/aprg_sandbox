#include "UniqueElement.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <numeric>

using namespace std;

namespace alba {

UniqueElement::UniqueElement() {}

UniqueElement::Value UniqueElement::getAUniqueElementOnTwoDuplicatedValues(Values const& values) const {
    return getXorResult(values);
}

UniqueElement::ValuePairs UniqueElement::getTwoUniqueElementsOnTwoDuplicatedValues(Values const& values) const {
    // Given an array in which all numbers except two are repeated once.
    // (i.e. we have 2n+2 numbers and n numbers are occurring twice and remaining two have occurred once).
    // Find those two numbers in the most efficient way.

    Value xorResult = getXorResult(values);
    Value lastBitOne = AlbaBitValueUtilities<Value>::getLastBitOneOnly(xorResult);

    Value valueWithOne{}, valueWithZero{};
    for (Value const& value : values) {
        if (value & lastBitOne) {
            valueWithOne ^= value;
        } else {
            valueWithZero ^= value;
        }
    }
    return ValuePairs{valueWithOne, valueWithZero};
}

UniqueElement::Value UniqueElement::getAUniqueElementOnThreeDuplicatedValues(Values const& values) const {
    // For three elements {01, 01, 01}:
    // -> twoElementsTracker    : 00 | 00, 00 | 01, 01 | 01, 00 |
    // -> oneElementTracker     : 00 | 01, 01 | 00, 00 | 01, 00 |
    // -> maskToRemoveCommonBits: 11 | 11     | 10     |
    // -> oneElementTracker at the end: 00

    // For one element {01}:
    // -> twoElementsTracker    : 00 | 00, 00
    // -> oneElementTracker     : 00 | 01, 01
    // -> maskToRemoveCommonBits: 11 | 11
    // -> oneElementTracker at the end: 01

    Value twoElementsTracker{}, oneElementTracker{};
    for (Value const& value : values) {
        twoElementsTracker |= (oneElementTracker & value);
        oneElementTracker ^= value;
        Value maskToRemoveCommonBits = ~(oneElementTracker & twoElementsTracker);
        oneElementTracker &= maskToRemoveCommonBits;
        twoElementsTracker &= maskToRemoveCommonBits;
    }
    return oneElementTracker;
}

UniqueElement::Value UniqueElement::getAnElementOccuringOddNumberOfTimes(Values const& values) const {
    // Given an array of positive integers.
    // All numbers occur an even number of times except one number which occurs an odd number of times.
    // Find the number in O(n) time & constant space.
    return getXorResult(values);
}

UniqueElement::Value UniqueElement::getXorResult(Values const& values) const {
    return std::accumulate(values.cbegin(), values.cend(), Value{}, [](Value const partialResult, Value const value) {
        return partialResult ^ value;
    });
}

}  // namespace alba
