#include "CountTotalSetBitsInAllNumbersFrom1ToN.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

CountTotalSetBitsInAllNumbersFrom1ToN::CountTotalSetBitsInAllNumbersFrom1ToN() {}

CountTotalSetBitsInAllNumbersFrom1ToN::Value CountTotalSetBitsInAllNumbersFrom1ToN::getTotalSetBitsUsingPopcount(
    Value const endValue) const {
    Value result{};
    for (Value currentValue = 0; currentValue <= endValue; ++currentValue) {
        result += AlbaBitValueUtilities<Value>::getNumberOfOnes(currentValue);
    }
    return result;
}

CountTotalSetBitsInAllNumbersFrom1ToN::Value
CountTotalSetBitsInAllNumbersFrom1ToN::getTotalSetBitsUsingPreComputedBitCounts(Value const endValue) const {
    constexpr auto MAX_NUMBER_OF_BITS = AlbaBitValueUtilities<Value>::getNumberOfBits();
    Values countsBeforeThisBit;
    countsBeforeThisBit.reserve(MAX_NUMBER_OF_BITS);
    countsBeforeThisBit.emplace_back(1);
    for (Value bitPosition = 1; bitPosition < MAX_NUMBER_OF_BITS; ++bitPosition) {
        Value valueForBitPosition = (1 << bitPosition) + 2 * countsBeforeThisBit[bitPosition - 1];
        // Formula: count = 2*previousValue + powerOfTwo;
        // -> From 0 to 1: 2^0 = 1
        // -> From 00 to 11: 2*1 + 2^1 = 4
        // -> From 000 to 111: 2*4  + 2^2 = 12
        // -> From 0000 to 1111: 2*12 + 8 = 36
        countsBeforeThisBit.emplace_back(valueForBitPosition);
    }

    Value result{};
    Value remainingValue{endValue};
    for (Value bitPositionPlusOne = MAX_NUMBER_OF_BITS - 1; bitPositionPlusOne > 0; --bitPositionPlusOne) {
        // Formula: totalCountForCurrentBit = bitCountOfALowerBit + remainingValue-seriesOfOnes;
        // -> For 1: add last bit
        // -> For 10: 1 + 1 = 2
        // -> For 100: 4 + 1 = 5
        // -> For 1000: 12 + 1 = 13
        // -> For 1110: (12 + 7) + (compute for 110) = 19 + (compute for 110)
        // -> For 11: 1 + 2 + (compute for 1)  = 3 + (compute for 1)
        Value powerOfTwo = Value(1) << bitPositionPlusOne;
        Value seriesOfOnes = powerOfTwo - 1;
        if (remainingValue & powerOfTwo) {
            result += countsBeforeThisBit[bitPositionPlusOne - 1] + remainingValue - seriesOfOnes;
            remainingValue ^= powerOfTwo;
        }
    }
    result += remainingValue;
    return result;
}

CountTotalSetBitsInAllNumbersFrom1ToN::Value CountTotalSetBitsInAllNumbersFrom1ToN::getTotalSetBitsUsingBitCounts(
    Value const endValue) const {
    constexpr auto MAX_NUMBER_OF_BITS = AlbaBitValueUtilities<Value>::getNumberOfBits();
    Value result(endValue & 1);
    Value countBeforeThisBit = 1;
    for (Value bitPosition = 1; bitPosition < MAX_NUMBER_OF_BITS; ++bitPosition) {
        Value powerOfTwo = Value(1) << bitPosition;
        Value seriesOfOnes = powerOfTwo - 1;
        if (endValue & powerOfTwo) {
            Value countForThisBit = (endValue & seriesOfOnes) + 1;
            result += countBeforeThisBit + countForThisBit;
        }
        countBeforeThisBit = (1 << bitPosition) + 2 * countBeforeThisBit;
        if (endValue >> (bitPosition + 1) == 0) {
            break;
        }
    }

    return result;
}

}  // namespace alba
