#include "NextHigherNumberWithSameNumberOfSetBits.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;

namespace alba {

NextHigherNumberWithSameNumberOfSetBits::NextHigherNumberWithSameNumberOfSetBits() {}

NextHigherNumberWithSameNumberOfSetBits::Value NextHigherNumberWithSameNumberOfSetBits::getNextHigherNumber(
    Value const value) const {
    Value result{};
    if (value) {
        Value lastBitOne = AlbaBitValueUtilities<Value>::getLastBitOneOnly(value);
        Value nextHigherByOneBit = value + lastBitOne;
        Value remainingBitsAtTheRight = ((value ^ nextHigherByOneBit) / lastBitOne) >> 2;
        result = nextHigherByOneBit | remainingBitsAtTheRight;
    }
    return result;
}

}  // namespace alba
